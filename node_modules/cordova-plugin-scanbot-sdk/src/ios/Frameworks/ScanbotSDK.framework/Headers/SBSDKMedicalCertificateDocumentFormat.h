//
//  SBSDKMedicalCertificateDocumentFormat.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Medical certificate document field types.
 */
typedef NS_ENUM(NSInteger, SBSDKMedicalCertificateDocumentFieldType) {
    /** Requires care. */
    SBSDKMedicalCertificateDocumentFieldTypeRequiresCare,
    /** Accident. */
    SBSDKMedicalCertificateDocumentFieldTypeAccident,
    /** Initial certificate. */
    SBSDKMedicalCertificateDocumentFieldTypeInitialCertificate,
    /** Renewed certificate. */
    SBSDKMedicalCertificateDocumentFieldTypeRenewedCertificate,
    /** Work accident. */
    SBSDKMedicalCertificateDocumentFieldTypeWorkAccident,
    /** Assigned to accident insurance doctor. */
    SBSDKMedicalCertificateDocumentFieldTypeAssignedToAccidentInsuranceDoctor,
    /** Incapable of work since. */
    SBSDKMedicalCertificateDocumentFieldTypeIncapableOfWorkSince,
    /** Incapable of work until. */
    SBSDKMedicalCertificateDocumentFieldTypeIncapableOfWorkUntil,
    /** Diagnosed on. */
    SBSDKMedicalCertificateDocumentFieldTypeDiagnosedOn,
    /** Document date. */
    SBSDKMedicalCertificateDocumentFieldTypeDocumentDate,
    /** Birth date. */
    SBSDKMedicalCertificateDocumentFieldTypeBirthDate,
    /** First name. */
    SBSDKMedicalCertificateDocumentFieldTypeFirstName,
    /** Last name. */
    SBSDKMedicalCertificateDocumentFieldTypeLastName,
    /** Diagnose. */
    SBSDKMedicalCertificateDocumentFieldTypeDiagnose,
    /** Health insurance number. */
    SBSDKMedicalCertificateDocumentFieldTypeHealthInsuranceNumber,
    /** Insured person number. */
    SBSDKMedicalCertificateDocumentFieldTypeInsuredPersonNumber,
    /** Status. */
    SBSDKMedicalCertificateDocumentFieldTypeStatus,
    /** Place of operation number. */
    SBSDKMedicalCertificateDocumentFieldTypePlaceOfOperationNumber,
    /** Doctor number. */
    SBSDKMedicalCertificateDocumentFieldTypeDoctorNumber
};

/**
 * Medical certificate field description.
 */
@interface SBSDKMedicalCertificateDocumentField : NSObject
    
/** Field type. */
@property (nonatomic) SBSDKMedicalCertificateDocumentFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;
    
/** Field value. */
@property (nonatomic, strong) NSString *value;

@end

/**
 * Class for parsing data obtained from QR code on medical certificates.
 */
@interface SBSDKMedicalCertificateDocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Document fields. */
@property (nonatomic, strong) NSArray<SBSDKMedicalCertificateDocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
