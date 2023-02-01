#import <UIKit/UIKit.h>
#import "SBSDKGenericDocumentCommonFieldType.h"

/** The generic document fields display status. Whether a field is shown or hidden in the user interface. */
typedef NSString* SBSDKGenericDocumentFieldDisplayState;

/** The field will not be shown in the user interface. */
extern NSString* _Nonnull const SBSDKGenericDocumentFieldDisplayStateHidden;

/** Field will be shown in the user interface if its text value isn't an empty string */
extern NSString* _Nonnull const SBSDKGenericDocumentFieldDisplayStateVisibleIfNotEmpty;

/** The field will be shown in the user interface. */
extern NSString* _Nonnull const SBSDKGenericDocumentFieldDisplayStateAlwaysVisible;

/** The fields validation status. Applicable only to fields that support some kind of validation, e.g. using check digits. */
typedef NS_ENUM(NSUInteger, SBSDKGenericDocumentFieldValidationStatus) {
    /** Field value failed validation */
    SBSDKGenericDocumentFieldValidationStatusInvalid,
    /** Field value passed validation */
    SBSDKGenericDocumentFieldValidationStatusValid,

    /** Field does not support validation  */
    SBSDKGenericDocumentFieldValidationStatusUndefined = (NSUInteger) -1,
};

/** A generic documents fields result of OCR text recognition. */
@interface SBSDKGenericDocumentOcrResult : NSObject

/** The recognized text of the field. */
@property(nonatomic, strong, nonnull) NSString *text;

/** Confidence in result accuracy. The value ranges from 0.0 to 1.0, higher is better. */
@property(nonatomic) float confidence;

@end

/** A generic documents field type. */
@interface SBSDKGenericDocumentFieldType : NSObject

/** Local field type name scoped to the containing document type */
@property(nonatomic, strong, nonnull) NSString *name;

/** Unique global field type name prefixed with the document types of all containing documents */
@property(nonatomic, strong, nonnull) NSString *fullName;

/** Normalized global field type name. Fields in document types derived from the same base document type in the schema will have the same normalized name. */
@property(nonatomic, strong, nonnull) NSString *normalizedName;

/** Optional common field type. Commonly occurring fields that have the same semantic meaning in different document types will often have a set common type. */
@property(nonatomic) SBSDKGenericDocumentCommonFieldType commonType;

/**
 * The friendly, human readable display name of this field in English. Can be customized using the function `setUserFieldTypeDisplayTexts`.
 * This computed property first looks up the display text for the receiver in the `userFieldTypeDisplayTexts` dictionary.
 * If there is no value stored, or the user dictionary is nil, it automatically falls back to the `defaultFieldTypeDisplayTexts` dictionary.
 */
@property(nullable, nonatomic, readonly) NSString *displayText;

/**
 * A dictionary of the default display strings for generic document field types.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the default display texts for the corresponding fields.
 */
+ (nonnull NSDictionary<NSString *, NSString *>*)defaultFieldTypeDisplayTexts;

/**
 * A dictionary of user defined display strings for generic document field types. Defaults to nil.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the user defined display texts for the corresponding fields.
 */
+ (nullable NSDictionary <NSString *, NSString *>*)userFieldTypeDisplayTexts;

/**
 * Sets a dictionary of user defined display strings. Used to specify user defined text for displaying documents field types in the
 * user interface.
 */
+ (void)setUserFieldTypeDisplayTexts:(nullable NSDictionary <NSString *, NSString *>*)userFieldTypeDisplayTexts;

/**
 * A dictionary of the default visibility states for generic document field types.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the state of visibility for the corresponding fields.
 */
+ (nonnull NSDictionary<NSString *, SBSDKGenericDocumentFieldDisplayState>*)defaultFieldTypeVisibilities;

/**
 * A dictionary of user defined visibility states for generic document field types. Defaults to nil.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the state of visibility for the corresponding fields.
 */
