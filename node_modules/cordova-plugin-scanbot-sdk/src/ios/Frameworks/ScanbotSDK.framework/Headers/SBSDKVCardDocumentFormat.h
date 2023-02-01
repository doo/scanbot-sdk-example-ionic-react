//
//  SBSDKVCardDocumentFormat.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 02.07.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBarCodeScannerDocumentFormat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * vCard document field type.
 */
typedef NS_ENUM(NSInteger, SBSDKVCardDocumentFieldType) {
    /** Version. */
    SBSDKVCardDocumentFieldTypeVersion,
    /** Source. */
    SBSDKVCardDocumentFieldTypeSource,
    /** Kind. */
    SBSDKVCardDocumentFieldTypeKind,
    /** XML. */
    SBSDKVCardDocumentFieldTypeXML,
    /** Name. */
    SBSDKVCardDocumentFieldTypeName,
    /** First name. */
    SBSDKVCardDocumentFieldTypeFirstName,
    /** Nickname. */
    SBSDKVCardDocumentFieldTypeNickname,
    /** Birthday. */
    SBSDKVCardDocumentFieldTypeBirthday,
    /** Anniversary. */
    SBSDKVCardDocumentFieldTypeAnniversary,
    /** Gender. */
    SBSDKVCardDocumentFieldTypeGender,
    /** Delivery address. */
    SBSDKVCardDocumentFieldTypeDeliveryAddress,
    /** Photo. */
    SBSDKVCardDocumentFieldTypePhoto,
    /** Telephone number. */
    SBSDKVCardDocumentFieldTypeTelephoneNumber,
    /** Email. */
    SBSDKVCardDocumentFieldTypeEmail,
    /** IMPP. */
    SBSDKVCardDocumentFieldTypeIMPP,
    /** Languages. */
    SBSDKVCardDocumentFieldTypeLanguages,
    /** Time zone. */
    SBSDKVCardDocumentFieldTypeTimeZone,
    /** Geolocation. */
    SBSDKVCardDocumentFieldTypeGeoLocation,
    /** Title. */
    SBSDKVCardDocumentFieldTypeTitle,
    /** Role. */
    SBSDKVCardDocumentFieldTypeRole,
    /** Logo. */
    SBSDKVCardDocumentFieldTypeLogo,
    /** Organisation. */
    SBSDKVCardDocumentFieldTypeOrganisation,
    /** Member. */
    SBSDKVCardDocumentFieldTypeMember,
    /** Related. */
    SBSDKVCardDocumentFieldTypeRelated,
    /** Categories. */
    SBSDKVCardDocumentFieldTypeCategories,
    /** Note. */
    SBSDKVCardDocumentFieldTypeNote,
    /** Product ID. */
    SBSDKVCardDocumentFieldTypeProductId,
    /** Revision. */
    SBSDKVCardDocumentFieldTypeRevision,
    /** Sound. */
    SBSDKVCardDocumentFieldTypeSound,
    /** UID. */
    SBSDKVCardDocumentFieldTypeUID,
    /** Client PID map. */
    SBSDKVCardDocumentFieldTypeClientPIDMap,
    /** URL. */
    SBSDKVCardDocumentFieldTypeURL,
    /** Public key. */
    SBSDKVCardDocumentFieldTypePublicKey,
    /** Busy time URL. */
    SBSDKVCardDocumentFieldTypeBusyTimeURL,
    /** Calendar URI for requests. */
    SBSDKVCardDocumentFieldTypeCalendarURIForRequests,
    /** Calendar URI. */
    SBSDKVCardDocumentFieldTypeCalendarURI,
    /** Custom. */
    SBSDKVCardDocumentFieldTypeCustom
};

/**
 * vCard document field description.
 */
@interface SBSDKVCardDocumentField : NSObject

/** Raw field value. */
@property (nonatomic, strong) NSString *rawText;

/** Field type. */
@property (nonatomic) SBSDKVCardDocumentFieldType type;

/** Field type modifiers. */
@property (nonatomic, strong) NSArray<NSString *> *typeModifiers;

/** Field values. */
@property (nonatomic, strong) NSArray<NSString *> *values;

/** Human-readable field type name. */
@property (nonatomic, strong, readonly) NSString *typeHumanReadableString;

@end

/**
 * vCard document description.
 */
@interface SBSDKVCardDocumentFormat : SBSDKBarCodeScannerDocumentFormat

/** Document fields. */
@property (nonatomic, strong) NSArray<SBSDKVCardDocumentField *> *fields;

@end

NS_ASSUME_NONNULL_END
