#ifndef BarcodeMapping_h
#define BarcodeMapping_h

#include "ScanbotStorageUtils.h"
#include "CordovaBarcodeExtensionFilter.h"
#include "ObjectMapper.h"

static inline SBSDKBarcodeType* barcodeTypeFromString(NSString* string) {
    if ([string isEqualToString:@"AZTEC"]) return SBSDKBarcodeTypeAztec;
    if ([string isEqualToString:@"CODABAR"]) return SBSDKBarcodeTypeCodaBar;
    if ([string isEqualToString:@"CODE_128"]) return SBSDKBarcodeTypeCode128;
    if ([string isEqualToString:@"CODE_39"]) return SBSDKBarcodeTypeCode39;
    if ([string isEqualToString:@"CODE_93"]) return SBSDKBarcodeTypeCode93;
    if ([string isEqualToString:@"DATA_MATRIX"]) return SBSDKBarcodeTypeDataMatrix;
    if ([string isEqualToString:@"EAN_13"]) return SBSDKBarcodeTypeEAN13;
    if ([string isEqualToString:@"EAN_8"]) return SBSDKBarcodeTypeEAN8;
    if ([string isEqualToString:@"ITF"]) return SBSDKBarcodeTypeITF;
    if ([string isEqualToString:@"PDF_417"]) return SBSDKBarcodeTypePDF417;
    if ([string isEqualToString:@"QR_CODE"]) return SBSDKBarcodeTypeQRCode;
    if ([string isEqualToString:@"UPC_A"]) return SBSDKBarcodeTypeUPCA;
    if ([string isEqualToString:@"UPC_E"]) return SBSDKBarcodeTypeUPCE;
    if ([string isEqualToString:@"MSI_PLESSEY"]) return SBSDKBarcodeTypeMSIPlessey;
    return nil;
}

static inline SBSDKBarcodeDocumentType* barcodeDocumentTypeFromString(NSString* string) {
    if ([string isEqualToString:@"AAMVA"]) return SBSDKBarcodeDocumentTypeAAMVA;
    if ([string isEqualToString:@"ID_CARD_PDF_417"]) return SBSDKBarcodeDocumentTypeIDCardPDF417;
    if ([string isEqualToString:@"SEPA"]) return SBSDKBarcodeDocumentTypeSEPA;
    if ([string isEqualToString:@"MEDICAL_CERTIFICATE"]) return SBSDKBarcodeDocumentTypeMedicalCertificate;
    if ([string isEqualToString:@"BOARDING_PASS"]) return SBSDKBarcodeDocumentTypeBoardingPass;
    if ([string isEqualToString:@"DE_MEDICAL_PLAN"]) return SBSDKBarcodeDocumentTypeMedicalPlan;
    if ([string isEqualToString:@"VCARD"]) return SBSDKBarcodeDocumentTypeVCard;
    if ([string isEqualToString:@"SWISS_QR"]) return SBSDKBarcodeDocumentTypeSwissQR;
    return nil;
}

