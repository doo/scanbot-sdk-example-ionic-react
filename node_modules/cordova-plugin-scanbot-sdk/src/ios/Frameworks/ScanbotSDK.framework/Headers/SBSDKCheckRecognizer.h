//
//  SBSDKCheckRecognizer.h
//  ScanbotSDK
//
//  Created by Dmitry Zaytsev on 12/04/16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import "SBSDKCheckRecognizerResult.h"

/**
 * A realtime detector and recognizer for U.S. Checks. It detects checks on CMSampleBufferRef object
 * from an AVFoundation video stream. After successful detection it runs a recognition
 * operation to extract the data fields of the detected check.
 */
@interface SBSDKCheckRecognizer : NSObject

/** An array of accepted check types. By default all check types are allowed. */
@property(nonnull, nonatomic, copy) NSArray<SBSDKCheckDocumentRootType *>* acceptedCheckTypes;

/**
 * Detects and recognizes a check in the given image.
 * This function is intended to be used with live detection.
 * Video stream from device returns a rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This function handles these orientation differences, so you shouldn't fix or rotate the input image.
 * Keep in mind, that the buffer received from the video stream is handled by the system. So in some cases it might be cleaned or changed by the system
 * before recognition occurs. You may convert the buffer to UIImage upon receiving it and use `recognizeOnImage:orientation:` function, if that is an issue.
 * @param sampleBufferRef The video frame or still image as CMSampleBufferRef object to detect a check on.
 * @param videoOrientation The orientation of the video frame. Should be the orientation that the device currently has, not actual image orientation.
 * @return A SBSDKCheckRecognizerResult object containing the field data or nil if detection or recognition failed.
 */
- (nullable SBSDKCheckRecognizerResult *)recognizeOnBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                               orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Detects and recognizes a check in the given image.
 * This function is intended to be used with live detection.
 * Video stream from device returns a rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This function handles these orientation differences, so you shouldn't fix or rotate the input image.
 * @param image Input image.
 * @param videoOrientation The orientation of the video frame. Should be the orientation that the device currently has, not actual image orientation.
 * @return A SBSDKCheckRecognizerResult object containing the field data or nil if detection or recognition failed.
 */
- (nullable SBSDKCheckRecognizerResult *)recognizeOnImage:(nonnull UIImage *)image
                                              orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Recognizes a check in the given image.
 * This function is intended to use for detection on static images.
 * @param image Input image.
 * @return A SBSDKCheckRecognizerResult object containing the field data or nil if detection or recognition failed.
 */
- (nullable SBSDKCheckRecognizerResult *)recognizeOnImage:(nonnull UIImage *)image;

@end
