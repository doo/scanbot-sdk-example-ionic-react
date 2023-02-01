//
//  ScanbotSdkUiPlugin.m
//  ScanbotSDKCordova
//
//  Created by Stefan Dragnev on 11.06.18.
//  Copyright © 2018 doo. All rights reserved.
//

#import "ScanbotSdkUiPlugin.h"
#import "ObjectMapper.h"
#import "JSONMappings.h"
#import "BarcodeMapping.h"
#import "GenericDocumentRecognizerMapping.h"
#import "UIColor+JSON.h"
#import "ScanbotSdkPlugin.h"

void runOnMainThread(void (^function)(void)) {
    dispatch_async(dispatch_get_main_queue(), function);
}

void runInBackground(void (^function)(void)) {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), function);
}

@implementation ScanbotSdkUiPlugin

- (void)reportError:(NSString*)errorString toCommand:(CDVInvokedUrlCommand*)command {
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:errorString];
    [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
}

- (void)startDocumentScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex: 0] : NULL;
    if (!arguments) {
        arguments = @{};
    }

    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];

    SBSDKUIDocumentScannerUIConfiguration* uiConfig = [[SBSDKUIDocumentScannerUIConfiguration alloc] init];
    SBSDKUIDocumentScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUIDocumentScannerBehaviorConfiguration alloc] init];
    SBSDKUIDocumentScannerTextConfiguration* textConfig = [[SBSDKUIDocumentScannerTextConfiguration alloc] init];

    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    SBSDKUIDocumentScannerAccessibilityConfiguration* accessibilityConfiguration = [[SBSDKUIDocumentScannerAccessibilityConfiguration alloc] init];
    NSDictionary* accessibilityConfigurationMap = [configuration objectForKey:@"accessibilityConfiguration"];
    if (accessibilityConfigurationMap) {
        @try {
            [ObjectMapper populateInstance:accessibilityConfiguration fromDictionary:accessibilityConfigurationMap];
            textConfig.accessibilityConfiguration = accessibilityConfiguration;
        }
        @catch (NSException* ex) {
            return;
        }
    }
    
    // Need to manually extract because of naming disparity between iOS and Android
    NSString* pageCounterButtonAccessibilityHint = [accessibilityConfigurationMap objectForKey:@"pageCounterAccessibilityHint"];
    if (pageCounterButtonAccessibilityHint != nil && pageCounterButtonAccessibilityHint.length > 0) {
        textConfig.accessibilityConfiguration.pageCounterButtonAccessibilityHint = pageCounterButtonAccessibilityHint;
    }
    
    SBSDKUIDocumentScannerConfiguration* config = [[SBSDKUIDocumentScannerConfiguration alloc] initWithUIConfiguration:uiConfig textConfiguration:textConfig behaviorConfiguration:behaviorConfig cameraConfiguration:[[SBSDKUICameraConfiguration alloc] init]];

    DocumentScannerPromiseProxy* delegate = [[DocumentScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];

    SBSDKUIDocumentScannerViewController* viewController = [SBSDKUIDocumentScannerViewController createNewWithDocument: nil configuration:config andDelegate:delegate];
    
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startGenericDocumentRecognizer:(CDVInvokedUrlCommand *)command {
    NSDictionary *arguments = command.arguments.count > 0 ? command.arguments[0] : nil;
    if (!arguments) {
        arguments = @{};
    }
    NSDictionary *configuration = arguments[@"uiConfigs"];
    SBSDKUIGenericDocumentRecognizerUIConfiguration *uiConfig = [[SBSDKUIGenericDocumentRecognizerUIConfiguration alloc] init];
    SBSDKUIGenericDocumentRecognizerBehaviorConfiguration *behaviorConfig = [[SBSDKUIGenericDocumentRecognizerBehaviorConfiguration alloc] init];
    SBSDKUIGenericDocumentRecognizerTextConfiguration *textConfig = [[SBSDKUIGenericDocumentRecognizerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration *cameraConfig = [[SBSDKUICameraConfiguration alloc] init];
    
    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:cameraConfig fromDictionary:configuration];
    }
    @catch (NSException *exception) {
        [self reportError:[exception reason] toCommand:command];
        return;
    }
    
    NSArray<SBSDKGenericDocumentRootType*> *genericTypes = extractAcceptedDocumentTypes(configuration);
    SBSDKUIDocumentType* documentType = [[SBSDKUIDocumentType alloc] initWithGenericTypes:genericTypes];
    behaviorConfig.documentType = documentType;
    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    SBSDKUIGenericDocumentRecognizerConfiguration *config = [[SBSDKUIGenericDocumentRecognizerConfiguration alloc] initWithUIConfiguration:uiConfig textConfiguration:textConfig behaviorConfiguration:behaviorConfig cameraConfiguration:cameraConfig];
    
    // We replace the default field titles with those defined by the user
    NSMutableDictionary<NSString*, NSString*>* fieldProperties = extractGenericDocumentRecognizerFieldProperties(configuration, genericTypes);
    for (NSString* key in fieldProperties.allKeys) {
        config.textConfiguration.fieldTypeDisplayTexts[key] = fieldProperties[key];
    }

    // We do the same thing with the default document type titles
    NSMutableDictionary<NSString*, NSString*>* docProperties = extractGenericDocumentRecognizerDocumentProperties(configuration, genericTypes);
    for (NSString* key in docProperties.allKeys) {
        config.textConfiguration.documentTypeDisplayTexts[key] = docProperties[key];
    }
    
    GenericDocumentRecognizerPromiseProxy *delegate = [[GenericDocumentRecognizerPromiseProxy alloc] initWithDelegate:self.commandDelegate
                                                                                andCallbackId:command.callbackId];
    
    SBSDKUIGenericDocumentRecognizerViewController *viewController = [SBSDKUIGenericDocumentRecognizerViewController createNewWithConfiguration:config
                                                                                                            andDelegate:delegate];
    
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}


- (void)startCheckRecognizer:(CDVInvokedUrlCommand *)command {
    NSDictionary *arguments = command.arguments.count > 0 ? command.arguments[0] : nil;
    if (!arguments) {
        arguments = @{};
    }
    NSDictionary *configuration = arguments[@"uiConfigs"];
    SBSDKUICheckRecognizerUIConfiguration *uiConfig = [[SBSDKUICheckRecognizerUIConfiguration alloc] init];
    SBSDKUICheckRecognizerBehaviorConfiguration *behaviorConfig = [[SBSDKUICheckRecognizerBehaviorConfiguration alloc] init];
    SBSDKUICheckRecognizerTextConfiguration *textConfig = [[SBSDKUICheckRecognizerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration* cameraConfig = extractCameraConfiguration(configuration);

    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:cameraConfig fromDictionary:configuration];
    }
    @catch (NSException *exception) {
        [self reportError:[exception reason] toCommand:command];
        return;
    }

    NSArray<SBSDKCheckDocumentRootType*> *checkTypes = extractAcceptedCheckTypes(configuration);
    behaviorConfig.acceptedCheckStandards = checkTypes;
    
    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    SBSDKUICheckRecognizerConfiguration *config = [[SBSDKUICheckRecognizerConfiguration alloc]
                                                   initWithUIConfiguration:uiConfig
                                                   textConfiguration:textConfig
                                                   behaviorConfiguration:behaviorConfig
                                                   cameraConfiguration:cameraConfig];
    
    CheckRecognizerPromiseProxy *delegate = [[CheckRecognizerPromiseProxy alloc] initWithDelegate:self.commandDelegate
                                                                                    andCallbackId:command.callbackId];
    
    SBSDKUICheckRecognizerViewController *viewController = [SBSDKUICheckRecognizerViewController createNewWithConfiguration:config
                                                                                                                andDelegate:delegate];
    
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startCroppingScreen:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }

    NSDictionary* page = [arguments objectForKey:@"page"];
    if (!page) {
        [self reportError:@"page is a required argument" toCommand:command];
        return;
    }

    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUICroppingScreenTextConfiguration* textConfig = [[SBSDKUICroppingScreenTextConfiguration alloc] init];
    SBSDKUICroppingScreenUIConfiguration* uiConfig = [[SBSDKUICroppingScreenUIConfiguration alloc] init];
    SBSDKUICroppingScreenBehaviorConfiguration *behaviorConfig = [[SBSDKUICroppingScreenBehaviorConfiguration alloc] init];
    
    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }
    
    SBSDKUICroppingScreenAccessibilityConfiguration* accessibilityConfiguration = [[SBSDKUICroppingScreenAccessibilityConfiguration alloc] init];
    NSDictionary* accessibilityConfigurationMap = [configuration objectForKey:@"accessibilityConfiguration"];
    if (accessibilityConfigurationMap) {
        @try {
            [ObjectMapper populateInstance:accessibilityConfiguration fromDictionary:accessibilityConfigurationMap];
            textConfig.accessibilityConfiguration = accessibilityConfiguration;
        }
        @catch (NSException* ex) {
            return;
        }
    }

    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    SBSDKUICroppingScreenConfiguration* config = [[SBSDKUICroppingScreenConfiguration alloc] initWithUIConfiguration:uiConfig textConfiguration:textConfig behaviorConfiguration:behaviorConfig];
    
    CroppingScreenPromiseProxy* delegate = [[CroppingScreenPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];

    SBSDKUICroppingViewController* viewController = [SBSDKUICroppingViewController createNewWithPage:pageFromDictionary(page) withConfiguration:config andDelegate:delegate];
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startMrzScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }

    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUIMRZScannerUIConfiguration* uiConfig = [[SBSDKUIMRZScannerUIConfiguration alloc] init];
    SBSDKUIMRZScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUIMRZScannerBehaviorConfiguration alloc] init];
    SBSDKUIMRZScannerTextConfiguration* textConfig = [[SBSDKUIMRZScannerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration* cameraConfig = [[SBSDKUICameraConfiguration alloc] init];

    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    // Eddy: Once we provide the functionality to return images as result, we should change this "allowedInterfaceOrientations"
    // to "camera orientation lock" via "behaviorConfig.orientationLockMode = SBSDKOrientationLockXXX", like in Document Scanner.
    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];

    int finderWidth = [[configuration objectForKey:@"finderWidth"] intValue];
    int finderHeight = [[configuration objectForKey:@"finderHeight"] intValue];
    uiConfig.finderAspectRatio = [[SBSDKAspectRatio alloc] initWithWidth:finderWidth andHeight:finderHeight];
    
    SBSDKUIMRZScannerConfiguration* config = [[SBSDKUIMRZScannerConfiguration alloc] initWithUIConfiguration:uiConfig
                                                                                           textConfiguration:textConfig
                                                                                       behaviorConfiguration:behaviorConfig
                                                                                         cameraConfiguration:cameraConfig];

    MRZScannerPromiseProxy* delegate = [[MRZScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];

    
    SBSDKUIMRZScannerViewController* viewController = [SBSDKUIMRZScannerViewController createNewWithConfiguration:config andDelegate:delegate];
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startBarcodeScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }

    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUIBarcodeScannerUIConfiguration* uiConfig = [[SBSDKUIBarcodeScannerUIConfiguration alloc] init];
    SBSDKUIBarcodeScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUIBarcodeScannerBehaviorConfiguration alloc] init];
    SBSDKUIBarcodeScannerTextConfiguration* textConfig = [[SBSDKUIBarcodeScannerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration* cameraConfig = [[SBSDKUICameraConfiguration alloc] init];
    
    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    // Map Additional parameters
    behaviorConfig.additionalParameters = extractAdditionalParameters(configuration);
    
    SBSDKBarcodeDensity barcodeDensity = extractBarcodeDensity(configuration);
    behaviorConfig.additionalParameters.codeDensity = barcodeDensity;
    
    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];

    bool shouldWaitForGeneratedImage = behaviorConfig.barcodeImageGenerationType != SBSDKBarcodeImageGenerationTypeNone;
    BarcodeScannerPromiseProxy* delegate = [[BarcodeScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate
                                                                                  andCallbackId:command.callbackId
                                                                    shouldWaitForGeneratedImage:shouldWaitForGeneratedImage];
    @try {
        [ObjectMapper populateInstance:delegate fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }
    // Barcode Filter (at the moment used for UPC Extension filters)
    SBSDKUIBarcodeFilter* barcodeFilter = extractBarcodeFilter(configuration);
    if (barcodeFilter) {
        behaviorConfig.barcodeFilter = barcodeFilter;
    }
    behaviorConfig.additionalParameters = extractAdditionalParameters(configuration);
    
    behaviorConfig.acceptedMachineCodeTypes = extractBarcodeTypes(configuration);
    NSArray* acceptedDocumentTypes = extractBarcodeDocumentTypes(configuration);
    
    SBSDKUIBarcodeSelectionOverlayConfiguration* selectionOverlayConfiguration = NULL; // TODO: selection overlay
    
    SBSDKUIBarcodeScannerConfiguration* config = [[SBSDKUIBarcodeScannerConfiguration alloc]
                                                  initWithUIConfiguration:uiConfig
                                                  textConfiguration:textConfig
                                                  behaviorConfiguration:behaviorConfig
                                                  cameraConfiguration:cameraConfig
                                                  selectionOverlayConfiguration:selectionOverlayConfiguration];
    
    SBSDKUIBarcodeScannerViewController*  viewController = [SBSDKUIBarcodeScannerViewController createNewWithConfiguration:config andDelegate:delegate];
    
    if (acceptedDocumentTypes && acceptedDocumentTypes.count > 0) {
        behaviorConfig.acceptedDocumentTypes = acceptedDocumentTypes;
    }

    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startBatchBarcodeScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? command.arguments[0] : NULL;
    if (!arguments) {
        arguments = @{};
    }
    NSDictionary* configuration = arguments[@"uiConfigs"];
    SBSDKUIBarcodesBatchScannerUIConfiguration *ui =
            [[SBSDKUIBarcodesBatchScannerUIConfiguration alloc] init];
    SBSDKUIBarcodesBatchScannerTextConfiguration *text =
            [[SBSDKUIBarcodesBatchScannerTextConfiguration alloc] init];
    SBSDKUIBarcodesBatchScannerBehaviorConfiguration *behavior =
            [[SBSDKUIBarcodesBatchScannerBehaviorConfiguration alloc] init];
    SBSDKUICameraConfiguration *cameraConfig =
            [[SBSDKUICameraConfiguration alloc] init];
    
    @try {
        [ObjectMapper populateInstance:ui fromDictionary:configuration];
        [ObjectMapper populateInstance:behavior fromDictionary:configuration];
        [ObjectMapper populateInstance:text fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }
    
    ui.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    BatchBarcodeScannerPromiseProxy* delegate = [[BatchBarcodeScannerPromiseProxy alloc]
                                                 initWithDelegate:self.commandDelegate andCallbackId: command.callbackId];
    @try {
        [ObjectMapper populateInstance:delegate fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }
    
    // Barcode Filter (at the moment used for UPC Extension filters)
    SBSDKUIBarcodeFilter* barcodeFilter = extractBarcodeFilter(configuration);
    if (barcodeFilter) {
        behavior.barcodeFilter = barcodeFilter;
    }
    
    behavior.additionalDetectionParameters = extractAdditionalParameters(configuration);
    
    SBSDKBarcodeDensity barcodeDensity = extractBarcodeDensity(configuration);
    behavior.additionalDetectionParameters.codeDensity = barcodeDensity;
    
    behavior.acceptedMachineCodeTypes = extractBarcodeTypes(configuration);
    
    NSArray* acceptedDocumentTypes = extractBarcodeDocumentTypes(configuration);
    
    if (acceptedDocumentTypes && acceptedDocumentTypes.count > 0) {
        behavior.acceptedDocumentTypes = acceptedDocumentTypes;
    }
    
    SBSDKUIBarcodeSelectionOverlayConfiguration* selectionOverlayConfiguration = NULL; // TODO: selection overlay
    
    SBSDKUIBarcodesBatchScannerConfiguration *config = [[SBSDKUIBarcodesBatchScannerConfiguration alloc]
                                                        initWithUIConfiguration:ui
                                                        textConfiguration:text
                                                        behaviorConfiguration:behavior
                                                        cameraConfiguration:cameraConfig
                                                        selectionOverlayConfiguration:selectionOverlayConfiguration];
    
    SBSDKUIBarcodesBatchScannerViewController* viewController = [SBSDKUIBarcodesBatchScannerViewController createNewWithConfiguration: config
                                                                                                                          andDelegate:delegate];
    
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startEHICScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }
    
    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUIHealthInsuranceCardScannerUIConfiguration* uiConfig = [[SBSDKUIHealthInsuranceCardScannerUIConfiguration alloc] init];
    SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration alloc] init];
    SBSDKUIHealthInsuranceCardScannerTextConfiguration* textConfig = [[SBSDKUIHealthInsuranceCardScannerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration *cameraConfig = [[SBSDKUICameraConfiguration alloc] init];
    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    SBSDKUIHealthInsuranceCardScannerConfiguration* config = [[SBSDKUIHealthInsuranceCardScannerConfiguration alloc] initWithUIConfiguration:uiConfig textConfiguration:textConfig behaviorConfiguration:behaviorConfig cameraConfiguration:cameraConfig];

    EHICScannerPromiseProxy* delegate = [[EHICScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];
    
    SBSDKUIHealthInsuranceCardScannerViewController* viewController = [SBSDKUIHealthInsuranceCardScannerViewController createNewWithConfiguration:config andDelegate:delegate];
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startLicensePlateScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }
    
    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUILicensePlateScannerUIConfiguration* uiConfig = [[SBSDKUILicensePlateScannerUIConfiguration alloc] init];
    SBSDKUILicensePlateScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUILicensePlateScannerBehaviorConfiguration alloc] init];
    SBSDKUILicensePlateScannerTextConfiguration* textConfig = [[SBSDKUILicensePlateScannerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration *cameraConfig = [[SBSDKUICameraConfiguration alloc] init];

    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }
    
    applyLicensePlateStyleConfiguration(configuration, uiConfig);

    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    
    NSString* guidanceText = [configuration objectForKey:@"guidanceText"];
    if (guidanceText == nil) {
        guidanceText = @"Place the whole license plate in the frame to scan it";
    }
    textConfig.finderTextHint = guidanceText;
    
    NSString* detectorMode = [configuration objectForKey:@"detectorMode"];
    if (detectorMode != nil && [detectorMode isEqualToString:@"CLASSIC"]) {
        behaviorConfig.scanStrategy = SBSDKLicensePlateScannerStrategyClassic;
    }

    SBSDKUILicensePlateScannerConfiguration* config = [[SBSDKUILicensePlateScannerConfiguration alloc] initWithUIConfiguration:uiConfig textConfiguration:textConfig behaviorConfiguration:behaviorConfig cameraConfiguration:cameraConfig];

    LicensePlateScannerPromiseProxy* delegate = [[LicensePlateScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];
    
    SBSDKUILicensePlateScannerViewController* viewController = [SBSDKUILicensePlateScannerViewController createNewWithConfiguration:config andDelegate:delegate];
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}

- (void)startDataScanner:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = command.arguments.count > 0 ? [command.arguments objectAtIndex:0] : NULL;
    if (!arguments) {
        arguments = @{};
    }
    
    NSDictionary* configuration = [arguments objectForKey:@"uiConfigs"];
    SBSDKUITextDataScannerUIConfiguration* uiConfig = [[SBSDKUITextDataScannerUIConfiguration alloc] init];
    SBSDKUITextDataScannerBehaviorConfiguration* behaviorConfig = [[SBSDKUITextDataScannerBehaviorConfiguration alloc] init];
    SBSDKUITextDataScannerTextConfiguration* textConfig = [[SBSDKUITextDataScannerTextConfiguration alloc] init];
    SBSDKUICameraConfiguration* cameraConfig = [[SBSDKUICameraConfiguration alloc] init];

    @try {
        [ObjectMapper populateInstance:uiConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:behaviorConfig fromDictionary:configuration];
        [ObjectMapper populateInstance:textConfig fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    uiConfig.orientationLockMode = [ObjectMapper extractOrientationLockMode:configuration];
    SBSDKUITextDataScannerConfiguration* config = [[SBSDKUITextDataScannerConfiguration alloc] initWithUIConfiguration:uiConfig
                                                                                                     textConfiguration:textConfig
                                                                                                 behaviorConfiguration:behaviorConfig
                                                                                                   cameraConfiguration:cameraConfig];
    
    NSDictionary* scannerStepConfigs = [arguments objectForKey:@"scannerStep"];
    if (!scannerStepConfigs) {
        [self reportError:@"Missing required argument 'scannerStep'" toCommand:command];
        return;
    }
    
    SBSDKUITextDataScannerStep* step = [[SBSDKUITextDataScannerStep alloc] init];
    @try {
        [ObjectMapper populateInstance:step fromDictionary:scannerStepConfigs];
    }
    @catch (NSException* ex) {
        [self reportError:[ex reason] toCommand:command];
        return;
    }

    DataScannerPromiseProxy* delegate = [[DataScannerPromiseProxy alloc] initWithDelegate:self.commandDelegate andCallbackId:command.callbackId];
    
    SBSDKUITextDataScannerViewController* viewController = [SBSDKUITextDataScannerViewController createNewWithConfiguration:config  andDelegate:delegate]; // recognitionStep:step
    [viewController setModalPresentationStyle:UIModalPresentationFullScreen];
    UIViewController* rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    [rootViewController presentViewController:viewController animated:true completion:nil];
}
@end


@implementation LicensePlateScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    LicensePlateScannerPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)licensePlateScanner:(SBSDKUILicensePlateScannerViewController *)viewController
   didRecognizeLicensePlate:(SBSDKLicensePlateScannerResult *)result {
    
    viewController.recognitionEnabled = false;
    // TODO: fix below once updated to iOS SDK version with fix for this component's navigation
//    [viewController dismissViewControllerAnimated:TRUE completion:nil];

    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{
                                                  @"status": @"OK",
                                                  @"licensePlateResult": @{
                                                          @"rawText": result.rawString,
                                                          @"confidence": @(result.confidence),
                                                          @"countryCode": result.countryCode,
                                                          @"licensePlate": result.licensePlate
                                                  }
                                              }]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)licensePlateScannerDidCancel:(nonnull SBSDKUILicensePlateScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                                                       callbackId:_callbackId];
    // release instance
    _strongSelf = nil;
}
@end


@implementation DataScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    DataScannerPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)textLineRecognizerViewController:(SBSDKUITextDataScannerViewController *)viewController
                           didFinishStep:(SBSDKUITextDataScannerStep *)step
                              withResult:(SBSDKUITextDataScannerStepResult *)result {
    
    viewController.recognitionEnabled = false;
    [viewController dismissViewControllerAnimated:TRUE completion:nil];
    
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{
                                                  @"status": @"OK",
                                                  @"dataResult": @{
                                                          @"textValue": result.text,
                                                          @"confidence": @(result.confidence),
                                                  }
                                              }]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)textLineRecognizerViewControllerDidCancel:(nonnull SBSDKUITextDataScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                                                       callbackId:_callbackId];
    // release instance
    _strongSelf = nil;
}
@end

