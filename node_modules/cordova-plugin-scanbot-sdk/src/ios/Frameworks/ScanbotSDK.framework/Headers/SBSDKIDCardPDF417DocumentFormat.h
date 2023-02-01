//
//  SBSDKIDCardPDF417DocumentFormat.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * ID card field types
 */
typedef NS_ENUM(NSInteger, SBSDKIDCardPDF417DocumentFieldType) {
    /** First name. */
    SBSDKIDCardPDF417DocumentFieldTypeFirstName,
    /** Last name. */
    SBSDKIDCardPDF417DocumentFieldTypeLastName,
    /** Document code. */
    SBSDKIDCardPDF417DocumentFieldTypeDocumentCode,
    /** Birth date. */
    SBSDKIDCardPDF417DocumentFieldTypeBirthDate,
    /** Date issued. */
    SBSDKIDCardPDF417DocumentFieldTypeDateIssued,
    /** Date expired. */
    SBSDKIDCardPDF417DocumentFieldTypeDateExpired,
    /** Optional. */
    SBSDKIDCardPDF417DocumentFieldTypeOptional1
};

/**
 * ID card field description
 */
@interface SBSDKIDCardPDF417DocumentField : NSObject
    
/** Field type */
@property (nonatomic) SBSDKIDCardPDF417DocumentFieldType type;
    
/** Field value */
@property (nonatomic, strong) NSString *value;

/** Human-readable field type name */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;
    
@end

/**
 * ID card document description
 */
@interface SBSDKIDCardPDF417DocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Fields in the parsed document */
@property (nonatomic, strong) NSArray<SBSDKIDCardPDF417DocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
