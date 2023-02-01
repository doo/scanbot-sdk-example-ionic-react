//
//  ScanbotSdkPlugin.m
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import "ScanbotSdkPlugin.h"

#import <Foundation/Foundation.h>

#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

#import <ScanbotSDK/SBSDKScanbotSDK.h>
#import "HandyJSONParameters.h"
#import "CDVScanbotSDKConfiguration.h"
#import "ScanbotStorageUtils.h"
#import "LoggingUtils.h"
#import "HashUtils.h"
#import "SharedConfiguration.h"
#import "ObjectMapper.h"
#import "JSONMappings.h"
#import "CDVOCRCompletionAdapter.h"

#import "SBSDKPolygon+JSON.h"
#import "SBSDKOCRResult+JSON.h"

#import <ScanbotSDK/UIImageSBSDK.h>

#import "BarcodeMapping.h"

@implementation ScanbotSdkPlugin

- (BOOL)checkSDKInitializationWithCommand:(CDVInvokedUrlCommand *)command {
    if (![SharedConfiguration defaultConfiguration].isSDKInitialized) {
        NSString *errorMessage = @"Scanbot SDK is not initialized. Please call the ScanbotSdk.initializeSdk() function first.";
        CDVPluginResult *pluginResult = [self pluginResultError:errorMessage];
        [self.commandDelegate sendPluginResult:pluginResult
                                    callbackId:command.callbackId];
        return NO;
    }
    return YES;
}

- (SBSDKBarcodeScanner*) createBarcodeScannerWithConfiguration:(NSDictionary*)configuration {
    SBSDKBarcodeScanner* barcodeScanner = [[SBSDKBarcodeScanner alloc] init];

    barcodeScanner.acceptedBarcodeTypes = extractBarcodeTypes(configuration);
    
    NSArray* acceptedDocumentTypes = extractBarcodeDocumentTypes(configuration);
    if (acceptedDocumentTypes && acceptedDocumentTypes.count > 0) {
        barcodeScanner.acceptedDocumentTypes = acceptedDocumentTypes;
    }
    
    barcodeScanner.additionalParameters = extractAdditionalParameters(configuration);
    
    return barcodeScanner;
}

- (void)detectBarcodesOnImage:(CDVInvokedUrlCommand*)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    NSString* callbackId = command.callbackId;
    
    NSDictionary* configuration = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!configuration) {
        configuration = @{};
    }
    
    NSString* imageUri = [configuration objectForKey:@"imageFileUri"];
    if (imageUri == nil) {
        [self reportError:@"Missing argument value for 'imageFileUri'." toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        
        SBSDKBarcodeScanner* barcodeScanner = [self createBarcodeScannerWithConfiguration: configuration];
        
        UIImage* image = [ScanbotStorageUtils loadImage:imageUri];
        if (!image) {
            [self reportError:@"Image could not be loaded." toCommand:command];
            return;
        }
        
        NSArray<SBSDKBarcodeScannerResult *> *barcodeResults = [barcodeScanner detectBarCodesOnImage:image];
        SBSDKUIBarcodeFilter* barcodeFilter = extractBarcodeFilter(configuration);
        if (barcodeFilter != nil) {
            barcodeResults = filterBarcodeResults(barcodeResults, barcodeFilter);
        }
        
        NSDictionary *dictionary = @{
            @"status": @"OK",
            @"barcodes": jsonFromBarcodeResults(barcodeResults)
        };
        [self.commandDelegate sendPluginResult:
         [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dictionary]
                                    callbackId:callbackId];
    }];
}

- (void)detectBarcodesOnImages:(CDVInvokedUrlCommand*)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    NSString* callbackId = command.callbackId;
    
    NSDictionary* configuration = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!configuration) {
        configuration = @{};
    }
    
    NSArray* imageUris = [configuration objectForKey:@"imageFilesUris"];
    if (!imageUris || imageUris.count == 0) {
        [self reportError:@"No image uris specified" toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        // Additional parameters
        SBSDKBarcodeScanner* barcodeScanner = [self createBarcodeScannerWithConfiguration: configuration];

        NSMutableArray *results = [[NSMutableArray alloc] init];
        UIImage* tmpImage = NULL;
        NSArray<SBSDKBarcodeScannerResult *> *tmpBarcodeResults = NULL;
        
        for (NSString* imageUri in imageUris) {
            tmpImage = [ScanbotStorageUtils loadImage:imageUri];
            if (!tmpImage) {
                [results addObject: @{
                    @"imageFileUri": imageUri,
                    @"error": @"Cannot load given image."
                }];
                continue;
            }
            
            tmpBarcodeResults = [barcodeScanner detectBarCodesOnImage:tmpImage];
            SBSDKUIBarcodeFilter* barcodeFilter = extractBarcodeFilter(configuration);
            if (barcodeFilter != nil) {
                tmpBarcodeResults = filterBarcodeResults(tmpBarcodeResults, barcodeFilter);
            }
            
            [results addObject:@{
                @"imageFileUri": imageUri,
                @"barcodeResults": jsonFromBarcodeResults(tmpBarcodeResults)
            }];
        }
        
        [self.commandDelegate sendPluginResult: [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                              messageAsDictionary:@{ @"status": @"OK", @"results": results }]
                                    callbackId:callbackId];
    }];
}

- (void)detectBarcodesFromBytes:(CDVInvokedUrlCommand*)command {
    // unsupported on iOS (android only feature)
    [self reportError:@"Unsupported feature!" toCommand:command];
}

