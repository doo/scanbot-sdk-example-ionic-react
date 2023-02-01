//
//  SBSDKUITextDataScannerStep.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 16.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKGenericTextLineRecognizerConfiguration.h"
#import "SBSDKAspectRatio.h"

/**
 * Defines a single workflow step of 'SBSDKUITextDataScannerViewController' flow.
 */
@interface SBSDKUITextDataScannerStep : NSObject

/**
 * The tag of the workflow step. Useful managing multiple workflow steps.
 * By default it is a UUID string.
 */
@property (nonnull, nonatomic, strong) NSString *stepTag;

/**
 * The title of the step.
 * By default it is an empty.
 */
@property (nonnull, nonatomic, strong) NSString *title;

/**
 * A user guidance hint for this workflow step.
 * The guidance hint is displayed while the workflow step is active.
 */
@property (nonnull, nonatomic, strong) NSString *guidanceText;

/**
 * Sets a validation pattern to validate to automatically validate recognized text.
 * '?' = any character
 * '#' - any digit
 *  All other characters represent themselves.
 *
 *  An empty string or nil value will disable the validation pattern.
 */
@property (nullable, nonatomic, strong) NSString *pattern;

/**
 * If set to YES pattern validation also validates successfully if only a part of the whole recognized text matches
 * the the validation pattern.
 * If set to NO, the whole text must match the validation pattern.
 * Applies to pattern validation only. Defaults to NO.
 */
@property (nonatomic) BOOL shouldMatchSubstring;

/**
 * Callback block for recognized text validation. If pattern validation is not powerful enough, you can
 * specify your own validation block here. Defaults to nil.
 */
@property(nullable, nonatomic, copy) SBSDKTextLineRecognizerValidationBlock validationBlock;

/**
 * Callback to clean a recognized text prior to validation. Filter out unwanted phrases and textual noise here.
 * Default is nil.
 */
@property(nullable, nonatomic, copy) SBSDKTextLineRecognizerTextSanitizerBlock stringSanitizerBlock;

/**
 * The cameras zoom level preferred for this step. The actual zoom might be different from the preferred one
 * to avoid clipping of finder area and maintain its aspect ratio and height;
 */
@property (nonatomic) CGFloat preferredZoom;

/**
 * The aspect ratio for the workflow steps region of interest and, equally, for the finder view.
 * Defaults to 5:1.
 */
@property (nonnull, nonatomic, strong) SBSDKAspectRatio *aspectRatio;

/**
 * The preferred height of the finder for zoom scale 1.0 (unzoomed).
 * The actual finder height might change to maintain aspect ratio and to not clip the screen.
 * Defaults to 40 points.
 */
@property (nonatomic) CGFloat unzoomedFinderHeight;

/**
 * A string (list) of accepted characters during text recognition. If empty or nil, all characters are accepted.
 * Defaults to nil.
 */
@property (nullable, nonatomic, strong) NSString *allowedSymbols;

/**
 * The text filter strategy for the text line recognizer step. Defaults to SBSDKTextFilterStrategyDocument.
 */
@property (nonatomic, assign) SBSDKTextFilterStrategy textFilterStrategy;


@end
