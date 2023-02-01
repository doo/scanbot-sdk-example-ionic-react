//
//  SBSDKMedicalCertificateRecognizerDateResult.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 15.11.17.
//  Copyright © 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Type classifiers for dates recognized on medical certificates.
 */
typedef NS_ENUM(NSUInteger, SBSDKMedicalCertificateRecognizerDateResultType) {
	/** The date describes since when the employee is incapable of work. */
    SBSDKMedicalCertificateRecognizerDateResultTypeIncapableOfWorkSince,
	
    /** The date describes until when the employee is incapable of work. */
    SBSDKMedicalCertificateRecognizerDateResultTypeIncapableOfWorkUntil,
	
    /** The date describes the day of diagnosis. */
    SBSDKMedicalCertificateRecognizerDateResultTypeDiagnosedOn,
    
    /** The date since when the child needs care. */
    SBSDKMedicalCertificateRecognizerDateResultTypeChildNeedsCareFrom,
    
    /** The date until the childs needs care. */
    SBSDKMedicalCertificateRecognizerDateResultTypeChildNeedsCareUntil,
    
    /** Patient birth date. */
    SBSDKMedicalCertificateRecognizerDateResultTypeBirthDate,
    
    /** Document date. */
    SBSDKMedicalCertificateRecognizerDateResultTypeDocumentDate,
	
    /** The date could not be classified. */
    SBSDKMedicalCertificateRecognizerDateResultTypeUndefined
};

/**
 * Class contains date information retrieved by medical certificates recognizer.
 */
@interface SBSDKMedicalCertificateRecognizerDateResult : NSObject

/** The string representation of the recognized and validated date. */
@property (nonatomic, strong) NSString *dateString;

/** The type of the date record. */
@property (nonatomic) SBSDKMedicalCertificateRecognizerDateResultType dateRecordType;

/** The confidence value of the character recognition. */
@property (nonatomic) double recognitionConfidence;

/** The confidence value of the date validation. */
@property (nonatomic) double validationConfidence;

@end