static inline SBSDKBarcodeMSIPlesseyChecksumAlgorithm extractPlesseyChecksumAlgorithmFromConfiguration(NSDictionary* configuration) {
    NSString* algorithm = [configuration objectForKey:@"msiPlesseyChecksumAlgorithm"];
    
    if (algorithm == nil) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10;
    if ([algorithm isEqualToString:@"None"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmNone;
    if ([algorithm isEqualToString:@"Mod10"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10;
    if ([algorithm isEqualToString:@"Mod1010"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1010;
    if ([algorithm isEqualToString:@"Mod11IBM"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11IBM;
    if ([algorithm isEqualToString:@"Mod11NCR"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod11NCR;
    if ([algorithm isEqualToString:@"Mod1110IBM"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110IBM;
    if ([algorithm isEqualToString:@"Mod1110NCR"]) return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod1110NCR;
    
    return SBSDKBarcodeMSIPlesseyChecksumAlgorithmMod10;
}

static inline NSArray<NSNumber*>* jsonFromRawBytes(NSData* rawBytes) {
    NSMutableArray<NSNumber*>* byteArray = [[NSMutableArray alloc] init];
    uint8_t* bytePtr = (uint8_t*)[rawBytes bytes];
    NSInteger totalData = [rawBytes length] / sizeof(uint8_t);
    for (int i=0 ; i<totalData; i++) {
        uint8_t current = bytePtr[i];
        [byteArray addObject:[[NSNumber alloc] initWithUnsignedChar:current]];
    }
    return byteArray;
}

static inline NSDictionary<NSString*, NSObject*>* jsonFromBarcodeResult(SBSDKBarcodeScannerResult *result) {
    NSMutableDictionary* x = @{
        @"type": result.type.name,
        @"text": result.rawTextString,
        @"textWithExtension": result.rawTextStringWithExtension,
        @"rawBytes": jsonFromRawBytes (result.rawBytes)
    }.mutableCopy;
    return x.copy;
}

static inline NSArray<NSDictionary<NSString*, NSObject*>*>* jsonFromMappedBarcodeResults(NSArray<SBSDKUIBarcodeMappedResult *> *results) {
    NSMutableArray<NSDictionary<NSString*, NSObject*>*>* jsonResults = [[NSMutableArray alloc] init];
    for (int i = 0; i < results.count; ++i) {
        [jsonResults addObject:jsonFromBarcodeResult([results objectAtIndex:i].barcode)];
    }
    
    return [jsonResults copy];
}

static inline NSArray<NSDictionary<NSString*, NSObject*>*>* jsonFromBarcodeResults(NSArray<SBSDKBarcodeScannerResult *> *results) {
    NSMutableArray<NSDictionary<NSString*, NSObject*>*>* jsonResults = [[NSMutableArray alloc] init];
    for (int i = 0; i < results.count; ++i) {
        [jsonResults addObject:jsonFromBarcodeResult([results objectAtIndex:i])];
    }
    
    return [jsonResults copy];
}

static inline NSArray* extractBarcodeDocumentTypes(NSDictionary* configuration) {
    NSArray* documentFormats = [configuration objectForKey:@"acceptedDocumentFormats"];
    if (documentFormats) {
        NSMutableArray* outDocumentTypes = [NSMutableArray array];
        for (NSString* format in documentFormats) {
            SBSDKBarcodeDocumentType* type = barcodeDocumentTypeFromString(format);
            if (type != nil) {
                [outDocumentTypes addObject:type];
            }
        }
        return outDocumentTypes.copy;
    }
    return nil;
}

static inline NSArray* extractBarcodeTypes(NSDictionary* configuration) {
    NSArray* barcodeFormats = [configuration objectForKey:@"barcodeFormats"];
    if (barcodeFormats && [barcodeFormats indexOfObject:@"ALL_FORMATS"] == NSNotFound) {
        NSMutableArray* machineCodeTypes = [NSMutableArray array];
        for (NSString* format in barcodeFormats) {
            SBSDKBarcodeType* type = barcodeTypeFromString(format);
            if (type != nil) {
                [machineCodeTypes addObject:type];
            }
        }
        return machineCodeTypes.copy;
    }
    return nil;
}

static inline SBSDKBarcodeDensity extractBarcodeDensity(NSDictionary* configuration) {
    SBSDKBarcodeDensity barcodeDensity = SBSDKBarcodeDensityLow;
    
    NSString* codeDensity = [configuration objectForKey:@"codeDensity"];
    if (codeDensity != nil) {
        if([codeDensity isEqualToString:@"HIGH"]) {
            barcodeDensity = SBSDKBarcodeDensityHigh;
        }
    }
    
    return barcodeDensity;
}

static inline SBSDKBarcodeAdditionalParameters* extractAdditionalParameters(NSDictionary* configuration) {
    SBSDKBarcodeAdditionalParameters* additionalParameters = [[SBSDKBarcodeAdditionalParameters alloc] init];
    @try {
        [ObjectMapper populateInstance:additionalParameters fromDictionary:configuration];
    }
    @catch (NSException* ex) {
        return nil;
    }
    
    // Need to manually extract because of naming disparity between iOS and Android
    // Also, it is nullable, 'true' by default, so we wrap it in an NSNumber
    NSNumber* gs1Decoding = [configuration objectForKey:@"gs1DecodingEnabled"];
    if (gs1Decoding != nil) {
        additionalParameters.enableGS1Decoding = [gs1Decoding boolValue];
    }
    
    additionalParameters.codeDensity = extractBarcodeDensity(configuration);
    
    // We also need to manually extract the MSI-Plessey Checksum Algorithm since it can't be mapped automatically
    additionalParameters.msiPlesseyChecksumAlgorithm = extractPlesseyChecksumAlgorithmFromConfiguration(configuration);
    
    return additionalParameters;
}

static inline SBSDKUIBarcodeFilter* extractBarcodeFilter(NSDictionary* configuration) {
    NSString* jsonFilterType = [configuration objectForKey:@"barcodeFilter"];
    if (jsonFilterType == nil) {
        return nil;
    }
    
    if ([jsonFilterType isEqualToString:@"WithExtension"]) {
        return [[CordovaBarcodeExtensionFilter alloc] init:CordovaBarcodeExtensionFilterWithExtension];
    } else if ([jsonFilterType isEqualToString:@"WithEAN2Extension"]) {
        return [[CordovaBarcodeExtensionFilter alloc] init:CordovaBarcodeExtensionFilterWithEAN2Extension];
    } else if ([jsonFilterType isEqualToString:@"WithEAN5Extension"]) {
        return [[CordovaBarcodeExtensionFilter alloc] init:CordovaBarcodeExtensionFilterWithEAN5Extension];
    }
    return nil;
}

static inline NSArray* filterBarcodeResults(NSArray<SBSDKBarcodeScannerResult *>* barcodeResults, SBSDKUIBarcodeFilter* filter) {
    NSMutableArray<SBSDKBarcodeScannerResult *>* outResults = [[NSMutableArray alloc] init];
    
    if (barcodeResults == nil) {
        return outResults;
    }
    
    for (SBSDKBarcodeScannerResult* result in barcodeResults) {
        if (![filter acceptsBarcode:result]) { continue; }
        [outResults addObject:result];
    }
    
    return outResults;
}

#endif /* BarcodeMapping_h */
