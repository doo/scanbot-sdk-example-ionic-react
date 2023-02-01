//
//  Scanbot SDK ReactNative Module
//
//  Copyright (c) 2018 doo GmbH. All rights reserved.
//

#import "SBSDKPolygon+JSON.h"
#import "HashUtils.h"
#import "ScanbotStorageUtils.h"
#import "SharedConfiguration.h"
#import "LoggingUtils.h"

@import ScanbotSDK;

static inline NSString * DetectionResultAsJSONStringValue(SBSDKDocumentDetectionStatus status) {
    switch (status) {
        case SBSDKDocumentDetectionStatusOK:
            return @"OK";
        case SBSDKDocumentDetectionStatusOK_SmallSize:
            return @"OK_BUT_TOO_SMALL";
        case SBSDKDocumentDetectionStatusOK_BadAngles:
            return @"OK_BUT_BAD_ANGLES";
        case SBSDKDocumentDetectionStatusOK_BadAspectRatio:
            return @"OK_BUT_BAD_ASPECT_RATIO";
        case SBSDKDocumentDetectionStatusOK_OffCenter:
            return @"OK_OFF_CENTER";
        case SBSDKDocumentDetectionStatusError_NothingDetected:
            return @"ERROR_NOTHING_DETECTED";
        case SBSDKDocumentDetectionStatusError_Brightness:
            return @"ERROR_TOO_DARK";
        case SBSDKDocumentDetectionStatusError_Noise:
            return @"ERROR_TOO_NOISY";
        default:
            return @"";
    }
}

static inline SBSDKDocumentDetectionStatus detectionStatusFromJSONString(NSString* detectionResult) {
    if (!detectionResult) {
        return SBSDKDocumentDetectionStatusNotAcquired;
    }
    if ([detectionResult isEqualToString:@"OK"]) return SBSDKDocumentDetectionStatusOK;
    if ([detectionResult isEqualToString:@"OK_BUT_TOO_SMALL"]) return SBSDKDocumentDetectionStatusOK_SmallSize;
    if ([detectionResult isEqualToString:@"OK_BUT_BAD_ANGLES"]) return SBSDKDocumentDetectionStatusOK_BadAngles;
    if ([detectionResult isEqualToString:@"OK_BUT_BAD_ASPECT_RATIO"]) return SBSDKDocumentDetectionStatusOK_BadAspectRatio;
    if ([detectionResult isEqualToString:@"OK_OFF_CENTER"]) return SBSDKDocumentDetectionStatusOK_OffCenter;
    if ([detectionResult isEqualToString:@"ERROR_NOTHING_DETECTED"]) return SBSDKDocumentDetectionStatusError_NothingDetected;
    if ([detectionResult isEqualToString:@"ERROR_TOO_DARK"]) return SBSDKDocumentDetectionStatusError_Brightness;
    if ([detectionResult isEqualToString:@"ERROR_TOO_NOISY"]) return SBSDKDocumentDetectionStatusError_Noise;
    return SBSDKDocumentDetectionStatusNotAcquired;
}

static inline NSString* MRZFieldNameAsString(SBSDKMachineReadableZoneRecognizerFieldName name) {
    switch (name) {
        case SBSDKMachineReadableZoneRecognizerFieldNameUnknown:
            return @"Unknown";
        case SBSDKMachineReadableZoneRecognizerFieldNameDocumentCode:
            return @"DocumentCode";
        case SBSDKMachineReadableZoneRecognizerFieldNameIssuingStateOrOrganization:
            return @"IssuingStateOrOrganization";
        case SBSDKMachineReadableZoneRecognizerFieldNameDepartmentOfIssuance:
            return @"DepartmentOfIssuance";
        case SBSDKMachineReadableZoneRecognizerFieldNameFirstName:
            return @"FirstName";
        case SBSDKMachineReadableZoneRecognizerFieldNameLastName:
            return @"LastName";
        case SBSDKMachineReadableZoneRecognizerFieldNameNationality:
            return @"Nationality";
        case SBSDKMachineReadableZoneRecognizerFieldNameDateOfBirth:
            return @"DateOfBirth";
        case SBSDKMachineReadableZoneRecognizerFieldNameGender:
            return @"Gender";
        case SBSDKMachineReadableZoneRecognizerFieldNameDateOfExpiry:
            return @"DateOfExpiry";
        case SBSDKMachineReadableZoneRecognizerFieldNamePersonalNumber:
            return @"PersonalNumber";
        case SBSDKMachineReadableZoneRecognizerFieldNameTravelDocumentType:
            return @"TravelDocumentType";
        case SBSDKMachineReadableZoneRecognizerFieldNameOptional1:
            return @"Optional1";
        case SBSDKMachineReadableZoneRecognizerFieldNameOptional2:
            return @"Optional2";
        case SBSDKMachineReadableZoneRecognizerFieldNameDiscreetIssuingStateOrOrganization:
            return @"DiscreetIssuingStateOrOrganization";
        default:
            return @"";
    }
}

