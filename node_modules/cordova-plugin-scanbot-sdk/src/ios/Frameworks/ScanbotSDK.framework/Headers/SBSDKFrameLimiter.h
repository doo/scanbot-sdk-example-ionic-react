//
//  SBSDKFrameLimiter.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 26.10.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A simple frame limiter class. An object can use this class to limit the number of events fired per second.
 * E.g. A camera device captures video frames with 60 frames per second and passes them to a detector.
 * Use this class to limit the number of detector runs to a smaller value, like 20 frames per second,
 * skipping the remaining 40 frames per second. As the detector needs lots of CPU power this limit can drastically
 * reduce CPU usage and therefore saves battery.
 */
@interface SBSDKFrameLimiter : NSObject

/** The frames per second value of the receiver. */
@property(nonatomic, assign) NSUInteger fpsCount;

/** The total number of frames the receiver registered since it started. */
@property(nonatomic, readonly) NSUInteger framesTotal;

/** The total number of frames the receiver skipped since it started. */
@property(nonatomic, readonly) NSUInteger framesSkipped;

/** The minimum time in seconds that must pass by before processing the next frame (1.0 / fpsCount). */
@property(nonatomic, readonly) NSTimeInterval frameDuration;

/** The percentual ratio of skipped frames to total frames since the receivers start. */
@property(nonatomic, readonly) double throttleRate;

/**
 * Designated initializer.
 * @param fpsCount The maximum number of frames per second to be analyzed.
 */
- (instancetype)initWithFPSCount:(NSUInteger)fpsCount;

/**
 * Returns YES, if since the last frame enough time passed by to process the next frame, NO otherwise.
 */
- (BOOL)isReadyForNextFrame;

@end

NS_ASSUME_NONNULL_END