@implementation DocumentScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    // This field retains a reference to the object until one of the callbacks gets called
    DocumentScannerPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)scanningViewController:(nonnull SBSDKUIDocumentScannerViewController *)viewController didFinishWithDocument:(nonnull SBSDKUIDocument *)document {
    NSMutableArray* result = [NSMutableArray new];
    for (int i = 0; i < [document numberOfPages]; ++i) {
        [result addObject:dictionaryFromPage([document pageAtIndex:i])];
    }

    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{
                                                                    @"status": [result count] > 0 ? @"OK" : @"CANCELED",
                                                                    @"pages": result
                                                                    }]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)scanningViewControllerDidCancel:(SBSDKUIDocumentScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED", @"pages": @[]}]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end


@implementation CroppingScreenPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    CroppingScreenPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)croppingViewController:(SBSDKUICroppingViewController *)viewController didFinish:(SBSDKUIPage *)changedPage {

    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{
                                                                    @"status": @"OK",
                                                                    @"page": dictionaryFromPage(changedPage)
                                                                    }]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)croppingViewControllerDidCancel:(SBSDKUICroppingViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end


@implementation MRZScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    MRZScannerPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)mrzDetectionViewController:(SBSDKUIMRZScannerViewController *)viewController didDetect:(SBSDKMachineReadableZoneRecognizerResult *)zone {
    NSMutableArray* fields = [NSMutableArray array];
    [viewController setRecognitionEnabled:NO];
    for (SBSDKMachineReadableZoneRecognizerField* field in zone.fields) {
        [fields addObject:@{@"name": MRZFieldNameAsString(field.fieldName),
                            @"value": field.value,
                            @"confidence": @(field.averageRecognitionConfidence)
                            }];
    }
    NSDictionary *dict = @{
        @"status": @"OK",
        @"mrzResult": @{
            @"fields": fields,
            @"checkDigitsCount": @(zone.checkDigitsCount),
            @"validCheckDigitsCount": @(zone.validCheckDigitsCount)
        }
    };
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:dict] callbackId:_callbackId];

    viewController.recognitionEnabled = false;
    [viewController dismissViewControllerAnimated:TRUE completion:nil];

    // release instance
    _strongSelf = nil;
}

