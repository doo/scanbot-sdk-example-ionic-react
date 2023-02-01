//
//  GenericDocumentRecognizerMapping.h
//  Scanbot SDK Example Ionic
//
//  Created by Danil Voitenko on 09.11.20.
//

#ifndef GenericDocumentRecognizerMapping_h
#define GenericDocumentRecognizerMapping_h

#include "SharedConfiguration.h"

static inline UIImage* getImageFromGdrDocuments(NSArray<SBSDKGenericDocument *>* documents, NSString* fieldKey) {
    for (SBSDKGenericDocument* document in documents) {
        SBSDKGenericDocumentField* field = [document fieldByTypeName:fieldKey];
        if (field == NULL) {
            continue;
        }
        return [field image];
    }
    return NULL;
}

static inline void putImageInGdrJsonMapFromDocuments(NSArray<SBSDKGenericDocument *>* documents,
                                                     NSMutableDictionary* jsonMap,
                                                     NSString* jsonKey,
                                                     NSString* documentKey
                                                     ) {
    @try {
        UIImage* image = getImageFromGdrDocuments(documents, documentKey);
        if (image == NULL) {
            return;
        }
        
        NSString *outputImageFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"jpg"];
        
        if ([ScanbotStorageUtils saveImage:outputImageFilePath
                                     image:image
                                   quality:[SharedConfiguration defaultConfiguration].configuration.storageImageQuality]) {
            [jsonMap setValue:outputImageFilePath forKey:jsonKey];
        } else {
            NSLog(@"WARNING: Cannot extract image from GDR document");
        }
    } @catch (NSException *exception) {
        NSLog(@"WARNING: Cannot extract image from GDR document");
        return;
    }
}

static inline void putGdrFieldFromDocuments(NSArray<SBSDKGenericDocument *>* documents,
                                            NSMutableDictionary* jsonMap,
                                            NSString* jsonKey,
                                            NSString* documentKey
                                            ) {
    for (SBSDKGenericDocument* document in documents) {
        SBSDKGenericDocumentField* field = [document fieldByTypeName:documentKey];
        if (field == NULL) {
            continue;
        }
        
        SBSDKGenericDocumentOcrResult* result = [field value];
        if (result == NULL) {
            continue;
        }
        
        NSMutableDictionary* fieldMap = getResultMapFromOcrResult(result);
        
        [jsonMap setObject:fieldMap forKey:jsonKey];
    }
}

static inline void putGdrFieldFromGenericDocumentField(NSMutableDictionary* jsonMap,
                                                       NSString* jsonKey,
                                                       SBSDKGenericDocumentField* field
                                                       ) {
    if (field != NULL) {
        NSMutableDictionary<NSString *, NSObject *> *ocrResult = getResultMapFromOcrResult(field.value);
        [jsonMap setObject:ocrResult forKey:jsonKey];
    }
}

static inline void putGdrFieldFromDriverLicenseCategory(NSMutableDictionary* jsonMap,
                                                        NSString* jsonKey,
                                                        SBSDKGenericDocumentDeDriverLicenseBackCategory* category
                                                        ) {
    NSMutableDictionary* categoryData = [[NSMutableDictionary alloc] init];
    
    putGdrFieldFromGenericDocumentField(categoryData, @"restrictions", category.restrictions);
    putGdrFieldFromGenericDocumentField(categoryData, @"validFrom", category.validFrom);
    putGdrFieldFromGenericDocumentField(categoryData, @"validUntil", category.validUntil);
    
    [jsonMap setObject:categoryData forKey:jsonKey];
}

