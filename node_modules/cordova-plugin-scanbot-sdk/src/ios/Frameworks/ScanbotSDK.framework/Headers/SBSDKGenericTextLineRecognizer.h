//
//  SBSDKGenericTextLineRecognizer.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 30.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

#import "SBSDKGenericTextLineRecognizerResult.h"
#import "SBSDKGenericTextLineRecognizerConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class to recognize one line of text in a small area and run validation on the result.
 * It is intended to be a very generic text-based live video recognizer for tasks that can't be accomplished with
 * the specialized recognizers in ScanbotSDK.
 */
@interface SBSDKGenericTextLineRecognizer : NSObject

/** Unavailable. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes an instance with the given configuration.
 * Returns nil, if the required OCR resources are not installed.
 * @param configuration The configuration object to be used to configure the new instance.
 */
- (nullable instancetype)initWithConfiguration:(SBSDKGenericTextLineRecognizerConfiguration *)configuration;

/**
 * Recognizes text information from given sample buffer. Intended for usage with live detection.
 * @param sampleBufferRef The sample buffer reference.
 * @param videoOrientation Video frame orientation. Should be the orientation that the device currently has, not actual image orientation.
 * @param rect Rectangle in image coordinates in which to perform the search. Must be inside the image.
 * @return The result of the recognition.
 */
- (nullable SBSDKGenericTextLineRecognizerResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                 orientation:(AVCaptureVideoOrientation)videoOrientation
                                                                      inRect:(CGRect)rect;

/**
 * Clears the frame accumulator of the recognizer.
 * This should be called after retrieving a result and initiating a new recognition.
 */
- (void)clearFrameAccumulator;

@end

NS_ASSUME_NONNULL_END