- (void)mrzDetectionViewControllerDidCancel:(SBSDKUIMRZScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end


@implementation EHICScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    EHICScannerPromiseProxy* _strongSelf;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    return [super init];
}

- (void)healthInsuranceCardDetectionViewController:(SBSDKUIHealthInsuranceCardScannerViewController *)viewController didDetectCard:(SBSDKHealthInsuranceCardRecognitionResult *)card {
    NSMutableArray* fields = [NSMutableArray array];
    
    for (SBSDKHealthInsuranceCardField* field in card.fields) {
        [fields addObject:@{@"type": HealthInsuranceFieldTypeAsString(field.type),
                            @"value": field.value,
                            @"confidence": @(field.confidence)
                            }];
    }
    NSDictionary *dict = @{
        @"status": @"OK",
        @"ehicResult": @{
            @"fields": fields,
        }
    };
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:dict] callbackId:_callbackId];

    viewController.recognitionEnabled = false;
    [viewController dismissViewControllerAnimated:TRUE completion:nil];

    // release instance
    _strongSelf = nil;
}

- (void)healthInsuranceCardDetectionViewControllerDidCancel:(SBSDKUIHealthInsuranceCardScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end


@implementation BarcodeScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    BarcodeScannerPromiseProxy* _strongSelf;
    NSDictionary* _resultMessage;
    bool _shouldWaitForGeneratedImage;
}

- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId shouldWaitForGeneratedImage:(bool)shouldWaitForGeneratedImage {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    _shouldWaitForGeneratedImage = shouldWaitForGeneratedImage;
    _resultMessage = @{@"status": @"OK"}.mutableCopy;
    return [super init];
}

- (void)reportResultsAndComplete {
    if (_shouldWaitForGeneratedImage && [_resultMessage objectForKey:@"imageFileUri"] == nil) {
        return;
    }

    if ([_resultMessage objectForKey:@"barcodes"] == nil) {
        return;
    }

    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:_resultMessage]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                        didDetectResults:(nonnull NSArray<SBSDKBarcodeScannerResult *> *)barcodeResults {
    runInBackground(^{
        NSObject* barcodesDict = jsonFromBarcodeResults(barcodeResults);

        runOnMainThread(^{
            [self->_resultMessage setValue:barcodesDict forKey:@"barcodes"];

            if (!self->_shouldWaitForGeneratedImage) {
                viewController.recognitionEnabled = false;
                [viewController dismissViewControllerAnimated:TRUE completion:nil];
            }

            [self reportResultsAndComplete];
        });
    });
}

- (void)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                  didCaptureBarcodeImage:(nullable UIImage *)barcodeImage
                                imageURL:(nullable NSURL *)imageURL {
    [_resultMessage setValue:imageURL.absoluteString forKey:@"imageFileUri"];

    if (self->_shouldWaitForGeneratedImage) {
        viewController.recognitionEnabled = false;
        [viewController dismissViewControllerAnimated:TRUE completion:nil];
    }

    [self reportResultsAndComplete];
}