static inline NSDictionary<NSString*, NSObject*>* extractGenericDocumentRecognizerResultFromGdrDocuments(NSArray<SBSDKGenericDocument *>* documents) {
    NSMutableDictionary<NSString *, NSObject *> *jsonMap = [NSMutableDictionary dictionary];
    
    putGdrFieldFromDocuments(documents, jsonMap, @"surname", @"Surname");
    putGdrFieldFromDocuments(documents, jsonMap, @"givenNames", @"GivenNames");
    putGdrFieldFromDocuments(documents, jsonMap, @"nationality", @"Nationality");
    putGdrFieldFromDocuments(documents, jsonMap, @"birthDate", @"BirthDate");
    putGdrFieldFromDocuments(documents, jsonMap, @"rawMrz", @"RawMRZ");
    putGdrFieldFromDocuments(documents, jsonMap, @"expiryDate", @"ExpiryDate");
    putGdrFieldFromDocuments(documents, jsonMap, @"birthplace", @"Birthplace");
    putGdrFieldFromDocuments(documents, jsonMap, @"issueDate", @"IssueDate");
    putGdrFieldFromDocuments(documents, jsonMap, @"issuingAuthority", @"IssuingAuthority");
    putGdrFieldFromDocuments(documents, jsonMap, @"address", @"Address");
    putGdrFieldFromDocuments(documents, jsonMap, @"eyeColor", @"EyeColor");
    putGdrFieldFromDocuments(documents, jsonMap, @"height", @"Height");
    putGdrFieldFromDocuments(documents, jsonMap, @"pin", @"PIN");
    putGdrFieldFromDocuments(documents, jsonMap, @"pseudonym", @"Pseudonym");
    putGdrFieldFromDocuments(documents, jsonMap, @"countryCode", @"CountryCode");
    putGdrFieldFromDocuments(documents, jsonMap, @"gender", @"Gender");
    putGdrFieldFromDocuments(documents, jsonMap, @"maidenName", @"MaidenName");
    putGdrFieldFromDocuments(documents, jsonMap, @"passportType", @"PassportType");
    putGdrFieldFromDocuments(documents, jsonMap, @"id", @"ID");
    putGdrFieldFromDocuments(documents, jsonMap, @"licenseCategories", @"LicenseCategories");
    putGdrFieldFromDocuments(documents, jsonMap, @"restrictions", @"Restrictions");
    putGdrFieldFromDocuments(documents, jsonMap, @"validFrom", @"ValidFrom");
    putGdrFieldFromDocuments(documents, jsonMap, @"validUntil", @"ValidUntil");
    
    // IMAGE(s) - These are retrieved as Bitmaps, saved in storage, and we only return the image URI
    putImageInGdrJsonMapFromDocuments(documents, jsonMap, @"photoImageUri", @"Photo");
    putImageInGdrJsonMapFromDocuments(documents, jsonMap, @"signatureImageUri", @"Signature");
    
    for (SBSDKGenericDocument* document in documents) {
        SBSDKGenericDocumentWrapper *wrapper = [document wrap];
        if ([wrapper isKindOfClass:[SBSDKGenericDocumentDePassport class]]) {
            NSMutableDictionary* mrzFields = [[NSMutableDictionary alloc] init];
            
            SBSDKGenericDocumentDePassport *passport = (SBSDKGenericDocumentDePassport*)wrapper;
            SBSDKGenericDocumentMRZ *mrz = passport.mrz;
            
            putGdrFieldFromGenericDocumentField(mrzFields, @"birthDate", mrz.birthDate);
            putGdrFieldFromGenericDocumentField(mrzFields, @"documentNumber", mrz.documentNumber);
            putGdrFieldFromGenericDocumentField(mrzFields, @"expiryDate", mrz.expiryDate);
            putGdrFieldFromGenericDocumentField(mrzFields, @"gender", mrz.gender);
            putGdrFieldFromGenericDocumentField(mrzFields, @"givenNames", mrz.givenNames);
            putGdrFieldFromGenericDocumentField(mrzFields, @"issuingAuthority", mrz.issuingAuthority);
            putGdrFieldFromGenericDocumentField(mrzFields, @"nationality", mrz.nationality);
            putGdrFieldFromGenericDocumentField(mrzFields, @"optional1", mrz.optional1);
            putGdrFieldFromGenericDocumentField(mrzFields, @"optional2", mrz.optional2);
            putGdrFieldFromGenericDocumentField(mrzFields, @"surname", mrz.surname);
            putGdrFieldFromGenericDocumentField(mrzFields, @"travelDocType", mrz.travelDocType);
            putGdrFieldFromGenericDocumentField(mrzFields, @"travelDocTypeVariant", mrz.travelDocTypeVariant);
            
            [jsonMap setObject:mrzFields forKey:@"mrz"];
        } else if ([wrapper isKindOfClass:[SBSDKGenericDocumentDeDriverLicenseBack class]]) {
            NSMutableDictionary* driverLicenseCategories = [[NSMutableDictionary alloc] init];
            
            SBSDKGenericDocumentDeDriverLicenseBack* driverLicenseBack = (SBSDKGenericDocumentDeDriverLicenseBack*)wrapper;
            SBSDKGenericDocumentDeDriverLicenseBackCategories *categories = driverLicenseBack.categories;
            
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"a", categories.a);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"a1", categories.a1);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"a2", categories.a2);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"b", categories.b);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"b1", categories.b1);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"be", categories.be);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"c", categories.c);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"c1", categories.c1);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"c1e", categories.c1e);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"ce", categories.ce);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"d", categories.d);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"d1", categories.d1);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"d1e", categories.d1e);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"de", categories.de);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"l", categories.l);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"m", categories.m);
            putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, @"t", categories.t);
            
            [jsonMap setObject:driverLicenseCategories forKey:@"categories"];
        }
    }
    
    return jsonMap;
}

static inline NSString* extractGenericDocumentTypeFromGdrDocuments(NSArray<SBSDKGenericDocument *>* documents) {
    NSString *documentType = @"";
    
    for (SBSDKGenericDocument* document in documents) {
        SBSDKGenericDocumentWrapper *wrapper = [document wrap];
        
        if ([wrapper isKindOfClass:[SBSDKGenericDocumentDePassport class]]){
            documentType = @"DePassport";
        } else if ([wrapper isKindOfClass:[SBSDKGenericDocumentDeDriverLicenseBack class]] || [wrapper isKindOfClass:[SBSDKGenericDocumentDeDriverLicenseFront class]]) {
            documentType = @"DeDriverLicense";
        } else if ([wrapper isKindOfClass:[SBSDKGenericDocumentDeIdCardBack class]] || [wrapper isKindOfClass:[SBSDKGenericDocumentDeIdCardFront class]]) {
            documentType = @"DeIdCard";
        }
    }
    
    return documentType;
}


#endif /* GenericDocumentRecognizerMapping_h */
