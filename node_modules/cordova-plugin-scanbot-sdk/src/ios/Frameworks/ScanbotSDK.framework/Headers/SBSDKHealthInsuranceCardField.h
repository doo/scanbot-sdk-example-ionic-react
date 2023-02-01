#import <Foundation/Foundation.h>

/**
 * EHIC field type.
 */
typedef NS_ENUM(NSUInteger, SBSDKHealthInsuranceCardFieldType) {
    /**
     * Field 3: surname
     */
    SBSDKHealthInsuranceCardFieldTypeSurname,

    /**
     * Field 4: given names
     */
    SBSDKHealthInsuranceCardFieldTypeGivenName,

    /**
     * Field 5: date of birth
     */
    SBSDKHealthInsuranceCardFieldTypeDateOfBirth,

    /**
     * Field 6: personal identification number
     */
    SBSDKHealthInsuranceCardFieldTypePersonalIdentificationNumber,

    /**
     * Field 7 (part before dash): institution number
     */
    SBSDKHealthInsuranceCardFieldTypeInstitutionNumber,

    /**
     * Field 7 (part after dash): institution name or abbreviation
     */
    SBSDKHealthInsuranceCardFieldTypeInstitutionName,

    /**
     * Field 8: card number
     */
    SBSDKHealthInsuranceCardFieldTypeCardNumber,

    /**
     * Field 9: card expiration date
     */
    SBSDKHealthInsuranceCardFieldTypeCardExpirationDate,

    /**
     * Field 10: card country
     */
    SBSDKHealthInsuranceCardFieldTypeCardCountry
};

/**
 * EHIC field data.
 */
@interface SBSDKHealthInsuranceCardField : NSObject

/**
 Field type.
 */
@property (nonatomic) SBSDKHealthInsuranceCardFieldType type;

/**
 Field string value.
 */
@property (nonatomic, strong) NSString* value;

/**
 OCR recognition confidence. Relevant only for fields whose values cannot be validated (like e.g. the person's name).
 */
@property (nonatomic) double confidence;

/**
 String representation of the field in the form of "Field name: Field value".
 */
- (NSString *)stringRepresentation;

@end