- (void)initializeSdk:(CDVInvokedUrlCommand *)command {
    
    NSDictionary *dictionary = @{
        @"interfaceOrientation": @{
            @"ALL": @(SBSDKOrientationLockNone),
            @"PORTRAIT": @(SBSDKOrientationLockPortrait),
            @"LANDSCAPE": @(SBSDKOrientationLockLandscape),
        },
        @"storageImageFormat": @{
            @"JPG": @(SBSDKImageFileFormatJPEG),
            @"PNG": @(SBSDKImageFileFormatPNG),
        },
        @"cameraPreviewMode": @{
            @"FILL_IN": @(SBSDKVideoContentModeFillIn),
            @"FIT_IN": @(SBSDKVideoContentModeFitIn),
        },
        @"barcodeImageGenerationType": @{
            @"NONE": @(SBSDKBarcodeImageGenerationTypeNone),
            @"VIDEO_FRAME": @(SBSDKBarcodeImageGenerationTypeFromVideoFrame),
            @"CAPTURED_IMAGE" :@(SBSDKBarcodeImageGenerationTypeCapturedImage),
        },
        @"textFilterStrategy": @{
            @"DOCUMENT": @(SBSDKTextFilterStrategyDocument),
            @"LC_DOT_MATRIX_DISPLAY": @(SBSDKTextFilterStrategyLCDotMatrixDisplay),
        },
        @"fileEncryptionMode": @{
            @"AES128": @(SBSDKAESEncrypterModeAES128),
            @"AES256": @(SBSDKAESEncrypterModeAES256)
        },
        @"engineMode": @{
            @"LEGACY": @(SBSDKBarcodeEngineModeLegacy),
            @"NEXT_GEN": @(SBSDKBarcodeEngineModeNextGen)
        },
        @"msiPlesseyChecksumAlgorithm": @{
            @"None": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmNone),
            @"Mod10": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10),
            @"Mod11IBM": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11IBM),
            @"Mod11NCR": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11NCR),
            @"Mod1010": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1010),
            @"Mod1110IBM": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110IBM),
            @"Mod1110NCR": @(SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110NCR)
        }
    };
    
    [ObjectMapper setEnumerationMapping:dictionary];
    
    // map config parameters and normalize some fields
    CDVScanbotSDKConfiguration* config = [[CDVScanbotSDKConfiguration alloc] init];
    [ObjectMapper populateInstance:config fromDictionary:[command.arguments firstObject]];
    config.licenseKey = [ObjectMapper normalizeJsonString:config.licenseKey];
    config.storageBaseDirectory = [ObjectMapper normalizeJsonFileURLAsString:config.storageBaseDirectory];
    
    [SharedConfiguration defaultConfiguration].loggingEnabled = config.loggingEnabled;
    [ScanbotSDK setLoggingEnabled:config.loggingEnabled];
    
    SBSDKDocumentDetectorMode mode = [ObjectMapper documentDetectorMode:[command.arguments firstObject]];
    [SBSDKDocumentDetector setDefaultDetectorMode:mode];
    
    BOOL hasLicense = NO;
    if (config.licenseKey) {
        [ScanbotSDK setLicense: config.licenseKey];
        hasLicense = YES;
    }
    
    // Check if the App has OCR data (ScanbotSDKOCRData.bundle) as resources provided:
    if ([SBSDKResourcesManager canInstallDefaultOCRResources]) {
        // if so, install those:
        [SBSDKResourcesManager installRequiredResourcesOfTypeIfNeeded:SBSDKResourceTypeOCR forceInstall:NO];
    }
    
    if (config.fileEncryptionPassword != nil && ![config.fileEncryptionPassword isEqualToString:@""]) {
        SBSDKAESEncrypter *encrypter = [[SBSDKAESEncrypter alloc] initWithPassword:config.fileEncryptionPassword mode:config.fileEncryptionMode];
        [ScanbotSDKUI setDefaultImageStoreEncrypter: encrypter];
        [ScanbotSDKUI setDefaultPDFEncrypter:encrypter];
    }
    
    // Optional custom SBSDKStorageLocation, can be nil for initialization of SBSDKUIPageFileStorage
    SBSDKStorageLocation* customStorageLocation = nil;
    if (config.storageBaseDirectory) {
        SBSDKLog(@"Using custom storage base directory: %@", config.storageBaseDirectory);
        NSURL* customStorageDirUrl = [NSURL URLWithString:config.storageBaseDirectory];
        customStorageLocation = [[SBSDKStorageLocation alloc] initWithBaseURL:customStorageDirUrl];
        
        SBSDKUIBarcodeImageStorage* storage = [[SBSDKUIBarcodeImageStorage alloc] initWithJPEGFileFormatAndCompressionQuality:          config.storageImageQuality location:customStorageLocation];
        [SBSDKUIBarcodeImageStorage setDefaultStorage:storage];
    }
    
    switch (config.storageImageFormat) {
        case SBSDKImageFileFormatJPEG:
            SBSDKUIPageFileStorage.defaultStorage = [[SBSDKUIPageFileStorage alloc] initWithJPEGFileFormatAndCompressionQuality:config.storageImageQuality location:customStorageLocation];
            break;
            
        case SBSDKImageFileFormatPNG:
            SBSDKUIPageFileStorage.defaultStorage = [[SBSDKUIPageFileStorage alloc] initWithImageFileFormat:SBSDKImageFileFormatPNG location:customStorageLocation];
            break;
            
        default:
        {
            CDVPluginResult *pluginResult = [self pluginResultError:@"Unsupported image file format."];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            return;
        }
    }
    
    [ScanbotSDK setSharedApplication:[UIApplication sharedApplication]];
    [SharedConfiguration defaultConfiguration].configuration = config;
    
    // verify we have a valid plugin storage directory
    if (![ScanbotStorageUtils pluginStorageDirectoryExists]) {
        CDVPluginResult *pluginResult = [self pluginResultError:@"Could not create the plugin storage directory."];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }
    
    NSString *callbackMessage = @"Scanbot SDK initialized.";
    if (!hasLicense) {
        callbackMessage = @"Scanbot SDK initialized. Trial mode activated. You can now test all features for 60 seconds.";
    }
    [SharedConfiguration defaultConfiguration].isSDKInitialized = YES;
    
    CDVPluginResult *pluginResult = [self pluginResultOk:callbackMessage];
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getImageData:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
        NSString *imageFileUri = params[@"imageFileUri"];
        NSURL *inputImageFileURL = [NSURL URLWithString:imageFileUri];
        NSData *data = [NSData dataWithContentsOfURL:inputImageFileURL];
        if (data == nil) {
            [self reportError:@"Image file not found" toCommand:command];
            return;
        }
        
        UIImage *image = [UIImage imageWithData:data];
        SBSDKAESEncrypter *encrypter = [ScanbotSDKUI defaultImageStoreEncrypter];
        
        if (image == nil && encrypter != nil) {
            data = [encrypter decryptData:data];
            image = [UIImage imageWithData:data];
        }
        if (image != nil && data != nil) {
            [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"base64ImageData": [data base64EncodedStringWithOptions:0]}] callbackId:command.callbackId];
        } else {
            [self reportError:@"Could not load or decrypt image data." toCommand:command];
        }
    }];
}

