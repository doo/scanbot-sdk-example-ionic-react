//
//  SBSDKSoundController.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 5/16/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 * A class to manage playback of sounds and vibration.
 */
@interface SBSDKSoundController : NSObject

/**
 * Plays a standard bleep sound.
 */
- (void)playBleepSound;

/** Plays a custom sound loaded from a given URL.
 * @param soundURL URL to the sound.
 */
- (void)playCustomSoundFromURL:(NSURL *)soundURL;

/**
 * Initiates a short vibration of the device. Can be used to give a haptic feedback.
 */
- (void)vibrate;

@end
