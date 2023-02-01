//
//  SBSDKMedicalPlanDocumentFormat.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 5/23/19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * German medical plan document subheading prescription information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanSubheadingPrescriptionFieldType){
    /** General information. */
    SBSDKMedicalPlanSubheadingPrescriptionFieldTypeGeneralInformation,
    /** Prescription free text. */
    SBSDKMedicalPlanSubheadingPrescriptionFieldTypePrescriptionFreeText
};

/**
 * German medical plan document subheading prescription information description field.
 */
@interface SBSDKMedicalPlanSubheadingPrescriptionField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanSubheadingPrescriptionFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document subheading prescription information description.
 */
@interface SBSDKMedicalPlanSubheadingPrescription : NSObject

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanSubheadingPrescriptionField *> *fields;

@end

/**
 * German medical plan document medicine substance information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanMedicineSubstanceFieldType) {
    /** Active substance. */
    SBSDKMedicalPlanMedicineSubstanceFieldTypeActiveSubstance,
    /** Potency. */
    SBSDKMedicalPlanMedicineSubstanceFieldTypePotency
};

/**
 * German medical plan document medicine substance information description field.
 */
@interface SBSDKMedicalPlanMedicineSubstanceField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanMedicineSubstanceFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document medicine substance information description.
 */
@interface SBSDKMedicalPlanMedicineSubstance : NSObject

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanMedicineSubstanceField *> *fields;

@end

/**
 * German medical plan document medicine information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanMedicineFieldType) {
    /** Pharmaceutical number. */
    SBSDKMedicalPlanMedicineFieldTypePharmaceuticalNumber,
    /** Drug name. */
    SBSDKMedicalPlanMedicineFieldTypeDrugName,
    /** Dosage form. */
    SBSDKMedicalPlanMedicineFieldTypeDosageForm,
    /** Dosage form free text. */
    SBSDKMedicalPlanMedicineFieldTypeDosageFormFreeText,
    /** Morning. */
    SBSDKMedicalPlanMedicineFieldTypeMorning,
    /** Midday. */
    SBSDKMedicalPlanMedicineFieldTypeMidday,
    /** Evening. */
    SBSDKMedicalPlanMedicineFieldTypeEvening,
    /** Night. */
    SBSDKMedicalPlanMedicineFieldTypeNight,
    /** Dosage free text. */
    SBSDKMedicalPlanMedicineFieldTypeDosageFreeText,
    /** Dosage unit. */
    SBSDKMedicalPlanMedicineFieldTypeDosingUnit,
    /** Dosage unit free text. */
    SBSDKMedicalPlanMedicineFieldTypeDosingUnitFreeText,
    /** Relevant info. */
    SBSDKMedicalPlanMedicineFieldTypeRelevantInfo,
    /** Reason for treatment. */
    SBSDKMedicalPlanMedicineFieldTypeReasonForTreatment,
    /** General notes. */
    SBSDKMedicalPlanMedicineFieldTypeGeneralNotes,
};

/**
 * German medical plan document medicine information description field.
 */
@interface SBSDKMedicalPlanMedicineField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanMedicineFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document medicine information description.
 */
@interface SBSDKMedicalPlanMedicine : NSObject

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanMedicineField *> *fields;

/** Substances. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanMedicineSubstance *> *substances;

@end

/**
 * German medical plan document subheading information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanStandardSubheadingFieldType) {
    /** Keywords. */
    SBSDKMedicalPlanStandardSubheadingFieldTypeKeyWords,
    /** Free text. */
    SBSDKMedicalPlanStandardSubheadingFieldTypeSubheadingFreeText,
};

/**
 * German medical plan document subheading information description field.
 */
@interface SBSDKMedicalPlanStandardSubheadingField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanStandardSubheadingFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document subheading information description.
 */
@interface SBSDKMedicalPlanStandardSubheading : NSObject

/** General notes. */
@property (nonatomic, strong) NSArray<NSString *> *generalNotes;

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanStandardSubheadingField *> *fields;

