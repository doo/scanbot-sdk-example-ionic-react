//
//  SBSDKNFCDatagroupDG1.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 07.05.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import "SBSDKNFCDatagroup.h"

/**
 * Data group 1 or DG1.
 * Contains general information about the passport and its holder.
 */
@interface SBSDKNFCDatagroupDG1 : SBSDKNFCDatagroup

/** The type of the document. */
@property(nonatomic, readonly) NSString* documentType;

/** The state or organisation that issued the passport. */
@property(nonatomic, readonly) NSString* issuingStateOrOrganization;

/** The unique number of the passport. */
@property(nonatomic, readonly) NSString* documentNumber;

/** The checksum digit of the passports document number. */
@property(nonatomic, readonly) NSInteger documentNumberCheckDigit;

/** Optional data. */
@property(nonatomic, readonly) NSString* optionalData;

/** Optional data 2. */
@property(nonatomic, readonly) NSString* optionalData2;

/** Optional data checksum. */
@property(nonatomic, readonly) NSInteger optionalDataCheckDigitTD3;

/** The date of birth of the passports holder. */
@property(nonatomic, readonly) NSDate* dateOfBirth;

/** The checksum digit of the date of birth. */
@property(nonatomic, readonly) NSInteger dateOfBirthCheckDigit;

/** The date of expiry of the passport. */
@property(nonatomic, readonly) NSDate* dateOfExpiry;

/** The checksum digit of the passports date of expiry. */
@property(nonatomic, readonly) NSInteger dateOfExpiryCheckDigit;

/** The sex of the passport holder. */
@property(nonatomic, readonly) NSString* sex;

/** The nationality of the passports holder. */
@property(nonatomic, readonly) NSString* nationality;

/** The composite checksum digit. */
@property(nonatomic, readonly) NSInteger compositeCheckDigit;

/** The name of the passport holder. */
@property(nonatomic, readonly) NSString* nameOfDocumentHolder;

@end
