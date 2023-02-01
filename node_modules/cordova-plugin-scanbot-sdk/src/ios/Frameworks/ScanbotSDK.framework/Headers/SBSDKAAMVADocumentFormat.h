//
//  SBSDKAAMVADocument.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Known values for AAMVA fields.
 */
typedef NS_ENUM(NSInteger, SBSDKAAMVARecordFieldType) {
    /** Unknown. */
    SBSDKAAMVARecordFieldTypeUnknown,
    /** Full name. */
    SBSDKAAMVARecordFieldTypeFullName,
    /** Last name. */
    SBSDKAAMVARecordFieldTypeLastName,
    /** Family name. */
    SBSDKAAMVARecordFieldTypeFamilyName,
    /** First name. */
    SBSDKAAMVARecordFieldTypeFirstName,
    /** MIddle name or initial. */
    SBSDKAAMVARecordFieldTypeMiddleNameOrInitial,
    /** Name suffix. */
    SBSDKAAMVARecordFieldTypeNameSuffix,
    /** Name prefix. */
    SBSDKAAMVARecordFieldTypeNamePrefix,
    /** Mailing street address line 1. */
    SBSDKAAMVARecordFieldTypeMailingStreetAddress1,
    /** Mailing street address line 2. */
    SBSDKAAMVARecordFieldTypeMailingStreetAddress2,
    /** Mailing city. */
    SBSDKAAMVARecordFieldTypeMailingCity,
    /** Mailing jurisdiction code. */
    SBSDKAAMVARecordFieldTypeMailingJurisdictionCode,
    /** Mailing postal code. */
    SBSDKAAMVARecordFieldTypeMailingPostalCode,
    /** Residence street address line 1. */
    SBSDKAAMVARecordFieldTypeResidenceStreetAddress1,
    /** Residence street address line 2. */
    SBSDKAAMVARecordFieldTypeResidenceStreetAddress2,
    /** Residence city. */
    SBSDKAAMVARecordFieldTypeResidenceCity,
    /** Residence jurisdiction code. */
    SBSDKAAMVARecordFieldTypeResidenceJurisdictionCode,
    /** Residence postal code. */
    SBSDKAAMVARecordFieldTypeResidencePostalCode,
    /** License or ID number. */
    SBSDKAAMVARecordFieldTypeLicenseOrIdNumber,
    /** License classification code. */
    SBSDKAAMVARecordFieldTypeLicenseClassificationCode,
    /** License restriction code. */
    SBSDKAAMVARecordFieldTypeLicenseRestrictionCode,
    /** License endorsements code. */
    SBSDKAAMVARecordFieldTypeLicenseEndorsementsCode,
    /** Height in feet/inches. */
    SBSDKAAMVARecordFieldTypeHeightInFeetInches,
    /** Height in CM. */
    SBSDKAAMVARecordFieldTypeHeightInCM,
    /** Weight in LBS. */
    SBSDKAAMVARecordFieldTypeWeightInLBS,
    /** Weight in KG. */
    SBSDKAAMVARecordFieldTypeWeightInKG,
    /** Eyes color. */
    SBSDKAAMVARecordFieldTypeEyesColor,
    /** Hair color. */
    SBSDKAAMVARecordFieldTypeHairColor,
    /** License expiration date. */
    SBSDKAAMVARecordFieldTypeLicenseExpirationDate,
    /** Date of birth. */
    SBSDKAAMVARecordFieldTypeDateOfBirth,
    /** Sex. */
    SBSDKAAMVARecordFieldTypeSex,
    /** License or ID document issue date. */
    SBSDKAAMVARecordFieldTypeLicenseOrIdDocumentIssueDate,
    /** Issue timestamp. */
    SBSDKAAMVARecordFieldTypeIssueTimestamp,
    /** Number of duplicates. */
    SBSDKAAMVARecordFieldTypeNumberOfDuplicates,
    /** Medical indicator codes. */
    SBSDKAAMVARecordFieldTypeMedicalIndicatorCodes,
    /** Organ donor. */
    SBSDKAAMVARecordFieldTypeOrganDonor,
    /** Non-resident indicator. */
    SBSDKAAMVARecordFieldTypeNonResidentIndicator,
    /** Unique customer identifier. */
    SBSDKAAMVARecordFieldTypeUniqueCustomerIdentifier,
    /** Social security number. */
    SBSDKAAMVARecordFieldTypeSocialSecurityNumber,
    /** Suffix. */
    SBSDKAAMVARecordFieldTypeSuffix,
    /** Prefix. */
    SBSDKAAMVARecordFieldTypePrefix,
    /** Virginia-specific class. */
    SBSDKAAMVARecordFieldTypeVirginiaSpecificClass,
    /** Virginia-specific restrictions. */
    SBSDKAAMVARecordFieldTypeVirginiaSpecificRestrictions,
    /** Virginia-specific endorsements. */
    SBSDKAAMVARecordFieldTypeVirginiaSpecificEndorsements,
    /** Weight range. */
    SBSDKAAMVARecordFieldTypePhysicalDescriptionWeightRange,
    /** Document discriminator. */
    SBSDKAAMVARecordFieldTypeDocumentDiscriminator,
    /** Country of territory of issuance. */
    SBSDKAAMVARecordFieldTypeCountryTerritoryOfIssuance,
    /** Federal commercial vehicle codes. */
    SBSDKAAMVARecordFieldTypeFederalCommercialVehicleCodes,
    /** Place of birth. */
    SBSDKAAMVARecordFieldTypePlaceOfBirth,
    /** Audit information. */
    SBSDKAAMVARecordFieldTypeAuditInformation,
    /** Inventory control number. */
    SBSDKAAMVARecordFieldTypeInventoryControlNumber,
    /** Race or ethnicity. */
    SBSDKAAMVARecordFieldTypeRaceEthnicity,
    /** Standard vehicle classification. */
    SBSDKAAMVARecordFieldTypeStandardVehicleClassification,
    /** Standard endorsement code. */
    SBSDKAAMVARecordFieldTypeStandardEndorsementCode,
    /** Standard restriction code. */
    SBSDKAAMVARecordFieldTypeStandardRestrictionCode,
    /** Jurisdiction-specific vehicle classification description. */
    SBSDKAAMVARecordFieldTypeJurisdictionSpecificVehicleClassificationDescription,
    /** Jurisdiction-specific. */
    SBSDKAAMVARecordFieldTypeJurisdictionSpecific,
    /** Jurisdiction-specific restriction code description. */
    SBSDKAAMVARecordFieldTypeJurisdictionSpecificRestrictionCodeDescription,
    /** Compliance type. */
    SBSDKAAMVARecordFieldTypeComplianceType,
    /** Card revision date. */
    SBSDKAAMVARecordFieldTypeCardRevisionDate,
    /** HazMat endorsement expiry date. */
    SBSDKAAMVARecordFieldTypeHazMatEndorsementExpiryDate,
    /** Limited duration document indicator. */
    SBSDKAAMVARecordFieldTypeLimitedDurationDocumentIndicator,
    /** Family name truncation. */
    SBSDKAAMVARecordFieldTypeFamilyNameTruncation,
    /** First name truncation. */
    SBSDKAAMVARecordFieldTypeFirstNamesTruncation,
    /** Middle names truncation. */
    SBSDKAAMVARecordFieldTypeMiddleNamesTruncation,
    /** Under 18 until. */
    SBSDKAAMVARecordFieldTypeUnder18Until,
    /** Under 19 until. */
    SBSDKAAMVARecordFieldTypeUnder19Until,
    /** Under 21 until. */
    SBSDKAAMVARecordFieldTypeUnder21Until,
    /** Organ donor indicator. */
    SBSDKAAMVARecordFieldTypeOrganDonorIndicator,
    /** Veteran indicator. */
    SBSDKAAMVARecordFieldTypeVeteranIndicator,
    /** Permit classification code. */
    SBSDKAAMVARecordFieldTypePermitClassificationCode,
    /** Permit expiration date. */
    SBSDKAAMVARecordFieldTypePermitExpirationDate,
    /** Permit identifier. */
    SBSDKAAMVARecordFieldTypePermitIdentifier,
    /** Permit issue date. */
    SBSDKAAMVARecordFieldTypePermitIssueDate,
    /** Permit restriction code. */
    SBSDKAAMVARecordFieldTypePermitRestrictionCode,
    /** Permit endorsement code. */
    SBSDKAAMVARecordFieldTypePermitEndorsementCode,
    /** Court restriction code. */
    SBSDKAAMVARecordFieldTypeCourtRestrictionCode,
};

