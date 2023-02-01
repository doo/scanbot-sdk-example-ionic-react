//
//  SBSDKBarcodeAdditionalParameters.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 08.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The checksum algorithm for MSI-Plessey type barcodes. */
typedef NS_ENUM(NSInteger, SBSDKBarcodeMSIPlesseyChecksumAlgorithm) {
    /** None. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmNone = 0,

    /** Mod10. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10 = 0x1,

    /** Mod11IBM. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11IBM = 0x2,

    /** Mod11NCR. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11NCR = 0x4,

    /** Mod1010. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1010 = 0x8,

    /** Mod110IBM. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110IBM = 0x10,

    /** Mod1110NCR. */
    SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110NCR = 0x20
};

/** 
 * The expected density of QR codes. A higher density finds more QR codes in an image 
 * but the performance is slightly reduced. 
 */
typedef NS_ENUM(NSInteger, SBSDKBarcodeDensity) {
    // Low density. Finds up to 6 QR codes in one image or video frame. This is the default value.
    SBSDKBarcodeDensityLow = 0,
    
    // High density. Finds up to 24 QR codes in one image or video frame.
    SBSDKBarcodeDensityHigh = 1
};


/**
 * A class that contains additional parameters for barcodes detection and filtering.
 */
@interface SBSDKBarcodeAdditionalParameters : NSObject

/**
 * With this option, the scanner assumes that the barcode can be a GS1 barcode, and modify the behavior as needed.
 * You can set it to NO, if you don't want to see decoded FNC1 characters ("]C1" and ASCII char 29).
 * The default is YES.
 */
@property (nonatomic) BOOL enableGS1Decoding;

/**
 * Minimum required text length of the detected barcode.
 * The default is 0.
 * NOTE: Currently works for ITF and MSI Plessey barcodes only!
 */
@property (nonatomic) NSUInteger minimumTextLength;

/**
 * Maximum text length of the detected barcode. Setting to zero removes the limit.
 * The default is 0.
 * NOTE: Currently works for ITF and MSI Plessey barcodes only!
 */
@property (nonatomic) NSUInteger maximumTextLength;

/**
 * Minimum required quiet zone on the barcode. Measured in modules (the size of minimal bar on the barcode).
 * The default is 10.
 * NOTE: Currently works for ITF and MSI Plessey barcodes only!
 */
@property (nonatomic) NSUInteger minimum1DBarcodesQuietZone;

/**
 * The checksum algorithm for MSI Plessey barcodes.
 * The default value is SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10.
 */
@property (nonatomic, assign) SBSDKBarcodeMSIPlesseyChecksumAlgorithm msiPlesseyChecksumAlgorithm;

/**
 * With this option enabled, the scanner removes checks digits for UPC, EAN and MSI Plessey codes.
 * Has no effect if both single and double digit MSI Plessey checksums are enabled.
 * The default is NO
 */
@property (nonatomic, assign) BOOL stripCheckDigits;

/**
 * The expected QR code density. Set to `SBSDKBarcodeDensityHigh` if you expect to find lots of QR codes in one image
 * or video frame. Set to `SBSDKBarcodeDensityLow`, the default value, otherwise. 
 */
@property (nonatomic, assign) SBSDKBarcodeDensity codeDensity;

@end
