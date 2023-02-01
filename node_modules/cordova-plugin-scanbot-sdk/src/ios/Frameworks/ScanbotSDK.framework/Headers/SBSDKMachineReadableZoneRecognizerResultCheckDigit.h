//
//  SBSDKMachineReadableZoneRecognizerResultCheckDigit.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 14.10.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#ifndef SBSDKMachineReadableZoneRecognizerResultCheckDigit_h
#define SBSDKMachineReadableZoneRecognizerResultCheckDigit_h

#import <Foundation/Foundation.h>

/**
 MRZ checkdigit types.
 */
typedef NS_ENUM(NSUInteger, SBSDKMachineReadableZoneRecognizerResultCheckDigitType) {
    
    /** Undefined. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypeUndefined = 0,
    
    /** Document number validation checkdigit. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypeDocumentNumber = 1,

    /** Date of birth validation checkdigit. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypeDateOfBirth = 2,
    
    /** Document expiration date validation checkdigit. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypeExpirationDate = 3,
    
    /** Personal number validation checkdigit. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypePersonalNumber = 4,
    
    /** General document validation checkdigit. **/
    SBSDKMachineReadableZoneRecognizerResultCheckDigitTypeGeneral = 5
};

/**
 Contains information about a single checkdigit.
 */
@interface SBSDKMachineReadableZoneRecognizerResultCheckDigit : NSObject

/** Raw checkdigit character. */
@property (nonatomic) char checkDigitCharacter;

/** Checkdigit validation result. */
@property (nonatomic) BOOL successfullyValidated;

/** Checkdigit type. */
@property (nonatomic) SBSDKMachineReadableZoneRecognizerResultCheckDigitType type;

/** Text string for this checkdigit validation. */
@property (nonatomic) NSString *validatedString;

@end

#endif /* SBSDKMachineReadableZoneRecognizerResultCheckDigit_h */
