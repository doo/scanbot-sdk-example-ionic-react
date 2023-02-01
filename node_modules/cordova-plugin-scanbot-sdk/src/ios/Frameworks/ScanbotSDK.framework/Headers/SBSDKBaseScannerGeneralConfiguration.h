//
//  SBSDKBaseScannerGeneralConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 19.07.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKVideoContentMode.h"
#import "SBSDKCapturePhotoQualityPrioritization.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The general configuration object for a 'SBSDKBaseScannerViewController' and its subclasses.
 */
@interface SBSDKBaseScannerGeneralConfiguration : NSObject

/**
 * The content mode of the video preview layer: fit-in or fill-in. Defaults to SBSDKVideoContentModeFillIn.
 */
@property (nonatomic, assign) SBSDKVideoContentMode videoContentMode;

/**
 * The priorization of still image quality and capturing speed.
 * Defaults to SBSDKCapturePhotoQualityPrioritizationBalanced.
 * If you experience lots of blurry still images try to set this property to SBSDKCapturePhotoQualityPrioritizationQuality.
 *
 * Note: Has no effect on devices prior to iOS 13.0!
 */
@property (nonatomic, assign) SBSDKCapturePhotoQualityPrioritization photoQualityPriorization;

/**
 * If set to YES, the camera session will be stopped entirely, when the base scanner view controller disappears,
 * and restarts when the it reappears.
 * The base scanner view controller will cause no CPU load after it disappeared.
 *
 * NO will NOT stop the camera session, but pauses the delivery of video frames from the camera session to the
 * base scanner view controller.
 * There is some low CPU activity while the base scanner view controller is not on screen, but there is also no
 * delay when the receiver returns to the screen.
 */
@property (nonatomic, assign) BOOL stopsCameraSessionWhenDisappeared;

/**
 * Disables auto-focus and locks the lens at the specified focus lens position. The default value is NO.
 */
@property (nonatomic, assign, getter=isFocusLockEnabled) BOOL focusLockEnabled;

/**
 * The position of the lens. Values can be between 0.0f (minimum focusing distance) and
 * 1.0f (maximum focusing distance). The value will be clamped to [0.0f, 1.0f]. The default value is 0.0.
 */
@property (nonatomic, assign) CGFloat focusLockPosition;

/** Whether the receiver plays a flash-light animation when capturing images or not. Defaults to NO. */
@property (nonatomic, assign) BOOL playFlashAnimation;

/**
 * This is the default configuration with the properties initialized as mentioned in their description.
 * @return The default general configuration object which can be changed and then passed back to the
 * base scanner view controller.
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