CDVInvokedUrlCommand *licenseFailureCommand;
- (void)setLicenseFailureHandler:(CDVInvokedUrlCommand *)command {
    
    licenseFailureCommand = command;
    [ScanbotSDK setLicenseFailureHandler:^(dooLicenseStatus status, dooFeature feature, NSString* errorMessage) {
        dispatch_async(dispatch_get_main_queue(), ^{
            CDVPluginResult *pluginResult = [self pluginResultObject:@{
                @"licenseStatus": [ScanbotSdkPlugin stringFromLicenseStatus:status],
                @"licenseFeature": [ScanbotSdkPlugin stringFromFeature:feature],
                @"licenseErrorMessage": errorMessage
            }];
            [pluginResult setKeepCallbackAsBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:licenseFailureCommand.callbackId];
        });
    }];
}

- (void)isLicenseValid:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    SBSDKLog(@"Validating ScanbotSDK license...");
    
    CDVPluginResult *pluginResult = nil;
    pluginResult = [self pluginResultObject:@{@"isLicenseValid":@([ScanbotSDK isLicenseValid])}];
#ifdef _CORDOVA_TEST_TARGET
    command.testCaseCompletionBlock(pluginResult);
#else
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
#endif
    SBSDKLog(@"Validation result: %i", [ScanbotSDK isLicenseValid]);
}

- (void)getLicenseInfo:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    SBSDKLog(@"Checking Scanbot SDK license status ...");
    
    double ms = [ScanbotSDK.licenseExpirationDate timeIntervalSince1970] * 1000;
    NSNumber *expirationMilliseconds = [NSNumber numberWithDouble:ms];
    
    CDVPluginResult *pluginResult = nil;
    pluginResult = [self pluginResultObject:@{
        @"info": @{
            @"isLicenseValid":@([ScanbotSDK isLicenseValid]),
            @"licenseStatus": [ScanbotSdkPlugin stringFromLicenseStatus:ScanbotSDK.licenseStatus],
            @"licenseExpirationDate": expirationMilliseconds
        }
    }];
    
#ifdef _CORDOVA_TEST_TARGET
    command.testCaseCompletionBlock(pluginResult);
#else
    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
#endif
    SBSDKLog(@"Validation result: %i", [ScanbotSDK isLicenseValid]);
}

+ (NSString*)descriptionFromLicenseStatus:(dooLicenseStatus)status {
    switch (status) {
        case LicenseStatusOkay:
            return @"License is valid";
        case LicenseStatusTrial:
            return @"No license installed, trial mode is active.";
        case LicenseStatusFailureExpired:
            return @"License error: License has expired.";
        case LicenseStatusFailureWrongOS:
            return @"License error: License does not include iOS support.";
        case LicenseStatusFailureCorrupted:
            return @"License error: License key string is corrupted. Please check the format.";
        case LicenseStatusFailureAppIDMismatch:
            return @"License error: License does not match to the bundle ID of this app.";
        case LicenseStatusFailureNotSet:
            return @"License error: No license installed.";
        default:
            return @"Unknown license status";
    }
}

+ (NSString*)stringFromLicenseStatus:(dooLicenseStatus)status {
    // String names are synced with the Android enum names
    switch (status) {
        case LicenseStatusOkay:
            return @"Okay";
        case LicenseStatusTrial:
            return @"Trial";
        case LicenseStatusFailureExpired:
            return @"Expired";
        case LicenseStatusFailureWrongOS:
            return @"WrongOS";
        case LicenseStatusFailureCorrupted:
            return @"Corrupted";
        case LicenseStatusFailureAppIDMismatch:
            return @"AppIDMismatch";
        case LicenseStatusFailureNotSet:
            return @"NotSet";
        default:
            return @"Unknown";
    }
}

