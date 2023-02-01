//
//  SBSDKMedicalCertificateRecognizerResult.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 14.11.17.
//  Copyright © 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SBSDKMedicalCertificateRecognizerCheckboxResult.h"
#import "SBSDKMedicalCertificateRecognizerDateResult.h"
#import "SBSDKMedicalCertificateRecognizerResultPatientField.h"

/** The form type of a recognized medical certificate. */
typedef NS_ENUM(NSInteger, SBSDKMedicalCertificateRecognizerFormType) {
    /** Unknown. */
    SBSDKMedicalCertificateRecognizerFormTypeUnknown = -1,
    
    /** Type 1A. */
    SBSDKMedicalCertificateRecognizerFormType_1A,

    /** Type 1B. */
    SBSDKMedicalCertificateRecognizerFormType_1B,

    /** Type 1C. */
    SBSDKMedicalCertificateRecognizerFormType_1C,

    /** Type 1D. */
    SBSDKMedicalCertificateRecognizerFormType_1D,

    /** Type 21A. */
    SBSDKMedicalCertificateRecognizerFormType_21A,
    
    /** Type 1B Custom.*/
    SBSDKMedicalCertificateRecognizerFormType_1B_CUSTOM
};

/** This class describes the results of a medical certificate recognition. */
@interface SBSDKMedicalCertificateRecognizerResult : NSObject

/** The form type of medical certificate. */
@property (nonatomic, assign) SBSDKMedicalCertificateRecognizerFormType formType;

/** Array of patient information fields */
@property (nullable, nonatomic, strong) NSArray<SBSDKMedicalCertificateRecognizerResultPatientField *> *patientFields;

/** Array of found checkboxes */
@property (nullable, nonatomic, strong) NSArray<SBSDKMedicalCertificateRecognizerCheckboxResult *> *checkboxes;

/** Array of found dates */
@property (nullable, nonatomic, strong) NSArray<SBSDKMedicalCertificateRecognizerDateResult *> *dates;

/** Defines whether recognition was successful */
@property (nonatomic) BOOL recognitionSuccessful;

/** A photo of the medical certificate. */
@property (nullable, nonatomic, strong) UIImage* image;

/**
 * @return Human readable english text for the receivers form type.
 */
- (nullable NSString *)stringForFormType;

/**
 * @param checkbox A medical certificates checkbox result.
 * @return Human readable english text for the given checkbox' type.
 */
- (nullable NSString *)stringForCheckboxResultType:(nonnull SBSDKMedicalCertificateRecognizerCheckboxResult *)checkbox;

/**
 * @param date A medical certificates date result.
 * @return Human readable english text for the given date`s type.
 */
- (nullable NSString *)stringForDateResultType:(nonnull SBSDKMedicalCertificateRecognizerDateResult *)date;

/**
 * @param patientField A medical certificates patients field.
 * @return Human readable english text for the given patient fields type.
 */
- (nullable NSString *)stringForPatientFieldType:(nonnull SBSDKMedicalCertificateRecognizerResultPatientField *)patientField;


/** @return Human readable english text for the entire medical certificate. */
- (nonnull NSString *)stringRepresentation;

@end
