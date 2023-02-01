//
//  SBSDKTIFFImageWriterUserDefinedField.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 11/25/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Custom TIFF field type. */
typedef NS_ENUM(int, SBSDKTIFFImageWriterUserDefinedFieldType) {
    /** A numeric field type. */
    SBSDKTIFFImageWriterUserDefinedFieldTypeNumeric,
    /** A string based field type. */
    SBSDKTIFFImageWriterUserDefinedFieldTypeString
};

/**
 * Class used to describe user-defined TIFF field.
 */
@interface SBSDKTIFFImageWriterUserDefinedField : NSObject

/** Field name. */
@property (nonatomic, strong, nonnull) NSString *fieldName;

/**
 * Field numeric tag. Please refer to TIFF documentation regarding reserved tag numbers
 * and their field types.
 */
@property (nonatomic) NSInteger fieldTag;

/**
 * Generate new field with given parameters.
 * @param value Field numeric value.
 * @param name Field name.
 * @param tag Field tag.
 * @return Generated field.
 */
+ (nonnull instancetype)fieldWithNumericValue:(nonnull NSNumber *)value
                            fieldName:(nonnull NSString *)name
                             fieldTag:(NSInteger)tag;

/**
 * Generate new field with given parameters.
 * @param value Field string value.
 * @param name Field name.
 * @param tag Field tag.
 * @return Generated field.
 */
+ (nonnull instancetype)fieldWithStringValue:(nonnull NSString *)value
                           fieldName:(nonnull NSString *)name
                            fieldTag:(NSInteger)tag;

/**
 * Field type getter.
 * @return Field type.
 */
- (SBSDKTIFFImageWriterUserDefinedFieldType)fieldType;

/**
 * Numeric value getter. Returns numeric value of the field, if field type is
 * SBSDKTIFFImageWriterUserDefinedFieldTypeNumeric. Returns nil otherwise.
 * @return Numeric value or nil.
 */
- (nullable NSNumber *)numericValue;

/**
 * String value getter. Returns string value of the field, if field type is
 * SBSDKTIFFImageWriterUserDefinedFieldTypeString. Returns nil otherwise.
 * @return Numeric value or nil.
 */
- (nullable NSString *)stringValue;

@end
