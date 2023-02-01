#import <UIKit/UIKit.h>

#import "SBSDKHealthInsuranceCardField.h"

/**
 * EHIC detection status.
 */
typedef NS_ENUM(NSUInteger, SBSDKHealthInsuranceCardDetectionStatus) {
    /**
     * Detection successful. The fields array is filled with all of the extracted data. All validatable fields have passed validation.
     */
    SBSDKHealthInsuranceCardDetectionStatusSuccess,
    
    /**
     * No document found or the document doesn't look like the back of an EHIC.
     */
    SBSDKHealthInsuranceCardDetectionStatusFailedDetection,
    
    /**
     * A potential EHIC was found but one or more fields failed validation.
     */
    SBSDKHealthInsuranceCardDetectionStatusIncompleteValidation
};

/**
 The result of EHIC recognition returned by SBSDKHealthInsuranceCardRecognizer
 */
@interface SBSDKHealthInsuranceCardRecognitionResult : NSObject

/**
 * An array of extracted card fields.
 */
@property (nonatomic, strong, nonnull) NSArray<SBSDKHealthInsuranceCardField*>* fields;

/**
 * Detection status.
 */
@property (nonatomic) SBSDKHealthInsuranceCardDetectionStatus status;

/**
 * String representation of the fields array.
 */
- (nonnull NSString *) stringRepresentation;

@end
