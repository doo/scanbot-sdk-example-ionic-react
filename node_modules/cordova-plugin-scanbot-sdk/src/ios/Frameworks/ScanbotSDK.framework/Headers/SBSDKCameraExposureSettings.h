//
//  SBSDKCameraExposureSettings.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.06.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 * This class provides information about the current cameras exposure settings.
 **/
@interface SBSDKCameraExposureSettings : NSObject

/** The exposure duration of the camera in milliseconds. */
@property(nonatomic, readonly) double exposureDuration;

/**
 * The exposure target offset in EV.
 * Negative values mean the image is too dark, positive values mean the image is too bright.
 * Usually the camera automatically tries to adapt its exposure parameters to keep the exposure target offset at a
 * value of 0 resulting in a proper exposure of the image.
 * If this value is not close to 0 the camera cannot adjust its exposure parameters properly, the image is either
 * way too dark or too bright.
 */
@property(nonatomic, readonly) float exposureTargetOffset;


/**
 * The ISO (or amplification) value of the camera.
 * The higher the value the more noise and less detail the image will have.
 */
@property(nonatomic, readonly) float ISOValue;

@end