+ (NSString*)stringFromFeature:(dooFeature)feature {
    // String names are synced with the Android enum names
    switch (feature) {
        case FeatureCheck:
            return @"Check";
        case FeatureOCR:
            return @"OCR";
        case FeatureQRCode:
            return @"QRCode";
        case FeatureNoFeature:
            return @"NoFeature";
        case FeatureCloudUpload:
            return @"CloudUpload";
        case FeaturePDFCreation:
            return @"PDFCreation";
        case FeatureW2Detection:
            return @"W2Detection";
        case FeatureEdgeDetection:
            return @"EdgeDetection";
        case FeatureCreditCardRecognition:
            return @"CreditCardRecognition";
        case FeatureDataIntelligence:
            return @"DataIntelligence";
        case FeatureMRZRecognition:
            return @"MRZRecognition";
        case FeatureDisabilityCertRecognition:
            return @"MedicalCertRecognition";
        case FeatureEdgeDetectionUI:
            return @"EdgeDetectionUI";
        case FeatureEHICRecognition:
            return @"EHICRecognition";
        case FeatureImageProcessing:
            return @"ImageProcessing";
        case FeatureInvoiceDetection:
            return @"InvoiceDetection";
        case FeatureMultipleObjectsDetection:
            return @"MultipleObjectsDetection";
        case FeaturePayformDetection:
            return @"PayformDetection";
        case FeatureTextOrientationDetection:
            return @"TextOrientationDetection";
        default:
            return @"Unknown";
    }
}

- (void)detectDocument:(NSString*)imageFileUri withCallback:(void (^)(NSString* error, NSDictionary* response))callback {
    SBSDKLog(@"Loading image from path: %@", imageFileUri);
    UIImage *image = [ScanbotStorageUtils loadImage:imageFileUri];
    
    if (!image) {
        NSString *loadingErrorString = @"Document detection failed. Input image file does not exist.";
        callback(loadingErrorString, nil);
        return;
    }
    
    image = [image sbsdk_imageWithNormalizedOrientation];
    SBSDKLog(@"Image loaded: %@", image);
    
    SBSDKLog(@"Creating SBSDKDocumentDetector instance ...");
    SBSDKDocumentDetector *detector = [SBSDKDocumentDetector new];
    SBSDKDocumentDetectorResult *result = [detector detectDocumentPolygonOnImage:image
                                                                visibleImageRect:CGRectZero
                                                                smoothingEnabled:YES
                                                      useLiveDetectionParameters:NO];
    
    NSString *outputImageFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"jpg"];
    NSURL *outputImageURL = [NSURL fileURLWithPath:outputImageFilePath];
    CGFloat compressionQuality = [SharedConfiguration defaultConfiguration].configuration.storageImageQuality / 100.;
    
    if (result.polygon != nil && (result.status == SBSDKDocumentDetectionStatusOK ||
                                  result.status == SBSDKDocumentDetectionStatusOK_SmallSize ||
                                  result.status == SBSDKDocumentDetectionStatusOK_BadAngles ||
                                  result.status == SBSDKDocumentDetectionStatusOK_BadAspectRatio)) {
        [SBSDKImageProcessor warpImage:image
                               polygon:result.polygon
                            completion:^(BOOL finished, NSError * _Nullable error, NSDictionary<NSString *,NSObject *> * _Nullable resultInfo) {
            if (finished && !error) {
                SBSDKLog(@"Got warpImage result");
                NSData *imageData = UIImageJPEGRepresentation((UIImage *)resultInfo[SBSDKResultInfoDestinationImageKey], compressionQuality);
                [imageData writeToFile:outputImageFilePath
                            atomically:YES];
                NSDictionary *callbackResult = @{@"documentImageFileUri":outputImageURL.absoluteString,
                                                 @"detectionResult":[result.polygon detectionStatusString],
                                                 @"polygon":[result.polygon polygonPoints]};
                
                callback(nil, callbackResult);
            } else {
                callback(error.localizedDescription, nil);
            }
        }];
    } else {
        NSString *detectionStatusString = [[SBSDKPolygon new] detectionStatusStringFromSBSDKStatus:SBSDKDocumentDetectionStatusError_NothingDetected];
        SBSDKLog(@"No acceptable polygon found. Result.status = %d", [result status]);
        NSDictionary *callbackResult = @{@"imageFileUri":[NSNull null],
                                         @"detectionResult":detectionStatusString,
                                         @"polygon":[NSArray array]};
        callback(nil, callbackResult);
    }
}

- (void)detectDocument:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    NSString *imageFilePath = params[@"imageFileUri"];
    
    [self detectDocument:imageFilePath withCallback:^(NSString *error, NSDictionary *response) {
        if (error) {
            CDVPluginResult *pluginResult = [self pluginResultError:error];
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
            SBSDKLog(error);
        } else {
            CDVPluginResult *pluginResult = [self pluginResultObject:response];
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
        }
    }];
}

- (void)detectDocumentOnPage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    SBSDKUIPage *page = pageFromDictionary(params[@"page"]);
    if (!page) {
        [self reportError:@"'page' is a required argument" toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        [page applyDocumentDetection];
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"page": dictionaryFromPage(page)}]
                                    callbackId:command.callbackId];
    }];
}

- (void)applyImageFilterOnPage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    SBSDKUIPage *page = pageFromDictionary(params[@"page"]);
    if (!page) {
        [self reportError:@"'page' is a required argument" toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        SBSDKImageFilterType imageFilter = filterIdFromFilterNameString(params[@"imageFilter"]);
        page.filter = imageFilter;
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"page": dictionaryFromPage(page)}]
                                    callbackId:command.callbackId];
    }];
}

