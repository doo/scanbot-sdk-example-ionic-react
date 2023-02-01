//
//  SBSDKGenericTextLineRecognizerConfiguration.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 30.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGBase.h>
#import "SBSDKAspectRatio.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Strategies for the generic text line recognizer.
 */
typedef NS_ENUM(NSInteger, SBSDKTextFilterStrategy) {
    /** Filters the recognized text for typical documents. */
    SBSDKTextFilterStrategyDocument,
    
    /** Filters the recognized text for license plates. Algorithmic solution.*/
    SBSDKTextFilterStrategyLicensePlateClassic __attribute__((deprecated("Please use SBSDKLicensePlateScanner."))),
    
    /** Filters the recognized text for license plates. Machine Learning solution*/
    SBSDKTextFilterStrategyLicensePlateML __attribute__((deprecated("Please use SBSDKLicensePlateScanner."))),
    
    /** Filters the recognized text for dot matrix displays. */
    SBSDKTextFilterStrategyLCDotMatrixDisplay
};

/** Block type to validate a recognition result. */
typedef BOOL (^SBSDKTextLineRecognizerValidationBlock)(NSString *);

/** Block type to sanitize the raw recognized text of a recognition result. */
typedef NSString* _Nullable (^SBSDKTextLineRecognizerTextSanitizerBlock)(NSString *);

/**
 * A descriptor-like class to configure an instance of SBSDKGenericTextLineRecognizer.
 */
@interface SBSDKGenericTextLineRecognizerConfiguration : NSObject

/**
 * The text filter strategy for the generic text line recognizer. Defaults to SBSDKTextFilterStrategyDocument.
 */
@property(nonatomic, assign) SBSDKTextFilterStrategy textFilterStrategy;

/**
 * A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 */
@property(nonatomic, copy) NSString *textRecognitionLanguages;

/**
 * A string (list) of accepted characters during text recognition. If empty or nil, all characters are accepted.
 */
@property(nullable, nonatomic, copy) NSString *textRecognitionAllowedCharacters;

/**
 * The maximum number of accumulated video frames before the current recognition result is returned.
 */
@property(nonatomic, assign) NSUInteger maximumNumberOfAccumulatedFrames;

/**
 * Maximum image side length (height or width) for OCR processing. If the initial image has longer side - it will be downscaled to the limit.
 * Setting to `0` means no limit. Default is 0.
 * Using this parameter might be useful for slower devices or to reduce processing load.
 */
@property(nonatomic, assign) NSUInteger ocrResolutionLimit;

/**
 * The minimum equal results in accumulated video frames to count as valid.
 */
@property(nonatomic, assign) NSUInteger minimumNumberOfRequiredFramesWithEqualRecognitionResult;

/**
 * A very basic and simple string pattern used to validate the recognized text.
 * ? - any character
 * # - any digit
 * All other characters represent themselves.
 * Note: If validationPattern and validationBlock are both non-nil, both validation methods are AND-connected to
 * form the final validation result.
 */
@property(nullable, nonatomic, copy) NSString *validationPattern;

/**
 * If set to NO, the whole recognized text must match the pattern in order to validate, otherwise the validation
 * will be successful if the recognized text contains a substring that matches the validation pattern.
 * Defaults to NO.
 */
@property(nonatomic, assign) BOOL validationPatternSubstringMatchingEnabled;

/**
 * A callback block used to validate the recognized text.
 * The recognized string is passed to the block as parameter and the block must return YES, if the result is valid and
 * NO otherwise.
 * Note: If validationPattern and validationBlock are both non-nil, both validation methods are AND-connected to
 * form the final validation result.
*/
@property(nullable, nonatomic, copy) SBSDKTextLineRecognizerValidationBlock validationBlock;

/**
 * A callback block used to sanitize the raw recognized text.
 * This block is called before validation and should be used to filter the raw text from unwanted characters and noise.
 * The returned sanitized string is then fed back into the recognizer to improve the quality and speed
 * of the recognition in the following video frames.
 */
@property(nullable, nonatomic, copy) SBSDKTextLineRecognizerTextSanitizerBlock stringSanitizerBlock;

/**
 * The default configuration initializer
 */
+ (instancetype)defaultConfiguration;

@end


NS_ASSUME_NONNULL_END