static inline NSString* HealthInsuranceFieldTypeAsString(SBSDKHealthInsuranceCardFieldType type) {
    
    if (type == SBSDKHealthInsuranceCardFieldTypeSurname)
        return @"SURNAME";
    if (type == SBSDKHealthInsuranceCardFieldTypeGivenName)
        return @"GIVEN_NAME";
    if (type == SBSDKHealthInsuranceCardFieldTypeCardNumber)
        return @"CARD_NUMBER";
    if (type == SBSDKHealthInsuranceCardFieldTypeDateOfBirth)
        return @"DATE_OF_BIRTH";
    if (type == SBSDKHealthInsuranceCardFieldTypeInstitutionName)
        return @"INSTITUTION_NAME";
    if (type == SBSDKHealthInsuranceCardFieldTypeInstitutionNumber)
        return @"INSTITUTION_NUMBER";
    if (type == SBSDKHealthInsuranceCardFieldTypeCardExpirationDate)
        return @"CARD_EXPIRATION_DATE";
    if (type == SBSDKHealthInsuranceCardFieldTypePersonalIdentificationNumber)
        return @"PERSONAL_IDENTIFICATION_NUMBER";
    
    return @"";
}

static inline NSString* ImageFilterAsJSONStringValue(SBSDKImageFilterType filter) {
    switch (filter) {
        case SBSDKImageFilterTypeNone: return @"NONE";
        case SBSDKImageFilterTypeColor: return @"COLOR_ENHANCED";
        case SBSDKImageFilterTypeGray: return @"GRAYSCALE";
        case SBSDKImageFilterTypeBinarized: return @"BINARIZED";
        case SBSDKImageFilterTypeColorDocument: return @"COLOR_DOCUMENT";
        case SBSDKImageFilterTypePureBinarized: return @"PURE_BINARIZED";
        case SBSDKImageFilterTypeBackgroundClean: return @"BACKGROUND_CLEAN";
        case SBSDKImageFilterTypeBlackAndWhite: return @"BLACK_AND_WHITE";
        case SBSDKImageFilterTypeOtsuBinarization: return @"OTSU_BINARIZATION";
        case SBSDKImageFilterTypeDeepBinarization: return @"DEEP_BINARIZATION";
        case SBSDKImageFilterTypeLowLightBinarization: return @"LOW_LIGHT_BINARIZATION";
        case SBSDKImageFilterTypeEdgeHighlight: return @"EDGE_HIGHLIGHT";
        case SBSDKImageFilterTypeLowLightBinarization2: return @"LOW_LIGHT_BINARIZATION_2";
        case SBSDKImageFilterTypeSensitiveBinarization: return @"SENSITIVE_BINARIZATION";
        default: return @"";
    }
}

static inline SBSDKImageFilterType filterIdFromFilterNameString(NSString* filterName) {
    if (!filterName) {
        return SBSDKImageFilterTypeNone;
    }
    
    if ([filterName isEqualToString:@"COLOR_ENHANCED"]) return SBSDKImageFilterTypeColor;
    if ([filterName isEqualToString:@"GRAYSCALE"]) return SBSDKImageFilterTypeGray;
    if ([filterName isEqualToString:@"BINARIZED"]) return SBSDKImageFilterTypeBinarized;
    if ([filterName isEqualToString:@"COLOR_DOCUMENT"]) return SBSDKImageFilterTypeColorDocument;
    if ([filterName isEqualToString:@"PURE_BINARIZED"]) return SBSDKImageFilterTypePureBinarized;
    if ([filterName isEqualToString:@"BACKGROUND_CLEAN"]) return SBSDKImageFilterTypeBackgroundClean;
    if ([filterName isEqualToString:@"BLACK_AND_WHITE"]) return SBSDKImageFilterTypeBlackAndWhite;
    if ([filterName isEqualToString:@"OTSU_BINARIZATION"]) return SBSDKImageFilterTypeOtsuBinarization;
    if ([filterName isEqualToString:@"DEEP_BINARIZATION"]) return SBSDKImageFilterTypeDeepBinarization;
    if ([filterName isEqualToString:@"LOW_LIGHT_BINARIZATION"]) return SBSDKImageFilterTypeLowLightBinarization;
    if ([filterName isEqualToString:@"EDGE_HIGHLIGHT"]) return SBSDKImageFilterTypeEdgeHighlight;
    if ([filterName isEqualToString:@"LOW_LIGHT_BINARIZATION_2"]) return SBSDKImageFilterTypeLowLightBinarization2;
    if ([filterName isEqualToString:@"SENSITIVE_BINARIZATION"]) return SBSDKImageFilterTypeSensitiveBinarization;
    return SBSDKImageFilterTypeNone;
}

