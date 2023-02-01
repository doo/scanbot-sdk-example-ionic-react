//
//  SBSDKSEPADocumentFormat.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * SEPA document field types,
 */
typedef NS_ENUM(NSInteger, SBSDKSEPADocumentFieldType) {
    /** Service tag. */
    SBSDKSEPADocumentFieldTypeServiceTag,
    /** Version. */
    SBSDKSEPADocumentFieldTypeVersion,
    /** Character set. */
    SBSDKSEPADocumentFieldTypeCharacterSet,
    /** Identification. */
    SBSDKSEPADocumentFieldTypeIdentification,
    /** Receiver's IBAN. */
    SBSDKSEPADocumentFieldTypeReceiverIBAN,
    /** Receiver's BIC. */
    SBSDKSEPADocumentFieldTypeReceiverBIC,
    /** Receiver's name. */
    SBSDKSEPADocumentFieldTypeReceiverName,
    /** Amount. */
    SBSDKSEPADocumentFieldTypeAmount,
    /** Purpose */
    SBSDKSEPADocumentFieldTypePurpose,
    /** Remittance*/
    SBSDKSEPADocumentFieldTypeRemittance,
    /** Information*/
    SBSDKSEPADocumentFieldTypeInformation
};

/**
 * SEPA document field information.
 */
@interface SBSDKSEPADocumentField : NSObject
    
/** Field type. */
@property (nonatomic) SBSDKSEPADocumentFieldType type;
    
/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

/** Field value. */
@property (nonatomic, strong) NSString *value;

@end

    
/**
 * SEPA parsed document information.
 */
@interface SBSDKSEPADocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Document fields. */
@property (nonatomic, strong) NSArray<SBSDKSEPADocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
