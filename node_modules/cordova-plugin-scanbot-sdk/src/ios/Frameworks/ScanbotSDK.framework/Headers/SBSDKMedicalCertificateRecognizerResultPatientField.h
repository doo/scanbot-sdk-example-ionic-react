//
//  SBSDKMedicalCertificateRecognizerResultPatientField.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 6/6/19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The various types of fields inside the patient information field of a medical certificate. */
typedef NS_ENUM(NSInteger, SBSDKMedicalCertificateRecognizerResultPatientFieldType) {
    
    /** The health insurance provider. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeInsuranceProvider = 0,
    
    /** The patients first name. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeFirstName = 1,

    /** The patients last name. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeLastName = 2,
    
    /** The patients address 1. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeAddressString1 = 3,
    
    /** The patients address 2. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeAddressString2 = 4,
    
    /** The patients diagnose. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeDiagnose = 5,
    
    /** The patients health insurance number. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeHealthInsuranceNumber = 6,
    
    /** The patients person number. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeInsuredPersonNumber = 7,
    
    /** The patients status. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeStatus = 8,
    
    /** The place of operation number. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypePlaceOfOperationNumber = 9,
    
    /** The doctors number. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeDoctorNumber = 10,

    /** An undefined field. */
    SBSDKMedicalCertificateRecognizerResultPatientFieldTypeUndefined = -1
};

NS_ASSUME_NONNULL_BEGIN

/** This class represents one entry of patient information recognized by medical certificate recognition. */
@interface SBSDKMedicalCertificateRecognizerResultPatientField : NSObject

/** The type of the field. */
@property (nonatomic) SBSDKMedicalCertificateRecognizerResultPatientFieldType type;

/** The raw string value of the field. */
@property (nonatomic, strong) NSString *value;

@end

NS_ASSUME_NONNULL_END
