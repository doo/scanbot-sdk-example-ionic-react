//
//  SBSDKSwissQRCodeDocumentFormat.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 11.02.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/** The version number of the Swiss QR code. */
typedef NS_ENUM(NSInteger, SBSDKSwissQRCodeVersion) {
    /** Version 1.0. */
    SBSDKSwissQRCodeVersion_V1_0,

    /** Version 2.0. */
    SBSDKSwissQRCodeVersion_V2_0,
    
    /** Version 2.1. */
    SBSDKSwissQRCodeVersion_V2_1
};

/** The type of one Swiss QR code field. */
typedef NS_ENUM(NSInteger, SBSDKSwissQRCodeFieldType) {
    /** The encoding. */
    SBSDKSwissQRCodeFieldTypeEncoding,

    /** The IBAN. */
    SBSDKSwissQRCodeFieldTypeIBAN,
    
    /** The payees address type. V2 only. */
    SBSDKSwissQRCodeFieldTypePayeeAddressType,
    
    /** The payees name. */
    SBSDKSwissQRCodeFieldTypePayeeName,
    
    /** The payees street or address line 1. */
    SBSDKSwissQRCodeFieldTypePayeeStreetOrAddressLine1,
    
    /** The payees building or address line 2. */
    SBSDKSwissQRCodeFieldTypePayeeBuildingOrAddressLine2,

    /** The payees postal code. */
    SBSDKSwissQRCodeFieldTypePayeePostalCode,

    /** The payees place. */
    SBSDKSwissQRCodeFieldTypePayeePlace,

    /** The payees country. */
    SBSDKSwissQRCodeFieldTypePayeeCountry,

    /** The final payees address type. V2 only. */
    SBSDKSwissQRCodeFieldTypeFinalPayeeAddressType,

    /** The final payees name. */
    SBSDKSwissQRCodeFieldTypeFinalPayeeName,

    /** The final payees street or address line 1. */
    SBSDKSwissQRCodeFieldTypeFinalPayeeStreetOrAddressLine1,

    /** The final payees building or address line 2. */
    SBSDKSwissQRCodeFieldTypeFinalPayeeBuildingOrAddressLine2,

    /** The final payees postal code. */
    SBSDKSwissQRCodeFieldTypeFinalPayeePostalCode,

    /** The final payees place. */
    SBSDKSwissQRCodeFieldTypeFinalPayeePlace,

    /** The final payees country. */
    SBSDKSwissQRCodeFieldTypeFinalPayeeCountry,

    /** The amount. */
    SBSDKSwissQRCodeFieldTypeAmount,

    /** The currency. */
    SBSDKSwissQRCodeFieldTypeCurrency,

    /** The due date. V1 only. */
    SBSDKSwissQRCodeFieldTypeDueDate,

    /** The debtors address type. V2 only. */
    SBSDKSwissQRCodeFieldTypeDebtorAddressType,

    /** The debtors name. */
    SBSDKSwissQRCodeFieldTypeDebtorName,
    
    /** The debtors street or address line 1. */
    SBSDKSwissQRCodeFieldTypeDebtorStreetOrAddressLine1,
    
    /** The debtors building or address line 2.*/
    SBSDKSwissQRCodeFieldTypeDebtorBuildingOrAddressLine2,
    
    /** The debtors postal code. */
    SBSDKSwissQRCodeFieldTypeDebtorPostalCode,
    
    /** The debtors place. */
    SBSDKSwissQRCodeFieldTypeDebtorPlace,
    
    /** The debtors country. */
    SBSDKSwissQRCodeFieldTypeDebtorCountry,
    
    /** The payment reference type. */
    SBSDKSwissQRCodeFieldTypePaymentReferenceType,
    
    /** The payment reference. */
    SBSDKSwissQRCodeFieldTypePaymentReference,
    
    /** Additional info. Unstructured. */
    SBSDKSwissQRCodeFieldTypeAdditionalInfoUnstructured,
    
    /** Additional info trailer. V2 only. */
    SBSDKSwissQRCodeFieldTypeAdditionalInfoTrailer,
    
    /** Additional billing information. V2 only. */
    SBSDKSwissQRCodeFieldTypeAdditionalBillingInformation,
    
    /** The alternative procedure parameter. */
    SBSDKSwissQRCodeFieldTypeAlternativeProcedureParameter
};





/** A class describing one data field of a Swiss QR code. */
@interface SBSDKSwissQRCodeDocumentField : NSObject

/** The fields type. */
@property(nonatomic, assign) SBSDKSwissQRCodeFieldType type;
    
/** The fields value. */
@property(nonatomic, strong) NSString *value;

/** Human-readable field type name. */
@property(nonatomic, readonly) NSString *typeHumanReadableString;

@end






/** The document format of a Swiss QR code. */
@interface SBSDKSwissQRCodeDocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** The version number of the Swiss QR Code. */
@property(nonatomic, assign) SBSDKSwissQRCodeVersion version;

/** The fields of the Swiss QR code. */
@property(nonatomic, strong) NSArray<SBSDKSwissQRCodeDocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