static inline SBSDKPDFRendererPageSize pageSizeFromPagesizeNameString(NSString* pageSizeName) {
    if (!pageSizeName) {
        return SBSDKPDFRendererPageSizeAuto;
    }
    
    if ([pageSizeName isEqualToString:@"FROM_IMAGE"]) return SBSDKPDFRendererPageSizeFromImage;
    if ([pageSizeName isEqualToString:@"A4"]) return SBSDKPDFRendererPageSizeA4;
    if ([pageSizeName isEqualToString:@"FIXED_A4"]) return SBSDKPDFRendererPageSizeFixedA4;
    if ([pageSizeName isEqualToString:@"US_LETTER"]) return SBSDKPDFRendererPageSizeUSLetter;
    if ([pageSizeName isEqualToString:@"FIXED_US_LETTER"]) return SBSDKPDFRendererPageSizeFixedUSLetter;
    if ([pageSizeName isEqualToString:@"AUTO_LOCALE"]) return SBSDKPDFRendererPageSizeAutoLocale;
    if ([pageSizeName isEqualToString:@"AUTO"]) return SBSDKPDFRendererPageSizeAuto;
    return SBSDKPDFRendererPageSizeAuto;
}

static inline NSDictionary* CGSizeAsJson(CGSize size) {
    return @{@"width": @(size.width),
             @"height": @(size.height)};
}

static inline CGSize CGSizeFromJson(NSDictionary* json) {
    return CGSizeMake(((NSNumber*)json[@"width"]).floatValue,
                      ((NSNumber*)json[@"height"]).floatValue);
}

static inline NSDictionary* dictionaryFromPage(SBSDKUIPage* page) {
    NSMutableDictionary* result = @{
        @"pageId": [page.pageFileUUID UUIDString],
        @"polygon": (page.polygon ? [page.polygon polygonPoints] : [NSArray new]),
        @"filter": ImageFilterAsJSONStringValue(page.filter),
        @"detectionResult": DetectionResultAsJSONStringValue(page.status),
        @"originalImageFileUri": uriWithMinihash(page.originalImageURL),
        @"originalPreviewImageFileUri": uriWithMinihash([SBSDKUIPageFileStorage.defaultStorage previewImageURLWithPageFileID:page.pageFileUUID pageFileType:SBSDKUIPageFileTypeOriginal]),
        @"isCapturedAutomatically": [NSNumber numberWithBool: page.isCapturedAutomatically]
    }.mutableCopy;
    
    if (!CGSizeEqualToSize(page.documentImageSizeLimit, CGSizeZero)) {
        result[@"documentImageSizeLimit"] = CGSizeAsJson(page.documentImageSizeLimit);
    }
    
    NSURL* documentImageUrl = page.documentImageURL;
    if (documentImageUrl) {
        NSURL* documentPreviewImageUrl = [SBSDKUIPageFileStorage.defaultStorage previewImageURLWithPageFileID:page.pageFileUUID pageFileType:SBSDKUIPageFileTypeDocument];
        [result setObject:uriWithMinihash(documentImageUrl) forKey:@"documentImageFileUri"];
        [result setObject:uriWithMinihash(documentPreviewImageUrl) forKey:@"documentPreviewImageFileUri"];
    }
    
    return result;
}

static inline CGPoint CGPointFromNSArray(NSDictionary<NSString*, NSNumber*>* pt) {
    CGFloat x = [pt[@"x"] doubleValue];
    CGFloat y = [pt[@"y"] doubleValue];
    
    return CGPointMake(x, y);
}