/** Medicines. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanMedicine *> *medicines;

/** Prescriptions. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanSubheadingPrescription *> *prescriptions;

@end

/**
 * German medical plan document doctor information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanDoctorFieldType) {
    /** Issuer name. */
    SBSDKMedicalPlanDoctorFieldTypeIssuerName,
    /** Doctor number. */
    SBSDKMedicalPlanDoctorFieldTypeDoctorNumber,
    /** Pharmacy ID. */
    SBSDKMedicalPlanDoctorFieldTypePharmacyID,
    /** Hospital ID. */
    SBSDKMedicalPlanDoctorFieldTypeHospitalID,
    /** Street. */
    SBSDKMedicalPlanDoctorFieldTypeStreet,
    /** Postal code. */
    SBSDKMedicalPlanDoctorFieldTypePostalCode,
    /** Place. */
    SBSDKMedicalPlanDoctorFieldTypePlace,
    /** Telephone number. */
    SBSDKMedicalPlanDoctorFieldTypeTelephoneNumber,
    /** Email. */
    SBSDKMedicalPlanDoctorFieldTypeEmail,
    /** Issuing date and time. */
    SBSDKMedicalPlanDoctorFieldTypeIssuingDateAndTime
};

/**
 * German medical plan document doctor information description field.
 */
@interface SBSDKMedicalPlanDoctorField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanDoctorFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document doctor information description.
 */
@interface SBSDKMedicalPlanDoctorInformation : NSObject

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanDoctorField *> *fields;

@end

/**
 * German medical plan document patient information description field type.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalPlanPatientFieldType) {
    /** First name. */
    SBSDKMedicalPlanPatientFieldTypeFirstName,
    /** Last name. */
    SBSDKMedicalPlanPatientFieldTypeLastName,
    /** Title. */
    SBSDKMedicalPlanPatientFieldTypeTitle,
    /** Prename. */
    SBSDKMedicalPlanPatientFieldTypePreName,
    /** Suffix. */
    SBSDKMedicalPlanPatientFieldTypeSuffix,
    /** Patient ID. */
    SBSDKMedicalPlanPatientFieldTypePatientID,
    /** Birth date. */
    SBSDKMedicalPlanPatientFieldTypeBirthDate,
    /** Gender. */
    SBSDKMedicalPlanPatientFieldTypeGender,
    /** Weight. */
    SBSDKMedicalPlanPatientFieldTypeWeight,
    /** Height. */
    SBSDKMedicalPlanPatientFieldTypeHeight,
    /** Creatinine value. */
    SBSDKMedicalPlanPatientFieldTypeCreatinineValue,
    /** Allergies and intolerances. */
    SBSDKMedicalPlanPatientFieldTypeAllergiesAndIntolerances,
    /** Breast feeding. */
    SBSDKMedicalPlanPatientFieldTypeBreastFeeding,
    /** Pregnant. */
    SBSDKMedicalPlanPatientFieldTypePregnant,
    /** Patient free text. */
    SBSDKMedicalPlanPatientFieldTypePatientFreeText
};

/**
 * German medical plan document patient information description field.
 */
@interface SBSDKMedicalPlanPatientField : NSObject

/** Field value. */
@property (nonatomic, strong) NSString *value;

/** Field type. */
@property (nonatomic) SBSDKMedicalPlanPatientFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * German medical plan document patient information description.
 */
@interface SBSDKMedicalPlanPatientInformation : NSObject

/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanPatientField *> *fields;

@end

/**
 * German medical plan document description structure.
 */
@interface SBSDKMedicalPlanDocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Identifier. */
@property (nonatomic, strong) NSString *GUID;

/** Current page. */
@property (nonatomic) NSInteger currentPage;

/** Total number of pages in document. */
@property (nonatomic) NSInteger totalNumberOfPages;

/** Document version. */
@property (nonatomic, strong) NSString *documentVersionNumber;

/** Patch version. */
@property (nonatomic, strong) NSString *patchVersionNumber;

/** Language and country code. */
@property (nonatomic, strong) NSString *languageCountryCode;

/** Patient information. */
@property (nonatomic, strong) SBSDKMedicalPlanPatientInformation *patient;

/** Doctor information. */
@property (nonatomic, strong) SBSDKMedicalPlanDoctorInformation *doctor;

/** Subheadings. */
@property (nonatomic, strong) NSArray<SBSDKMedicalPlanStandardSubheading *> *subheadings;

@end

NS_ASSUME_NONNULL_END
