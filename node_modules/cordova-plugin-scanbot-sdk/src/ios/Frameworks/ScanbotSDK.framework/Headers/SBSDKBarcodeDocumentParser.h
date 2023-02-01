//
//  SBSDKBarcodeDocumentParser.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 27.01.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SBSDKBarCodeScannerDocumentFormat.h"
#import "SBSDKAAMVADocumentFormat.h"
#import "SBSDKIDCardPDF417DocumentFormat.h"
#import "SBSDKSEPADocumentFormat.h"
#import "SBSDKMedicalCertificateDocumentFormat.h"
#import "SBSDKBoardingPassDocumentFormat.h"
#import "SBSDKMedicalPlanDocumentFormat.h"
#import "SBSDKVCardDocumentFormat.h"
#import "SBSDKSwissQRCodeDocumentFormat.h"
#import "SBSDKGS1DocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class to parse a raw string value (usually taken from the barcode)
 * into a formatted document of the supported type.
 */
@interface SBSDKBarcodeDocumentParser : NSObject

/**
 * Parses the string into one of the supported document type or returns
 * nil if none of the supported document types was detected.
 * @param inputString The string to be parsed.
 * @return Parsed barcode document or nil.
 */
- (SBSDKBarCodeScannerDocumentFormat *)parseDocument:(NSString *)inputString;

@end

NS_ASSUME_NONNULL_END
