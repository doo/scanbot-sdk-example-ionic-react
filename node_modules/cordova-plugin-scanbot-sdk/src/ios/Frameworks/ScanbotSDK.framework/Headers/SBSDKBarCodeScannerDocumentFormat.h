//
//  SBSDKBarCodeScannerFormattedResult.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A helper class describing a barcode document type.
 */
@interface SBSDKBarcodeDocumentType: NSObject

/** Name of the barcode document type. */
@property (nonatomic, readonly) NSString *name;

/** This class cannot be instantiated. */
- (instancetype)init NS_UNAVAILABLE;

/** Returns an array of all valid bar code document types. */
+ (NSArray<SBSDKBarcodeDocumentType*>*)allTypes;

@end


/** The barcode document type AAMVA. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeAAMVA;

/** The barcode document type PDF417. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeIDCardPDF417;

/** The barcode document type SEPA. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeSEPA;

/** The barcode document type for medical certificates. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeMedicalCertificate;

/** The barcode document type for boarding passes. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeBoardingPass;

/** The barcode document type for medical plans. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeMedicalPlan;

/** The barcode document type for VCards. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeVCard;

/** The barcode document type for Swiss QR codes. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeSwissQR;

/** The barcode document type for GS1 codes. */
extern SBSDKBarcodeDocumentType * const SBSDKBarcodeDocumentTypeGS1;

/**
 * Base class for describing recognized and parsed barcode information.
 */
@interface SBSDKBarCodeScannerDocumentFormat : NSObject

/** Indicates, whether parsing was successful. */
@property (nonatomic) BOOL parsedSuccessful;

/** The type of the barcode document. */
@property (nonatomic, readonly) SBSDKBarcodeDocumentType *type;

/** Initializer */
- (instancetype)initWithString:(NSString *)rawString;

@end

NS_ASSUME_NONNULL_END
