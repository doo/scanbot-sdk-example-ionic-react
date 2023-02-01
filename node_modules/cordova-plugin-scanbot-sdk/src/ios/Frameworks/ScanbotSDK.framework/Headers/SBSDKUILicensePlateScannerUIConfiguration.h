//
//  SBSDKUILicensePlateScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIDialogStyle.h"
#import "SBSDKUIDialogButtonStyle.h"
#import "SBSDKOrientationLock.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the user interface look and feel of the license plate scanner.
 */
@interface SBSDKUILicensePlateScannerUIConfiguration : NSObject

/** Foreground color of the top bar buttons when they are active. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Foreground color of the top bar buttons when they are inactive. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Width of finder frame border. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/** The preferred heigth of the view finder. Defaults to 150.0. */
@property (nonatomic) CGFloat finderPreferredHeight;

/** Foreground color of the description label. */
@property (nonnull, nonatomic, strong) UIColor *finderTextHintColor;

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Whether the flash button is hidden or not. Default is NO. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** The style of the confirmation dialog. */
@property (nonatomic, strong) SBSDKUIDialogStyle *confirmationDialogStyle;

/** The style of the confirmation dialogs confirm button. */
@property (nonatomic, strong) SBSDKUIDialogButtonStyle *confirmationDialogConfirmButtonStyle;

/** The style of the confirmation dialogs retry button. */
@property (nonatomic, strong) SBSDKUIDialogButtonStyle *confirmationDialogRetryButtonStyle;

@end

NS_ASSUME_NONNULL_END