- (void)rotatePage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    SBSDKUIPage *page = pageFromDictionary(params[@"page"]);
    if (!page) {
        [self reportError:@"'page' is a required argument" toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        NSNumber* times = params[@"times"];
        [page rotateClockwise:-[times integerValue]];
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"page": dictionaryFromPage(page)}]
                                    callbackId:command.callbackId];
    }];
}

- (void)getFilteredDocumentPreviewUri:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    SBSDKUIPage *page = pageFromDictionary(params[@"page"]);
    if (!page) {
        [self reportError:@"'page' is a required argument" toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        SBSDKImageFilterType imageFilter = filterIdFromFilterNameString(params[@"imageFilter"]);
        NSURL* url = [page documentPreviewImageURLUsingFilter:imageFilter];
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"imageFileUri": uriWithMinihash(url)}]
                                    callbackId:command.callbackId];
    }];
}

- (void)applyImageFilter:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    NSString *imageFilePath = params[@"imageFileUri"];
    NSString *outputImageFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"jpg"];
    NSURL *inputImageFileURL = [NSURL URLWithString:imageFilePath];
    __block NSURL *outputImageFIleURL = [NSURL fileURLWithPath:outputImageFilePath];
    
    CGFloat compressionQuality = params.qualityValue;
    [SBSDKImageProcessor filterImage:[UIImage imageWithData:[NSData dataWithContentsOfURL:inputImageFileURL]]
                              filter:filterIdFromFilterNameString(params[@"imageFilter"])
                          completion:^(BOOL finished, NSError * _Nullable error, NSDictionary<NSString *,NSObject *> * _Nullable resultInfo) {
        if (finished && !error) {
            NSData *imageData = UIImageJPEGRepresentation((UIImage *)resultInfo[SBSDKResultInfoDestinationImageKey], compressionQuality);
            [imageData writeToFile:outputImageFilePath
                        atomically:YES];
            SBSDKLog(@"Got filterImage result");
            CDVPluginResult *pluginResult = [self pluginResultObject:@{@"imageFileUri":outputImageFIleURL.absoluteString}];
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
        } else {
            CDVPluginResult *pluginResult = [self pluginResultError:error.localizedDescription];
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
        }
    }];
}

- (void)rotateImage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    NSString *imageFileUri = params.imageFileUriValue;
    NSInteger rotationDegrees = params.degreesValue;
    CGFloat quality = params.qualityValue;
    NSString *outputImageFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"jpg"];
    SBSDKLog(@"imageFileUri: %@", imageFileUri);
    SBSDKLog(@"degrees: %i", rotationDegrees);
    SBSDKLog(@"quality: %f", quality);
    
    [self.commandDelegate runInBackground:^{
        UIImage *inputImage = [ScanbotStorageUtils loadImage:imageFileUri];
        
        CDVPluginResult *pluginResult = nil;
        if (inputImage) {
            UIImage *outputImage = [inputImage sbsdk_imageRotatedByDegrees:rotationDegrees];
            if ([ScanbotStorageUtils saveImage:outputImageFilePath
                                         image:outputImage
                                       quality:quality]) {
                pluginResult = [self pluginResultObject:@{@"imageFileUri":[NSURL fileURLWithPath:outputImageFilePath].absoluteString}];
            } else {
                pluginResult = [self pluginResultError:@"Save image failed"];
            }
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
            
        } else {
            pluginResult = [self pluginResultError:@"Input image not found"];
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
            
        }
    }];
}

- (void)createPdf:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    if (![params validateArrayParameter:@"images" withErrorMessage:@"At least one image must be present."]) {
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        NSArray<NSString *> *imageFileUris = params[@"images"];
        NSMutableArray* imageFileURLs = [NSMutableArray arrayWithCapacity:[imageFileUris count]];
        for (NSString* uriStr in imageFileUris) {
            [imageFileURLs addObject:[NSURL URLWithString:uriStr]];
        }
        SBSDKIndexedImageStorage *tempStorage = [self tempImageStorageFromFilesList:imageFileURLs];
        
        NSString *outputPdfFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"pdf"];
        SBSDKLog(@"PDF output file path: %@", outputPdfFilePath);
        NSURL *pdfOutputURL = [NSURL fileURLWithPath:outputPdfFilePath];
        
        // optional PDF encryptor, can be nil (see SDK initialization)
        SBSDKAESEncrypter *pdfEncrypter = [ScanbotSDKUI defaultPDFEncrypter];
        
        [SBSDKPDFRenderer renderImageStorage:tempStorage
                            copyImageStorage:NO
                                    indexSet:nil
                                withPageSize:pageSizeFromPagesizeNameString(params[@"pageSize"])
                                   encrypter:pdfEncrypter
                                      output:pdfOutputURL
                           completionHandler:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
            dispatch_async(dispatch_get_main_queue(), ^{
                SBSDKLog(@"Got PDF renderer result");
                // cleaning up the temp storage dir!
                [tempStorage removeAllImages];
                CDVPluginResult *pluginResult = nil;
                if (finished && !error) {
                    pluginResult = [self pluginResultObject:@{@"pdfFileUri":pdfOutputURL.absoluteString}];
                } else {
                    pluginResult = [self pluginResultError:error.localizedDescription];
                }
#ifdef _CORDOVA_TEST_TARGET
                command.testCaseCompletionBlock(pluginResult);
#else
                [self.commandDelegate sendPluginResult:pluginResult
                                            callbackId:command.callbackId];
#endif
            });
            
        }];
    }];
}