- (void)qrBarcodeDetectionViewControllerDidCancel:(SBSDKUIBarcodeScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{@"status": @"CANCELED"}]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}

- (void)qrBarcodeDetectionViewControllerDidTimeout:(SBSDKUIBarcodeScannerViewController *)viewController {
    [_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                              messageAsDictionary:@{
                                                  @"status": @"CANCELED",
                                                  @"canceledDueToTimeout": @(true)
                                              }]
                     callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end


@implementation BatchBarcodeScannerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    BatchBarcodeScannerPromiseProxy* _strongSelf;
    NSDictionary* _resultMessage;
}
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    _resultMessage = @{@"status": @"OK"}.mutableCopy;
    return [super init];
}

- (void)barcodesBatchScannerViewController:(SBSDKUIBarcodesBatchScannerViewController *)
        viewController didFinishWithResults:(NSArray<SBSDKUIBarcodeMappedResult *> *)barcodeResults {
    runInBackground(^{
        
        NSObject* barcodesDict = jsonFromMappedBarcodeResults(barcodeResults);
        runOnMainThread(^{
            [self->_resultMessage setValue:barcodesDict forKey:@"barcodes"];

            viewController.recognitionEnabled = false;
            [viewController dismissViewControllerAnimated:TRUE completion:nil];

            [self->_delegate sendPluginResult:[CDVPluginResult
                            resultWithStatus:CDVCommandStatus_OK
                                               messageAsDictionary:self->_resultMessage]
                                   callbackId:self->_callbackId];
            self->_strongSelf = nil;
        });
    });
}