+ (nullable NSDictionary <NSString *, SBSDKGenericDocumentFieldDisplayState>*)userFieldTypeVisibilities;

/**
 * Sets a dictionary of user defined visibility states. Used to specify user defined visibility of documents field types in the
 * user interface.
 */
+ (void)setUserFieldTypeVisibilities:(nullable NSDictionary<NSString *, SBSDKGenericDocumentFieldDisplayState>*)userFieldTypeVisibilities;

@end


/** A generic documents field. */
@interface SBSDKGenericDocumentField : NSObject

/** The type of the field. */
@property(nonatomic, strong, nonnull) SBSDKGenericDocumentFieldType *type;

/** Optional value of the field. Applicable only to text fields. */
@property(nonatomic, strong, nullable) SBSDKGenericDocumentOcrResult *value;

/** Image crop of the field.  */
@property(nonatomic, strong, nullable) UIImage *image;

/** Field validation status. Applicable only to fields that support some kind of validation. */
@property SBSDKGenericDocumentFieldValidationStatus validationStatus;

@end



/** A generic documents type. */
@interface SBSDKGenericDocumentType : NSObject

/** Local document type name. */
@property(nonatomic, strong, nonnull) NSString *name;

/** Unique global document type name prefixed with the document types of all containing documents. */
@property(nonatomic, strong, nonnull) NSString *fullName;

/** Normalized global document type name. Common document types appearing as child documents in different places will often have the same normalized type name. */
@property(nonatomic, strong, nonnull) NSString *normalizedName;

/**
 * The friendly, human readable display name of this document type in English. Can be customized using the function `setUserDocumentTypeDisplayTexts`.
 * This computed property first looks up the display text for the receiver in the `userDocumentTypeDisplayTexts` dictionary.
 * If there is no value stored, or the user dictionary is nil, it automatically falls back to the `defaultDocumentTypeDisplayTexts` dictionary.
 */
- (nullable NSString *)displayText;

/**
 * A dictionary of the default display strings for generic document types.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the default display texts for the corresponding document types.
 */
+ (nonnull NSDictionary<NSString *, NSString *>*)defaultDocumentTypeDisplayTexts;

/**
 * A dictionary of user defined display strings for generic document types. Defaults to nil.
 * Each key is equal to a document types `normalizedName` property.
 * The values contain the user defined display texts for the corresponding document types.
 */
+ (nullable NSDictionary <NSString *, NSString *> *)userDocumentTypeDisplayTexts;

/**
 * Sets a dictionary of user defined display strings. Used to specify user defined text for displaying a document type in the
 * user interface.
 */
+ (void)setUserDocumentTypeDisplayTexts:(nullable NSDictionary <NSString *, NSString *>*)userDocumentTypeTexts;

@end


/** A generic document. Contains fields and sub-documents. */
@interface SBSDKGenericDocument : NSObject

/** The documents type. */
@property(nonatomic, strong, nonnull) SBSDKGenericDocumentType *type;

/** A list of the documents fields. */
@property(nonatomic, strong, nonnull) NSArray<SBSDKGenericDocumentField *> *fields;

/** A list of the documents sub-documents. */
@property(nonatomic, strong, nonnull) NSArray<SBSDKGenericDocument *> *children;

/** The average confidence in the accuracy of the document recognition result. */
@property float confidence;

/** The weight of the confidence. Can be used to calculate the weighted average confidence of two or more documents. */
@property float confidenceWeight;

/** Returns a field given its local or common type name. Returns nil if not found. */
- (nullable SBSDKGenericDocumentField *)fieldByTypeName:(nonnull NSString *)name;

/** Returns all fields given a local or common field type name. */
- (nonnull NSArray<SBSDKGenericDocumentField *> *)fieldsByTypeName:(nonnull NSString *)name;

/** Returns a sub-document given its document type name. Returns nil if not found. */
- (nullable SBSDKGenericDocument *)childByDocumentType:(nonnull NSString *)name;

@end