- (void)writeTiff:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    if (![params validateArrayParameter:@"images" withErrorMessage:@"At least one image must be present."]) {
        return;
    }
    NSArray<NSString *> *imageFilePaths = params[@"images"];
    NSMutableArray* uris = [NSMutableArray arrayWithCapacity:[imageFilePaths count]];
    for (NSString* uriStr in imageFilePaths) {
        [uris addObject:[NSURL URLWithString:uriStr]];
    }
    
    [self.commandDelegate runInBackground:^{
        NSString *outputTiffFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"tiff"];
        SBSDKLog(@"TIFF output file path: %@", outputTiffFilePath);
        
        NSURL* outputTiffFileUri = [NSURL fileURLWithPath:outputTiffFilePath];
        
        BOOL binarized = params[@"oneBitEncoded"] ? [params[@"oneBitEncoded"] boolValue] : FALSE;
        
        NSInteger dpi = params[@"dpi"] ? [params[@"dpi"] intValue] : 200;
        SBSDKTIFFImageWriterCompressionOptions defaultCompression = (binarized ? COMPRESSION_CCITT_T6 : COMPRESSION_ADOBE_DEFLATE);
        SBSDKTIFFImageWriterCompressionOptions compression = tiffCompressionOptionFromStringName(params[@"compression"], defaultCompression);
        
        // validate compression type compatibility:
        // check against compression types, which are compatible only with binarized images (1-bit encoded).
        if (!binarized && (compression == COMPRESSION_CCITTRLE || compression == COMPRESSION_CCITTFAX3 || compression == COMPRESSION_CCITT_T4 ||
                           compression == COMPRESSION_CCITTFAX4 || compression == COMPRESSION_CCITT_T6 || compression == COMPRESSION_CCITTRLEW)) {
            [self.commandDelegate sendPluginResult:[self pluginResultError:@"Incompatible compression type. The given compression type is only applicable to binarized images."]
                                        callbackId:command.callbackId];
            return;
        }
        
        SBSDKTIFFImageWriterParameters *tiffParams = [SBSDKTIFFImageWriterParameters defaultParameters];
        tiffParams.binarize = binarized;
        tiffParams.compression = compression;
        tiffParams.dpi = dpi;
        
        BOOL success = false;
        
        SBSDKAESEncrypter *encrypter = [ScanbotSDKUI defaultPDFEncrypter];
        if (encrypter != NULL) {
            NSArray<UIImage*>* decryptedImages = [self decryptedImages:uris];
            if (decryptedImages != NULL) {
                success = [SBSDKTIFFImageWriter writeTIFF:decryptedImages
                                                  fileURL:outputTiffFileUri
                                                encrypter:encrypter
                                               parameters:tiffParams];
            }
        } else {
            success = [SBSDKTIFFImageWriter writeTIFFFromURLs:uris
                                                      fileURL:outputTiffFileUri
                                                   parameters:tiffParams];
        }
        
        if (!success) {
            [self.commandDelegate sendPluginResult:[self pluginResultError:@"TIFF file creating failed"] callbackId:command.callbackId];
        }
        
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"tiffFileUri": [outputTiffFileUri absoluteString]}]
                                    callbackId:command.callbackId];
    }];
}

- (NSArray<UIImage*>*)decryptedImages: (NSArray<NSURL*>*) urls {
    
    NSMutableArray *resultedImages = [[NSMutableArray alloc] init];
    
    SBSDKAESEncrypter* encrypter = [ScanbotSDKUI defaultPDFEncrypter];
    if (encrypter == NULL) {
        return resultedImages;
    }
    
    NSData* tmpData = NULL;
    NSData* decryptedData = NULL;
    UIImage* image = NULL;
    
    for (NSURL* url in urls) {
        tmpData = [[NSData alloc] initWithContentsOfURL:url];
        if (tmpData == NULL) { continue; }
        
        decryptedData = [encrypter decryptData:tmpData];
        if (decryptedData == NULL) { continue; }
        
        image = [[UIImage alloc] initWithData:decryptedData];
        if (image == NULL) { continue; }
        
        [resultedImages addObject:image];
    }
    
    return resultedImages;
}

- (void)cleanup:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        SBSDKLog(@"Cleaning SBSDKUIPageFileStorage ...");
        [SBSDKUIPageFileStorage.defaultStorage removeAll];
        
        SBSDKLog(@"Cleaning the plugin storage directory ...");
        NSError *cleanupError = [ScanbotStorageUtils removeAllFilesFromPluginStorageDirectory];
        
        SBSDKLog(@"Cleaning SBSDKUIBarcodeImageStorage ...");
        [[SBSDKUIBarcodeImageStorage defaultStorage] removeAll];
        
        CDVPluginResult *pluginResult = nil;
        if (!cleanupError) {
            pluginResult = [self pluginResultOk:@"Cleanup done."];
        } else {
            pluginResult = [self pluginResultError:cleanupError.localizedDescription];
        }
        
#ifdef _CORDOVA_TEST_TARGET
        command.testCaseCompletionBlock(pluginResult);
#else
        [self.commandDelegate sendPluginResult:pluginResult
                                    callbackId:command.callbackId];
#endif
    }];
}

- (NSArray<NSString *> *)checkMissingLanguages:(NSArray<NSString *> *)languages {
    NSArray *installedLanguages = [SBSDKOpticalTextRecognizer installedLanguages];
    NSMutableArray<NSString *> *missingLanguges = [NSMutableArray array];
    for (NSString *languageCode in languages) {
        if (![installedLanguages containsObject:languageCode]) {
            [missingLanguges addObject:languageCode];
        }
    }
    return missingLanguges;
}