static inline SBSDKUIPage* pageFromDictionary(NSDictionary* dict) {
    if (!dict) {
        return nil;
    }
    SBSDKPolygon* poly = nil;
    NSArray* points = [dict objectForKey:@"polygon"];
    if (points != nil && [points count] == 4) {
        poly = [[SBSDKPolygon alloc] initWithNormalizedPointA:CGPointFromNSArray(points[0])
                                                       pointB:CGPointFromNSArray(points[1])
                                                       pointC:CGPointFromNSArray(points[2])
                                                       pointD:CGPointFromNSArray(points[3])];
        poly.detectionStatus = detectionStatusFromJSONString(dict[@"detectionResult"]);
    }
    
    NSUUID* uuid = [[NSUUID alloc] initWithUUIDString:dict[@"pageId"]];
    CGSize documentImageSizeLimit = dict[@"documentImageSizeLimit"] ? CGSizeFromJson(dict[@"documentImageSizeLimit"]) : CGSizeZero;
    
    return [[SBSDKUIPage alloc] initWithPageFileID:uuid
                                           polygon:poly
                                            filter:filterIdFromFilterNameString([dict objectForKey:@"filter"])
                            documentImageSizeLimit:documentImageSizeLimit];
}

static inline NSArray<SBSDKUIPage *>* pagesFromJsonArray(NSArray* jsonPages) {
    if (jsonPages == nil || [jsonPages count] == 0) {
        return nil;
    }
    
    NSMutableArray<SBSDKUIPage *> *sdkPages = [NSMutableArray new];
    for (NSDictionary* p in jsonPages) {
        [sdkPages addObject:pageFromDictionary(p)];
    }
    
    return sdkPages;
}

static inline SBSDKTIFFImageWriterCompressionOptions tiffCompressionOptionFromStringName(NSString* compressionName, SBSDKTIFFImageWriterCompressionOptions defaultValue) {
    if (!compressionName) {
        return defaultValue;
    }
    
    if ([compressionName isEqualToString:@"CCITTRLE"]) return COMPRESSION_CCITTRLE;
    if ([compressionName isEqualToString:@"CCITTFAX3"]) return COMPRESSION_CCITTFAX3;
    if ([compressionName isEqualToString:@"CCITT_T4"]) return COMPRESSION_CCITT_T4;
    if ([compressionName isEqualToString:@"CCITTFAX4"]) return COMPRESSION_CCITTFAX4;
    if ([compressionName isEqualToString:@"CCITT_T6"]) return COMPRESSION_CCITT_T6;
    if ([compressionName isEqualToString:@"CCITTRLEW"]) return COMPRESSION_CCITTRLEW;
    if ([compressionName isEqualToString:@"LZW"]) return COMPRESSION_LZW;
    if ([compressionName isEqualToString:@"PACKBITS"]) return COMPRESSION_PACKBITS;
    if ([compressionName isEqualToString:@"DEFLATE"]) return COMPRESSION_DEFLATE;
    if ([compressionName isEqualToString:@"ADOBE_DEFLATE"]) return COMPRESSION_ADOBE_DEFLATE;
    return COMPRESSION_NONE;
}

static inline SBSDKGenericDocumentRootType* gdrRootTypeFromString(NSString* string) {
    if ([string isEqualToString: @"DeIdFront"]) {
        return SBSDKGenericDocumentRootType.deIdCardFront;
    }
    if ([string isEqualToString: @"DeIdBack"]) {
        return SBSDKGenericDocumentRootType.deIdCardBack;
    }
    if ([string isEqualToString: @"DePassport"]) {
        return SBSDKGenericDocumentRootType.dePassport;
    }
    if ([string isEqualToString: @"DeDriverLicenseFront"]) {
        return SBSDKGenericDocumentRootType.deDriverLicenseFront;
    }
    if ([string isEqualToString: @"DeDriverLicenseBack"]) {
        return SBSDKGenericDocumentRootType.deDriverLicenseBack;
    }
    
    return NULL;
}

static inline NSArray<SBSDKGenericDocumentRootType*>* gdrRootTypesFromJsonArray(NSArray<NSString*>* jsonArray) {
    NSMutableArray<SBSDKGenericDocumentRootType*>* outArray = [[NSMutableArray alloc] init];
    for (NSString* string in jsonArray) {
        SBSDKGenericDocumentRootType* rootType = gdrRootTypeFromString(string);
        if (rootType == NULL) {
            continue;
        }
        [outArray addObject: rootType];
    }
    return outArray;
}

