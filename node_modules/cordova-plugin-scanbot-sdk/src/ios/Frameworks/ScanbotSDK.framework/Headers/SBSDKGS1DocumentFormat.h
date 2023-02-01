//
//  SBSDKGS1DocumentFormat.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 26.01.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/** A GS1 document field validation status. */
typedef NS_ENUM(NSInteger, SBSDKGS1SystemElementValidationStatus) {
    
    /** The validation status is valid. */
    SBSDKGS1SystemElementValidationStatusValid,
    
    /** The validation status is invalid. */
    SBSDKGS1SystemElementValidationStatusInvalid
};

/** A class describing a data field of a GS1 code. */
@interface SBSDKGS1DocumentField : NSObject

/** The GS1 application identifier. Also contains variable part, e.g. decimal point place. */
@property (nonatomic, strong) NSString *applicationIdentifier;

/** The description defined in a GS1 specification, if standard. */
@property (nonatomic, strong) NSString *fieldDescription;

/** The data title defined in GS1 specification, if standard. */
@property (nonatomic, strong) NSString *dataTitle;

/** The unprocessed raw field value. */
@property (nonatomic, strong) NSString *rawValue;

/** Indicates whether the application identifier of the field is defined by the GS1 standard. */
@property (nonatomic, assign) BOOL standard;

/** Contains the parse error, if any was found during the parsing. */
@property (nonatomic, assign) SBSDKGS1SystemElementValidationStatus validationStatus;

@end

/** The document format of a GS1 code. */
@interface SBSDKGS1DocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** The fields of the GS1 code. */
@property (nonatomic, strong) NSArray<SBSDKGS1DocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