- (NSString *)missingLanguagesStringFromArray:(NSArray<NSString *> *)missingLanguagesArray {
    NSString *arrayRepresentation = @"";
    for (NSInteger index = 0; index < missingLanguagesArray.count; index++) {
        NSString *languageCode = missingLanguagesArray[index];
        arrayRepresentation = [arrayRepresentation stringByAppendingFormat:@"\"%@\"", languageCode];
        if (index < missingLanguagesArray.count - 1) {
            arrayRepresentation = [arrayRepresentation stringByAppendingString:@", "];
        }
    }
    return [NSString stringWithFormat:@"Missing OCR language files for languages: [%@]", arrayRepresentation];
}

- (void)performOcr:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    if (![params validateArrayParameter:@"images" withErrorMessage:@"At least one image must be present."] ||
        ![params validateArrayParameter:@"languages" withErrorMessage:@"At least one language must be specified."] ||
        ![params validateParameter:@"outputFormat"]) {
        return;
    }
    
    NSArray *languages = params[@"languages"];
    NSArray *missingLanguages = [self checkMissingLanguages:languages];
    if (missingLanguages.count > 0) {
        CDVPluginResult *pluginResult = [self pluginResultError:[self missingLanguagesStringFromArray:missingLanguages]];
#ifdef _CORDOVA_TEST_TARGET
        command.testCaseCompletionBlock(pluginResult);
#else
        [self.commandDelegate sendPluginResult:pluginResult
                                    callbackId:command.callbackId];
#endif
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        NSArray<NSString *> *imageFileUris = params[@"images"];
        NSMutableArray* imageFileURLs = [NSMutableArray arrayWithCapacity:[imageFileUris count]];
        for (NSString* uriStr in imageFileUris) {
            [imageFileURLs addObject:[NSURL URLWithString:uriStr]];
        }
        SBSDKIndexedImageStorage *tempStorage = [self tempImageStorageFromFilesList:imageFileURLs];
        
        NSString *langString = languages.firstObject;
        for (NSInteger index = 1; index < languages.count; ++index) {
            langString = [NSString stringWithFormat:@"%@+%@", langString, languages[index]];
        }
        
        CDVOCRCompletionAdapter *adapter = [CDVOCRCompletionAdapter adapterWithOutputFormat:params[@"outputFormat"]];
        
        // optional PDF encryptor, can be nil (see SDK initialization)
        SBSDKAESEncrypter *pdfEncrypter = [ScanbotSDKUI defaultPDFEncrypter];
        
        [SBSDKOpticalTextRecognizer recognizeText:tempStorage
                                 copyImageStorage:NO
                                         indexSet:nil
                                   languageString:langString
                                        encrypter:pdfEncrypter
                                     pdfOutputURL:adapter.outputPDFURL
                                       completion:[adapter adaptBlock:^(NSDictionary *resultDict, NSError *error) {
            SBSDKLog(@"Got OCR result");
            // cleaning up the temp storage dir!
            [tempStorage removeAllImages];
            CDVPluginResult *pluginResult = nil;
            if (!error) {
                pluginResult = [self pluginResultObject:resultDict];
            } else {
                pluginResult = [self pluginResultError:error.localizedDescription];
            }
#ifdef _CORDOVA_TEST_TARGET
            command.testCaseCompletionBlock(pluginResult);
#else
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
#endif
        }]];
    }];
}

- (void)getOcrConfigs:(CDVInvokedUrlCommand *)command {
    [self.commandDelegate runInBackground:^{
        NSMutableDictionary *resultDict = [NSMutableDictionary dictionary];
        
        NSURL *languageDataPathURL = [SBSDKResourcesManager customOCRLanguagesDataURL];
        resultDict[@"languageDataPath"] = [languageDataPathURL absoluteString];
        resultDict[@"installedLanguages"] = [SBSDKOpticalTextRecognizer installedLanguages];
        
        CDVPluginResult *pluginResult = [self pluginResultObject:resultDict];
        [self.commandDelegate sendPluginResult:pluginResult
                                    callbackId:command.callbackId];
    }];
}

- (void)createPage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    
    [self.commandDelegate runInBackground:^{
        NSString* imageFileUri = params[@"originalImageFileUri"];
        UIImage* image = [ScanbotStorageUtils loadImage:imageFileUri];
        if (!image) {
            [self reportError:@"Could not load image from given file." toCommand:command];
            return;
        }
        image = [image sbsdk_imageWithNormalizedOrientation];
        
        NSUUID* pageId = [SBSDKUIPageFileStorage.defaultStorage addImage:image];
        SBSDKUIPage* page = [[SBSDKUIPage alloc] initWithPageFileID:pageId polygon:nil];
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"page": dictionaryFromPage(page)}]
                                    callbackId:command.callbackId];
    }];
}

- (void)setDocumentImage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    
    [self.commandDelegate runInBackground:^{
        SBSDKUIPage* page = pageFromDictionary(params[@"page"]);
        if (!page) {
            [self reportError:@"'page' is a required argument" toCommand:command];
            return;
        }
        
        NSString* documentImageUri = params[@"documentImageFileUri"];
        UIImage* image = [ScanbotStorageUtils loadImage:documentImageUri];
        if (!documentImageUri) {
            [self reportError:@"Image not found." toCommand:command];
            return;
        }
        
        NSError* error;
        [SBSDKUIPageFileStorage.defaultStorage setImage:image
                                  forExistingPageFileID:page.pageFileUUID
                                           pageFileType:SBSDKUIPageFileTypeDocument
                                                  error:&error];
        
        if (error) {
            [self reportError:error.localizedDescription toCommand:command];
        } else {
            [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"page": dictionaryFromPage(page)}]
                                        callbackId:command.callbackId];
        }
    }];
}

