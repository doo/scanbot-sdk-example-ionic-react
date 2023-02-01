//
//  SBSDKUITextDataScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 11.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUITextDataScannerStep.h"

/**
 * Configuration for the behavior of text line recognizer.
 */
@interface SBSDKUITextDataScannerBehaviorConfiguration : NSObject

/** The data scanner recognition step. */
@property (nonatomic, strong) SBSDKUITextDataScannerStep *recognitionStep;

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** Whether the word boxes should be shown. */
@property (nonatomic, assign) BOOL wordBoxHighlightEnabled;

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
 * A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 */
@property(nonatomic, copy) NSString *supportedLanguages;

@end