/**
 * AAMVA document subfile field.
 */
@interface SBSDKAAMVADocumentSubfileField : NSObject
    
/** Field type. */
@property (nonatomic) SBSDKAAMVARecordFieldType type;

/** Field type string. */
@property (nonatomic, strong) NSString *typeString;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;
    
/** Field formatted value. */
@property (nonatomic, strong) NSString *value;

/** Field raw value. */
@property (nonatomic, strong) NSString *rawValue;

@end

/**
 * AAMVA document subfile information.
 */
@interface SBSDKAAMVADocumentSubfile : NSObject

/** Type of this subfile. */
@property (nonatomic, strong) NSString *subFileType;

/** Subfile raw header string. */
@property (nonatomic, strong) NSString *subFileRawHeaderString;

/** Parsed fields. */
@property (nonatomic, strong) NSArray<SBSDKAAMVADocumentSubfileField *> *fields;

@end

/**
 * AAMVA document information.
 */
@interface SBSDKAAMVADocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Raw header string. */
@property (nonatomic, strong) NSString *headerRawString;

/** AAMVA file type. */
@property (nonatomic, strong) NSString *fileType;

/** Issuer identification number. */
@property (nonatomic, strong) NSString *issuerIdentificationNumber;

/** Document version string. */
@property (nonatomic, strong) NSString *AAMVAVersionNumber;

/** Jurisdiction version string. */
@property (nonatomic, strong) NSString *jurisdictionVersionNumber;

/** Number of entries in the documents. */
@property (nonatomic) NSInteger numberOfEntries;

/** Vector of document's subfiles. */
@property (nonatomic, strong) NSArray<SBSDKAAMVADocumentSubfile *> *subfiles;

@end

NS_ASSUME_NONNULL_END
