//
//  SBSDKMultipleObjectsDetector.h
//  ScanbotSDKBeta
//
//  Created by Stefan Dragnev on 09.08.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SBSDKPolygon.h"
#import "SBSDKAspectRatioRange.h"


/**
 * A class to detect multiple non-overlapping rectangular objects in a UIImage or CMSampleBufferRef. Like a bunch of business cards.
 */
@interface SBSDKMultipleObjectsDetector : NSObject

/**
 * Detects multiple non-overlapping rectangular objects within an image. Like a bunch of business cards.
 * @param image The image on which multiple rectangular objects should be detected.
 * @return An array of detected SBSDKPolygon objects.
 */
- (nullable NSArray<SBSDKPolygon*>*) detectOnImage:(nonnull UIImage*)image;

/**
 * Detects multiple non-overlapping rectangular objects within a samplebuffer. Like a bunch of business cards.
 * @param sampleBufferRef The sample buffer on which multiple rectangular objects should be detected.
 * @param videoOrientation The video orientation for the given sample buffer.
 * @return An array of detected SBSDKPolygon objects.
 */
- (nullable NSArray<SBSDKPolygon*>*) detectInSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                              orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Detects multiple non-overlapping rectangular objects within a pixel buffer. Like a bunch of business cards.
 * @param pixelBufferRef The pixel buffer on which multiple rectangular objects should be detected.
 * @param videoOrientation The video orientation for the given sample buffer.
 * @return An array of detected SBSDKPolygon objects.
 */
- (nullable NSArray<SBSDKPolygon*>*) detectInPixelBuffer:(nonnull CVPixelBufferRef)pixelBufferRef
                                             orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Defines aspect ratio range. Only objects that are within this range will be detected. The default range is `1:2 - 2:1`.;
 */
@property (nonatomic, strong, nonnull) SBSDKAspectRatioRange *aspectRatioRange;

@end