- (void)barcodesBatchScannerViewControllerDidCancel:
        (SBSDKUIBarcodesBatchScannerViewController *)viewController {
    [_delegate
            sendPluginResult:[CDVPluginResult
                    resultWithStatus:CDVCommandStatus_OK
                 messageAsDictionary:@{@"status": @"CANCELED"}]
                  callbackId:_callbackId];

    // release instance
    _strongSelf = nil;
}
@end

@implementation GenericDocumentRecognizerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    GenericDocumentRecognizerPromiseProxy* _strongSelf;
    NSDictionary* _resultMessage;
}
- (id)initWithDelegate:(id<CDVCommandDelegate>)delegate andCallbackId:(NSString *)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    _resultMessage = @{@"status" : @"OK"}.mutableCopy;
    return [super init];
}

- (void)genericDocumentRecognizerViewControllerDidCancel:(SBSDKUIGenericDocumentRecognizerViewController *)viewController {
    [viewController dismissViewControllerAnimated:YES completion:nil];
    [self->_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsDictionary:@{@"status" : @"CANCELED"}]
                           callbackId:self->_callbackId];
    self->_strongSelf = nil;
}

- (void)genericDocumentRecognizerViewController:(SBSDKUIGenericDocumentRecognizerViewController *)viewController
                         didFinishWithDocuments:(NSArray<SBSDKGenericDocument *> *)documents {
    NSObject *documentsDic = extractGenericDocumentRecognizerResultFromGdrDocuments(documents);
    NSString *documentType = extractGenericDocumentTypeFromGdrDocuments(documents);
    
    [self->_resultMessage setValue:documentType forKey:@"documentType"];
    [self->_resultMessage setValue:documentsDic forKey:@"fields"];
    
    [viewController dismissViewControllerAnimated:YES completion:nil];
    [self->_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsDictionary:self->_resultMessage]
                           callbackId:self->_callbackId];
    self->_strongSelf = nil;
}

