//
//  SBSDKUINFCPassportReaderUIConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKOrientationLock.h"

/** Configuration for user interface of the NFC reader screen. */
@interface SBSDKUINFCPassportReaderUIConfiguration : NSObject

/** Foreground color of the cancel button and selected flash button. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the flash button when the flash is off. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Width of inner finder frame border. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/** Foreground color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Foreground color of the description label. */
@property (nonnull, nonatomic, strong) UIColor *finderTextHintColor;

/** Color of the progress bar. */
@property (nonnull, nonatomic, strong) UIColor *progressBarColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

@end