static inline NSArray<SBSDKGenericDocumentRootType*>* extractAcceptedDocumentTypes(NSDictionary* configuration) {
    NSArray* jsonArray = [configuration objectForKey:@"acceptedDocumentTypes"];
    if (!jsonArray || [jsonArray count] == 0) {
        return [SBSDKGenericDocumentRootType allDocumentTypes];
    }
    
    return gdrRootTypesFromJsonArray(jsonArray);
}

static inline SBSDKCheckDocumentRootType* checkRootTypeFromString(NSString* string) {
    if ([string isEqualToString: @"USACheck"]) {
        return SBSDKCheckDocumentRootType.usaCheck;
    }
    if ([string isEqualToString: @"FRACheck"]) {
        return SBSDKCheckDocumentRootType.fraCheck;
    }
    if ([string isEqualToString: @"KWTCheck"]) {
        return SBSDKCheckDocumentRootType.kwtCheck;
    }
    if ([string isEqualToString: @"AUSCheck"]) {
        return SBSDKCheckDocumentRootType.ausCheck;
    }
    if ([string isEqualToString: @"INDCheck"]) {
        return SBSDKCheckDocumentRootType.indCheck;
    }
    if ([string isEqualToString: @"UnknownCheck"]) {
        return SBSDKCheckDocumentRootType.unknownCheck;
    }
    
    return NULL;
}

static inline NSArray<SBSDKCheckDocumentRootType*>* checkDocumentRootTypesFromJsonArray(NSArray<NSString*>* jsonArray) {
    NSMutableArray<SBSDKCheckDocumentRootType*>* outArray = [[NSMutableArray alloc] init];
    for (NSString* string in jsonArray) {
        SBSDKCheckDocumentRootType* rootType = checkRootTypeFromString(string);
        if (rootType == NULL) {
            continue;
        }
        [outArray addObject: rootType];
    }
    return outArray;
}

static inline NSArray<SBSDKCheckDocumentRootType*>* extractAcceptedCheckTypes(NSDictionary* configuration) {
    NSArray* jsonArray = [configuration objectForKey:@"acceptedCheckStandards"];
    if (!jsonArray || [jsonArray count] == 0) {
        return [SBSDKCheckDocumentRootType allDocumentTypes];
    }
    
    return checkDocumentRootTypesFromJsonArray(jsonArray);
}

static inline void addFieldPropertyFromDictionary(NSMutableDictionary* fields,
                                                  NSDictionary* configuration,
                                                  NSString* key,
                                                  NSString* fieldName
                                                  ) {
    NSString* value = [configuration objectForKey:key];
    if (value == NULL) {
        return;
    }
    [fields setObject: value forKey: fieldName];
}