@end


@implementation CheckRecognizerPromiseProxy {
    id<CDVCommandDelegate> _delegate;
    NSString* _callbackId;
    CheckRecognizerPromiseProxy* _strongSelf;
    NSDictionary* _resultMessage;
}
- (id)initWithDelegate:(id<CDVCommandDelegate>)delegate andCallbackId:(NSString *)callbackId {
    _delegate = delegate;
    _callbackId = callbackId;
    _strongSelf = self;
    _resultMessage = @{@"status" : @"OK"}.mutableCopy;
    return [super init];
}

- (void)checkRecognizerViewControllerDidCancel:(SBSDKUICheckRecognizerViewController *)viewController {
    [viewController dismissViewControllerAnimated:YES completion:nil];
    [self->_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsDictionary:@{@"status" : @"CANCELED"}]
                           callbackId:self->_callbackId];
    self->_strongSelf = nil;
}

- (void)checkRecognizerViewController:(SBSDKUICheckRecognizerViewController *)viewController
                    didRecognizeCheck:(nonnull SBSDKCheckRecognizerResult *)result {
    extractCheckRecognizerResultFromCheckResult(result, self->_resultMessage);
    
    [viewController dismissViewControllerAnimated:YES completion:nil];
    [self->_delegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsDictionary:self->_resultMessage]
                           callbackId:self->_callbackId];
    self->_strongSelf = nil;
}

@end
