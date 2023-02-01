//
//  SBSDKMRZRecognizerResult.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 28.09.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKMachineReadableZoneRecognizerTextLine.h"
#import "SBSDKMachineReadableZoneRecognizerField.h"
#import "SBSDKMachineReadableZoneRecognizerResultCheckDigit.h"

/**
 Type classifier for machine-readable-zone document types.
 */
typedef NS_ENUM(NSInteger, SBSDKMachineReadableZoneRecognizerResultDocumentType) {
    
    /** The document type is unknown. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypeUndefined = 4,
    
    /** The document is a passport. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypePassport = 0,
    
    /** The document is a visa. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypeVisa = 1,
    
    /** The document is a travel document. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypeTravelDocument = 2,
    
    /** The document is an ID card. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypeIDCard = 3,
    
    /** The document is a Swiss driver license. */
    SBSDKMachineReadableZoneRecognizerResultDocumentTypeSwissDriverLicense = 5,
};

/**
 * A class encapsulating a machine-readable-zone recognition result.
 */
@interface SBSDKMachineReadableZoneRecognizerResult : NSObject

/** Whether the recognition was successful or not. */
@property (nonatomic) BOOL recognitionSuccessful;

/** The type of the recognized document. */
@property (nonatomic) SBSDKMachineReadableZoneRecognizerResultDocumentType documentType;

/** The document code. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *documentCodeField;

/** The issuing state or organization. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *issuingStateOrOrganizationField;

/** The issuing department. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *departmentOfIssuanceField;

/** The first name. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *firstNameField;

/** The last name. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *lastNameField;

/** The nationality. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *nationalityField;

/** The date of birth. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *dateOfBirthField;

/** The gender. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *genderField;

/** The expiration date. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *dateOfExpiryField;

/** The personal number. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *personalNumberField;

/** The travel document type. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *travelDocumentTypeField;

/** The optional field #1. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *optional1Field;

/** The optional field #2. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *optional2Field;

/** The discreet issuing state or organization. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *discreetIssuingStateOrOrganizationField;

/** The kind of document in Swiss driver license. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *kindOfDocumentField;

/** The PIN number in Swiss driver license. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *PINNumberField;

/** The language code in Swiss driver license. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *languageCodeField;

/** The version of the document in Swiss driver license. */
@property (nonatomic, strong, nullable) SBSDKMachineReadableZoneRecognizerField *versionNumberField;

/** An array of all recognized text lines. */
@property (nonatomic, strong, nonnull) NSArray<SBSDKMachineReadableZoneRecognizerTextLine *> *textLines;

/** An array of all recognized fields. */
@property (nonatomic, strong, nonnull) NSArray<SBSDKMachineReadableZoneRecognizerField *> *fields;

/** An array of recognized checkdigits. */
@property (nonatomic, strong, nonnull) NSArray<SBSDKMachineReadableZoneRecognizerResultCheckDigit *> *checkDigits;

/**
 * Returns a string representation of all fields.
 * @return String, containing the field names, values and confidences of all fields.
 */
- (nonnull NSString *)stringRepresentation;

/**
 * Returns a string representation of all fields.
 * @return String, containing the field names and values of all fields.
 */
- (nonnull NSString *)stringRepresentationWithoutConfidence;

/**
 * Number of successfully validated check digits.
 */
@property(nonatomic) int validCheckDigitsCount;

/**
 * Total number of check digits as required by the travel document type
 */
@property(nonatomic) int checkDigitsCount;


/** The document code. */
@property (nonatomic, strong, nullable) NSString *documentCode __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The issuing state or organization. */
@property (nonatomic, strong, nullable) NSString *issuingStateOrOrganization __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The issuing department. */
@property (nonatomic, strong, nullable) NSString *departmentOfIssuance __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The first name. */
@property (nonatomic, strong, nullable) NSString *firstName __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The last name. */
@property (nonatomic, strong, nullable) NSString *lastName __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The nationality. */
@property (nonatomic, strong, nullable) NSString *nationality __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The date of birth. */
@property (nonatomic, strong, nullable) NSString *dateOfBirth __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The gender. */
@property (nonatomic, strong, nullable) NSString *gender __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The expiration date. */
@property (nonatomic, strong, nullable) NSString *dateOfExpiry __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The personal number. */
@property (nonatomic, strong, nullable) NSString *personalNumber __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The travel document type. */
@property (nonatomic, strong, nullable) NSString *travelDocumentType __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The optional field #1. */
@property (nonatomic, strong, nullable) NSString *optional1 __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The optional field #2. */
@property (nonatomic, strong, nullable) NSString *optional2 __attribute__((deprecated("Please use appropriate field getter instead.")));

/** The discreet issuing state or organization. */
@property (nonatomic, strong, nullable) NSString *discreetIssuingStateOrOrganization __attribute__((deprecated("Please use appropriate field getter instead.")));

@end
