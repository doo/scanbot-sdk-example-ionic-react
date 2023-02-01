//
//  SBSDKBarCodeScannerSearchResult.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 17.01.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKPolygon.h"
#import "SBSDKBarCodeScannerDocumentFormat.h"
#import "SBSDKBarcodeType.h"

#import "SBSDKAAMVADocumentFormat.h"
#import "SBSDKIDCardPDF417DocumentFormat.h"
#import "SBSDKSEPADocumentFormat.h"
#import "SBSDKMedicalCertificateDocumentFormat.h"
#import "SBSDKBoardingPassDocumentFormat.h"
#import "SBSDKMedicalPlanDocumentFormat.h"
#import "SBSDKVCardDocumentFormat.h"
#import "SBSDKSwissQRCodeDocumentFormat.h"
#import "SBSDKGS1DocumentFormat.h"

#import "SBSDKBarcodeDocumentParser.h"

NS_ASSUME_NONNULL_BEGIN

/** The barcode metadata key for the EAN/UPC extensions. */
extern NSString* const SBSDKBarcodeMetadataEANUPCExtensionKey;

/**
 * This class encapsulates the result of a barcode detection.
 */
@interface SBSDKBarcodeScannerResult : NSObject

/** SBSDKPolygon instance where the barcode was found. */
@property (nonatomic, strong, readonly) SBSDKPolygon *polygon;

/** The barcodes type. */
@property (nonatomic, readonly) SBSDKBarcodeType *type;

/** A perspective corrected image of the barcode. */
@property (nonatomic, strong, readonly) UIImage *barcodeImage;

/** The raw content value of the found barcode. */
@property (nonatomic, strong, readonly) NSString *rawTextString;

/** The raw content value of the found barcode including an eventual extension from the metadata. */
@property (nonatomic, strong, readonly) NSString *rawTextStringWithExtension;

/** The raw content bytes of the found barcode. */
@property (nonatomic, strong) NSData *rawBytes;

/** The formatted result object depending on scanned barcodes document type (if supported). */
@property (nonatomic, strong) SBSDKBarCodeScannerDocumentFormat *formattedResult;

/**
 * The metadata of the found barcode.
 * Accessible via public keys e.g. metadata[SBSDKBarcodeMetadataEANUPCExtensionKey].
 * */
@property (nonatomic, strong) NSDictionary* metadata;

/** Initializer */
- (instancetype)initWithPolygon:(SBSDKPolygon *)poly
                           type:(SBSDKBarcodeType *)type
                   barcodeImage:(UIImage *)image
                  rawTextString:(NSString *)string
                       rawBytes:(NSData *)rawBytes
                       metadata:(NSDictionary*)metadata;

@end

NS_ASSUME_NONNULL_END
