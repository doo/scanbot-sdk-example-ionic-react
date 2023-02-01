//
//  SBSDKUIMedicalCertificateScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.01.22.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"
#import "SBSDKUIDialogStyle.h"
#import "SBSDKUIDialogButtonStyle.h"
#import "SBSDKOrientationLock.h"

/**
 * Configuration for the user interface of the medical certificate scanner.
 */
@interface SBSDKUIMedicalCertificateScannerUIConfiguration : NSObject

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Foreground color of the cancel button and when flash button is on. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the flash button when flash is off. */
@property (nonnull, nonatomic, strong) UIColor *flashButtonInactiveColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Whether the user guidance label is hidden or not. */
@property (nonatomic, assign, getter=isUserGuidanceHidden) BOOL userGuidanceHidden;

/** The text color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceTextColor;

/** The background color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceBackgroundColor;

/** The style of the dialog/alert in case of error. */
@property (nonnull, nonatomic, strong) SBSDKUIDialogStyle *errorDialogStyle;

/** The style of the dialogs/alerts OK button in case of error. */
@property (nonnull, nonatomic, strong) SBSDKUIDialogButtonStyle *errorDialogButtonStyle;

/** Line color of the view finder overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Width of the view finders lines. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/**
 * Aspect ratio of the view finder (width \ height). Set to nil if no view finder should be displayed.
 * The default is DIN A5 portrait: 148/210.
 */
@property (nullable, nonatomic, strong) SBSDKAspectRatio *finderAspectRatio;

/**
 * Secondary aspect ratio of finder frame (width \ height). Set to nil if no secondary view finder should be displayed.
 * The default is DIN A6 landscape: 148/105.
 */
@property (nullable, nonatomic, strong) SBSDKAspectRatio *finderSecondaryAspectRatio;

@end