static inline NSMutableDictionary<NSString*, NSString*>* extractGenericDocumentRecognizerFieldProperties(NSDictionary* uiConfig,
                                                                                                         NSArray<SBSDKGenericDocumentRootType*> *genericTypes)
{
    NSDictionary* configuration = [uiConfig objectForKey:@"detailsFieldConfiguration"];
    
    NSMutableDictionary<NSString*, NSString*>* fieldProperties = [[NSMutableDictionary alloc] init];
    
    if (configuration != NULL) {
        NSDictionary* deIdCardBackFields = @{
            @"fieldAddressTitle": SBSDKGenericDocumentDeIdCardBackAddressFieldNormalizedName,
            @"fieldEyeColorTitle": SBSDKGenericDocumentDeIdCardBackEyeColorFieldNormalizedName,
            @"fieldHeightTitle": SBSDKGenericDocumentDeIdCardBackHeightFieldNormalizedName,
            @"fieldIssueDateTitle": SBSDKGenericDocumentDeIdCardBackIssueDateFieldNormalizedName,
            @"fieldIssuingAuthorityTitle": SBSDKGenericDocumentDeIdCardBackIssuingAuthorityFieldNormalizedName,
            @"fieldRawMrzTitle": SBSDKGenericDocumentDeIdCardBackRawMRZFieldNormalizedName,
            @"fieldPseudonymTitle": SBSDKGenericDocumentDeIdCardBackPseudonymFieldNormalizedName
        };
        
        NSDictionary* deIdCardFrontFields = @{
            @"fieldBirthDateTitle": SBSDKGenericDocumentDeIdCardFrontBirthDateFieldNormalizedName,
            @"fieldBirthPlaceTitle": SBSDKGenericDocumentDeIdCardFrontBirthplaceFieldNormalizedName,
            @"fieldExpiryDateTitle": SBSDKGenericDocumentDeIdCardFrontExpiryDateFieldNormalizedName,
            @"fieldGivenNamesTitle": SBSDKGenericDocumentDeIdCardFrontGivenNamesFieldNormalizedName,
            @"fieldIdTitle": SBSDKGenericDocumentDeIdCardFrontIDFieldNormalizedName,
            @"fieldMaidenNameTitle": SBSDKGenericDocumentDeIdCardFrontMaidenNameFieldNormalizedName,
            @"fieldNationalityTitle": SBSDKGenericDocumentDeIdCardFrontNationalityFieldNormalizedName,
            @"fieldPinTitle": SBSDKGenericDocumentDeIdCardFrontPINFieldNormalizedName,
            @"fieldPhotoTitle": SBSDKGenericDocumentDeIdCardFrontPhotoFieldNormalizedName,
            @"fieldSignatureTitle": SBSDKGenericDocumentDeIdCardFrontSignatureFieldNormalizedName,
            @"fieldSurnameTitle": SBSDKGenericDocumentDeIdCardFrontSurnameFieldNormalizedName
        };
        
        NSDictionary* dePassportFields = @{
            @"fieldBirthDateTitle": SBSDKGenericDocumentDePassportBirthDateFieldNormalizedName,
            @"fieldBirthPlaceTitle": SBSDKGenericDocumentDePassportBirthplaceFieldNormalizedName,
            @"fieldCountryCodeTitle": SBSDKGenericDocumentDePassportCountryCodeFieldNormalizedName,
            @"fieldExpiryDateTitle": SBSDKGenericDocumentDePassportExpiryDateFieldNormalizedName,
            @"fieldGenderTitle": SBSDKGenericDocumentDePassportGenderFieldNormalizedName,
            @"fieldGivenNamesTitle": SBSDKGenericDocumentDePassportGivenNamesFieldNormalizedName,
            @"fieldIdTitle": SBSDKGenericDocumentDePassportIDFieldNormalizedName,
            @"fieldIssueDateTitle": SBSDKGenericDocumentDePassportIssueDateFieldNormalizedName,
            @"fieldIssuingAuthorityTitle": SBSDKGenericDocumentDePassportIssuingAuthorityFieldNormalizedName,
            @"fieldMaidenNameTitle": SBSDKGenericDocumentDePassportMaidenNameFieldNormalizedName,
            @"fieldNationalityTitle": SBSDKGenericDocumentDePassportNationalityFieldNormalizedName,
            @"fieldPassportTypeTitle": SBSDKGenericDocumentDePassportPassportTypeFieldNormalizedName,
            @"fieldPhotoTitle": SBSDKGenericDocumentDePassportPhotoFieldNormalizedName,
            @"fieldRawMrzTitle": SBSDKGenericDocumentDePassportRawMRZFieldNormalizedName,
            @"fieldSignatureTitle": SBSDKGenericDocumentDePassportSignatureFieldNormalizedName,
            @"fieldSurnameTitle": SBSDKGenericDocumentDePassportSurnameFieldNormalizedName
        };
        
        NSDictionary* deDriverLicenseBackFields = @{
            @"fieldRestrictionsTitle": SBSDKGenericDocumentDeDriverLicenseBackRestrictionsFieldNormalizedName
        };
        
        NSDictionary* deDriverLicenseFrontFields = @{
            @"fieldBirthDateTitle": SBSDKGenericDocumentDeDriverLicenseFrontBirthDateFieldNormalizedName,
            @"fieldBirthPlaceTitle": SBSDKGenericDocumentDeDriverLicenseFrontBirthplaceFieldNormalizedName,
            @"fieldExpiryDateTitle": SBSDKGenericDocumentDeDriverLicenseFrontExpiryDateFieldNormalizedName,
            @"fieldGivenNamesTitle": SBSDKGenericDocumentDeDriverLicenseFrontGivenNamesFieldNormalizedName,
            @"fieldIdTitle": SBSDKGenericDocumentDeDriverLicenseFrontIDFieldNormalizedName,
            @"fieldIssueDateTitle": SBSDKGenericDocumentDeDriverLicenseFrontIssueDateFieldNormalizedName,
            @"fieldIssuingAuthorityTitle": SBSDKGenericDocumentDeDriverLicenseFrontIssuingAuthorityFieldNormalizedName,
            @"fieldLicenseCategoriesTitle": SBSDKGenericDocumentDeDriverLicenseFrontLicenseCategoriesFieldNormalizedName,
            @"fieldPhotoTitle": SBSDKGenericDocumentDeDriverLicenseFrontPhotoFieldNormalizedName,
            @"fieldSignatureTitle": SBSDKGenericDocumentDeDriverLicenseFrontSignatureFieldNormalizedName,
            @"fieldSurnameTitle": SBSDKGenericDocumentDeDriverLicenseFrontSurnameFieldNormalizedName,
        };
        
        // De ID Card (BACK)
        if ([genericTypes containsObject:SBSDKGenericDocumentRootType.deIdCardBack]) {
            for (NSString* key in deIdCardBackFields.allKeys) {
                addFieldPropertyFromDictionary(fieldProperties, configuration, key, [deIdCardBackFields objectForKey:key]);
            }
        }
        
        // De ID Card (FRONT)
        if ([genericTypes containsObject:SBSDKGenericDocumentRootType.deIdCardFront]) {
            for (NSString* key in deIdCardFrontFields.allKeys) {
                addFieldPropertyFromDictionary(fieldProperties, configuration, key, [deIdCardFrontFields objectForKey:key]);
            }
        }
        
        // De Passport (FRONT & BACK)
        if ([genericTypes containsObject:SBSDKGenericDocumentRootType.dePassport]) {
            for (NSString* key in dePassportFields.allKeys) {
                addFieldPropertyFromDictionary(fieldProperties, configuration, key, [dePassportFields objectForKey:key]);
            }
        }
        
        // De Driver License (BACK)
        if ([genericTypes containsObject:SBSDKGenericDocumentRootType.deDriverLicenseBack]) {
            for (NSString* key in deDriverLicenseBackFields.allKeys) {
                addFieldPropertyFromDictionary(fieldProperties, configuration, key, [deDriverLicenseBackFields objectForKey:key]);
            }
        }
        
        // De Driver License (FRONT)
        if ([genericTypes containsObject:SBSDKGenericDocumentRootType.deDriverLicenseFront]) {
            for (NSString* key in deDriverLicenseFrontFields.allKeys) {
                addFieldPropertyFromDictionary(fieldProperties, configuration, key, [deDriverLicenseFrontFields objectForKey:key]);
            }
        }
    }
    
    return fieldProperties.mutableCopy;
}

