//
//  SBSDKUIMRZScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 20.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"
#import "SBSDKOrientationLock.h"

/** Configuration for user interface of the detector screens for machine readable zones. */
@interface SBSDKUIMRZScannerUIConfiguration : NSObject

/** Foreground color of the cancel button and when flash button is on. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the flash button when flash is off. */
@property (nonnull, nonatomic, strong) UIColor *flashButtonInactiveColor;

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Foreground color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Width of finder frame border. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/**
 * Aspect ratio of finder frame (width \ height), which is used to build actual finder frame.
 * Defaults to 7 : 1.
 */
@property (nonnull, nonatomic, strong) SBSDKAspectRatio *finderAspectRatio;

/** Foreground color of the description label. */
@property (nonnull, nonatomic, strong) UIColor *finderTextHintColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

@end