- (void)removePage:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    SBSDKUIPage *page = pageFromDictionary(params[@"page"]);
    if (!page) {
        [self reportError:@"'page' is a required argument" toCommand:command];
        return;
    }
    [SBSDKUIPageFileStorage.defaultStorage removePageFileID:page.pageFileUUID];
    
    [self.commandDelegate sendPluginResult:[self pluginResultOk:@"Removed"]
                                callbackId:command.callbackId];
}

- (void)estimateBlur:(CDVInvokedUrlCommand *)command {
    NSString* callbackId = command.callbackId;
    
    NSDictionary* configuration = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!configuration) {
        configuration = @{};
    }
    NSString* imageUri = [configuration objectForKey:@"imageFileUri"];
    if (imageUri == nil) {
        [self reportError:@"Missing argument value for 'imageFileUri'." toCommand:command];
        return;
    }
    
    [self.commandDelegate runInBackground:^{
        UIImage* image = [ScanbotStorageUtils loadImage:imageUri];
        
        // optional image encryptor, can be nil (see SDK initialization)
        SBSDKAESEncrypter *imageEncrypter = [ScanbotSDKUI defaultImageStoreEncrypter];
        
        if (image == nil && imageEncrypter != nil) {
            // might be an encrypted image, try to decrypt
            NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:imageUri]];
            data = [imageEncrypter decryptData:data];
            image = [UIImage imageWithData:data];
        }
        
        if (!image) {
            [self reportError:@"Image could not be loaded." toCommand:command];
            return;
        }
        double blur = [[[SBSDKBlurrinessEstimator alloc] init] estimateImageBlurriness:image];
        NSDictionary *dictionary = @{ @"status": @"OK", @"blur": [NSNumber numberWithDouble:blur] };
        
        [self.commandDelegate sendPluginResult:
         [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dictionary]
                                    callbackId:callbackId];
    }];
}

- (void)refreshImageUris:(CDVInvokedUrlCommand *)command {
    if (![self checkSDKInitializationWithCommand:command]) {
        return;
    }
    
    HandyJSONParameters *params = [HandyJSONParameters JSONParametersWithCordovaCommand:command];
    NSArray<SBSDKUIPage *> *sdkPages = pagesFromJsonArray(params[@"pages"]);
    if (sdkPages == nil || [sdkPages count] == 0) {
        [self reportError:@"'pages' is a required argument" toCommand:command];
        return;
    }
    
    // As the location of the Application Support folder can change (e.g. on app update), we simply recreate
    // Page objects here to get a refreshed absolute file paths of the images.
    // (under the hood the native iOS SDK works with relative paths and is able to handle variable Application Support location)
    [self.commandDelegate runInBackground:^{
        NSMutableArray* refreshedPages = [NSMutableArray new];
        for (SBSDKUIPage *page in sdkPages) {
            [refreshedPages addObject:dictionaryFromPage(page)];
        }
        [self.commandDelegate sendPluginResult:[self pluginResultObject:@{@"pages": refreshedPages}]
                                    callbackId:command.callbackId];
    }];
}

- (SBSDKIndexedImageStorage *)tempImageStorageFromFilesList:(NSArray<NSURL *> *)imageFileURLs {
    NSString* tempSubFolderName = [[[NSUUID UUID] UUIDString] lowercaseString];
    NSString* pluginStorageDirectoryPath = [ScanbotStorageUtils pluginStorageDirectoryPath];
    NSURL *tempStorageDirUrl = [[NSURL alloc] initFileURLWithPath: [NSString stringWithFormat:@"%@/%@", pluginStorageDirectoryPath, tempSubFolderName]];
    SBSDKStorageLocation *location = [[SBSDKStorageLocation alloc] initWithBaseURL:tempStorageDirUrl];
    
    // optional image encryptor, can be nil (see SDK initialization)
    SBSDKAESEncrypter *imageEncrypter = [ScanbotSDKUI defaultImageStoreEncrypter];
    
    return [[SBSDKIndexedImageStorage alloc] initWithStorageLocation:location
                                                          fileFormat:SBSDKImageFileFormatJPEG
                                                       withEncrypter:imageEncrypter
                                                 encryptedImagesURLs:imageFileURLs];
}

- (CDVPluginResult*)pluginResultOk:(NSString*)resultData {
    return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                         messageAsDictionary:@{@"status": @"OK", @"message": resultData}];
}

- (CDVPluginResult*)pluginResultObject:(NSDictionary*)resultData {
    NSMutableDictionary* resultWithStatus = @{@"status": @"OK"}.mutableCopy;
    [resultWithStatus addEntriesFromDictionary:resultData];
    return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                         messageAsDictionary:resultWithStatus];
}

- (CDVPluginResult*)pluginResultError:(NSString*)errorMessage {
    return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                         messageAsDictionary:@{@"status": @"ERROR", @"message": errorMessage}];
}

- (void)reportError:(NSString*)message toCommand:(CDVInvokedUrlCommand *)command {
    [self.commandDelegate sendPluginResult:[self pluginResultError:message] callbackId:command.callbackId];
}

@end