static inline NSMutableDictionary<NSString*, NSString*>* extractGenericDocumentRecognizerDocumentProperties(NSDictionary* uiConfig,
                                                                                                            NSArray<SBSDKGenericDocumentRootType*> *genericTypes
                                                                                                            ) {
    NSDictionary* configuration = [uiConfig objectForKey:@"detailsFieldConfiguration"];
    
    NSMutableDictionary<NSString*, NSString*>* typeProperties = [[NSMutableDictionary alloc] init];
    
    if (configuration != NULL) {
        NSString* text = [configuration objectForKey:@"deIdCardBackDocumentTitle"];
        if (text && [genericTypes containsObject:SBSDKGenericDocumentRootType.deIdCardBack]) {
            [typeProperties setValue:text forKey:SBSDKGenericDocumentDeIdCardBackDocumentType];
        }
        
        text = [configuration objectForKey:@"deIdCardFrontDocumentTitle"];
        if (text && [genericTypes containsObject:SBSDKGenericDocumentRootType.deIdCardFront]) {
            [typeProperties setValue:text forKey:SBSDKGenericDocumentDeIdCardFrontDocumentType];
        }
        
        text = [configuration objectForKey:@"dePassportDocumentTitle"];
        if (text && [genericTypes containsObject:SBSDKGenericDocumentRootType.dePassport]) {
            [typeProperties setValue:text forKey:SBSDKGenericDocumentDePassportDocumentType];
        }
        
        text = [configuration objectForKey:@"deDriverLicenseBackDocumentTitle"];
        if (text && [genericTypes containsObject:SBSDKGenericDocumentRootType.deDriverLicenseBack]) {
            [typeProperties setValue:text forKey:SBSDKGenericDocumentDePassportDocumentType];
        }
        
        text = [configuration objectForKey:@"deDriverLicenseFrontDocumentTitle"];
        if (text && [genericTypes containsObject:SBSDKGenericDocumentRootType.deDriverLicenseFront]) {
            [typeProperties setValue:text forKey:SBSDKGenericDocumentDePassportDocumentType];
        }
    }
    
    return typeProperties;
}

