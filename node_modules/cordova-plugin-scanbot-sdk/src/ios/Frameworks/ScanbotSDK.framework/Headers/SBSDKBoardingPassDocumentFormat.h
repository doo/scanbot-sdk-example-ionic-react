//
//  SBSDKBoardingPassDocumentFormat.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 20.05.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Boarding pass field types,
 */
typedef NS_ENUM(NSInteger, SBSDKBoardingPassDocumentFieldType) {
    /** Operating carrier PNR code. */
    SBSDKBoardingPassDocumentFieldTypeOperatingCarrierPNRCode,
    /** Departure airport code. */
    SBSDKBoardingPassDocumentFieldTypeDepartureAirportCode,
    /** Destination airport code. */
    SBSDKBoardingPassDocumentFieldTypeDestinationAirportCode,
    /** Operating carrier designator. */
    SBSDKBoardingPassDocumentFieldTypeOperatingCarrierDesignator,
    /** Flight number. */
    SBSDKBoardingPassDocumentFieldTypeFlightNumber,
    /** Date of flight in Julian format. */
    SBSDKBoardingPassDocumentFieldTypeDateOfFlightJulian,
    /** Compartment code. */
    SBSDKBoardingPassDocumentFieldTypeCompartmentCode,
    /** Seat number. */
    SBSDKBoardingPassDocumentFieldTypeSeatNumber,
    /** Check-in sequence number. */
    SBSDKBoardingPassDocumentFieldTypeCheckInSequenceNumber,
    /** Passenger status. */
    SBSDKBoardingPassDocumentFieldTypePassengerStatus,
    /** Version number. */
    SBSDKBoardingPassDocumentFieldTypeVersionNumber,
    /** Passenger description. */
    SBSDKBoardingPassDocumentFieldTypePassengerDescription,
    /** Source of check-in. */
    SBSDKBoardingPassDocumentFieldTypeSourceOfCheckIn,
    /** Source of boarding pass issuance. */
    SBSDKBoardingPassDocumentFieldTypeSourceOfBoardingPassIssuance,
    /** Date of boarding pass issuance in Julian format. */
    SBSDKBoardingPassDocumentFieldTypeDateOfBoardingPassIssuanceJulian,
    /** Document type. */
    SBSDKBoardingPassDocumentFieldTypeDocumentType,
    /** Airline designator of boarding pass issuer. */
    SBSDKBoardingPassDocumentFieldTypeAirlineDesignatorOfBoardingPassIssuer,
    /** Baggage tag license plate numbers. */
    SBSDKBoardingPassDocumentFieldTypeBaggageTagLicensePlateNumbers,
    /** First non-consecutive baggage tag license plate number. */
    SBSDKBoardingPassDocumentFieldTypeFirstNonConsecutiveBaggageTagLicensePlateNumber,
    /** Second non-consecutive baggage tag license plate number. */
    SBSDKBoardingPassDocumentFieldTypeSecondNonConsecutiveBaggageTagLicensePlateNumber,
    /** Airline numeric code. */
    SBSDKBoardingPassDocumentFieldTypeAirlineNumericCode,
    /** Document form serial number. */
    SBSDKBoardingPassDocumentFieldTypeDocumentFormSerialNumber,
    /** Selectee indicator. */
    SBSDKBoardingPassDocumentFieldTypeSelecteeIndicator,
    /** International document verification. */
    SBSDKBoardingPassDocumentFieldTypeInternationalDocumentationVerification,
    /** Marketing carrier designator. */
    SBSDKBoardingPassDocumentFieldTypeMarketingCarrierDesignator,
    /** Frequent flyer airline designator. */
    SBSDKBoardingPassDocumentFieldTypeFrequentFlyerAirlineDesignator,
    /** Frequent flyer number. */
    SBSDKBoardingPassDocumentFieldTypeFrequentFlyerNumber,
    /** IDAD indicator. */
    SBSDKBoardingPassDocumentFieldTypeIDADIndicator,
    /** Free baggage allowance. */
    SBSDKBoardingPassDocumentFieldTypeFreeBaggageAllowance,
    /** Fast track. */
    SBSDKBoardingPassDocumentFieldTypeFastTrack,
    /** For individual airline use. */
    SBSDKBoardingPassDocumentFieldTypeForIndividualAirlineUse
};

/**
 * Boarding pass leg field description.
 */
@interface SBSDKBoardingPassLegField : NSObject
    
/** Field type. */
@property (nonatomic) SBSDKBoardingPassDocumentFieldType type;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;
    
/** Field value. */
@property (nonatomic, strong) NSString *value;

@end

/**
 * Boarding pass leg information.
 */
@interface SBSDKBoardingPassLeg : NSObject
    
/** Fields. */
@property (nonatomic, strong) NSArray<SBSDKBoardingPassLegField *> *fields;

@end

/**
 * Boarding pass document description.
 */
@interface SBSDKBoardingPassDocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Number of legs in document. */
@property (nonatomic) NSInteger numberOfLegs;

/** Passenger name. */
@property (nonatomic, strong) NSString *name;

/** Value indicates that this ticket is an electronic ticket. */
@property (nonatomic) BOOL electronicTicket;

/** Security data string. */
@property (nonatomic, strong) NSString *securityData;

/** Legs information. */
@property (nonatomic, strong) NSArray<SBSDKBoardingPassLeg *> *legs;

@end

NS_ASSUME_NONNULL_END