static inline NSMutableDictionary<NSString *, NSObject *> *getResultMapFromOcrResult(SBSDKGenericDocumentOcrResult *field) {
    NSMutableDictionary* fieldMap = [[NSMutableDictionary alloc] init];
    
    [fieldMap setValue:[field text] forKey:@"text"];
    [fieldMap setValue:@([field confidence]) forKey:@"confidence"];
    
    return fieldMap;
}

static inline NSString* getNormalizedCheckFieldName(SBSDKGenericDocumentFieldType* fieldType) {
    NSString* fieldName = fieldType.name;
    
    if ([fieldName isEqualToString: @"FontType"]){
        return @"fontType";
    }
    if ([fieldName isEqualToString: @"RawString"]){
        return @"rawString";
    }
    if ([fieldName isEqualToString: @"AccountNumber"]){
        return @"accountNumber";
    }
    if ([fieldName isEqualToString: @"AuxiliaryOnUs"]){
        return @"auxiliaryOnUs";
    }
    if ([fieldName isEqualToString: @"TransitNumber"]){
        return @"transitNumber";
    }
    if ([fieldName isEqualToString: @"ChequeNumber"]){
        return @"chequeNumber";
    }
    if ([fieldName isEqualToString: @"RoutingNumber"]){
        return @"routingNumber";
    }
    if ([fieldName isEqualToString: @"SortCode"]){
        return @"sortCode";
    }
    if ([fieldName isEqualToString: @"AuxDomestic"]){
        return @"auxDomestic";
    }
    if ([fieldName isEqualToString: @"BSB"]){
        return @"bsb";
    }
    if ([fieldName isEqualToString: @"ExtraAuxDomestic"]){
        return @"extraAuxDomestic";
    }
    if ([fieldName isEqualToString: @"TransactionCode"]){
        return @"transactionCode";
    }
    if ([fieldName isEqualToString: @"SerialNumber"]){
        return @"serialNumber";
    }
    if ([fieldName isEqualToString: @"SortNumber"]){
        return @"sortNumber";
    }
    
    
    return fieldType.name;
}

static inline void extractCheckRecognizerResultFromCheckResult(SBSDKCheckRecognizerResult* checkResult, NSDictionary* resultMessage){
    UIImage* checkImage = checkResult.checkImage;
    
    if(checkImage != NULL){
        NSString *outputImageFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"jpg"];
        
        if ([ScanbotStorageUtils saveImage:outputImageFilePath
                                     image:checkImage
                                   quality:[SharedConfiguration defaultConfiguration].configuration.storageImageQuality]) {
            
            [resultMessage setValue:outputImageFilePath forKey:@"imageUri"];
        } else {
            SBSDKLog(@"Error saving check image");
        }
    }
    
    NSMutableDictionary* fields = [[NSMutableDictionary alloc] init];
    for(SBSDKGenericDocumentField* field in checkResult.document.fields){
        NSMutableDictionary* fieldMap = [[NSMutableDictionary alloc] init];
        
        NSMutableDictionary* value = getResultMapFromOcrResult(field.value);
        
        [fieldMap setValue:value forKey:@"value"];
        
        NSString* validationStatus = field.validationStatus == SBSDKGenericDocumentFieldValidationStatusValid ? @"Valid" : @"Invalid";
        [fieldMap setValue:validationStatus forKey:@"validationStatus"];
        
        NSString* typeName = getNormalizedCheckFieldName(field.type);
        [fields setValue:fieldMap forKey:typeName];
    }
    [resultMessage setValue:fields forKey:@"fields"];
    
    NSString* checkType = checkResult.document.type.name;
    [resultMessage setValue:checkType forKey:@"checkType"];
    
    NSString* status = checkResult.status == SBSDKCheckRecognitionResultStatusSuccess ? @"SUCCESS" : @"FAIL";
    [resultMessage setValue:status forKey:@"status"];
}

static inline SBSDKUICameraConfiguration* extractCameraConfiguration(NSDictionary* configuration) {
    SBSDKUICameraConfiguration* cameraConfiguration = [[SBSDKUICameraConfiguration alloc] init];
    
    NSString* cameraModule = [configuration objectForKey:@"cameraModule"];
    if(!cameraModule) {
        return nil;
    }
    
    if ([cameraModule isEqualToString:@"FRONT"]) {
        cameraConfiguration.camera = SBSDKCameraDevice.defaultFrontFacingCamera;
    } else if ([cameraModule isEqualToString:@"BACK"]) {
        cameraConfiguration.camera = SBSDKCameraDevice.defaultBackFacingCamera;
    }
    
    return cameraConfiguration;
}
