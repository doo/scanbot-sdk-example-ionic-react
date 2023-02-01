//
//  SBSDKUICheckRecognizerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"
#import "SBSDKUIDialogStyle.h"
#import "SBSDKUIDialogButtonStyle.h"
#import "SBSDKOrientationLock.h"

/**
 * Configuration for the user interface of the check scanner.
 */
@interface SBSDKUICheckRecognizerUIConfiguration : NSObject

/** Foreground color of the cancel button and when flash button is on. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the top bar buttons (flash) when disabled. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** The foreground color of the viewFinder. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** The background color of the camera overlay outside the view finders area. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** The width of the view finder lines. The default value is 2. */
@property (nonatomic, assign) CGFloat finderLineWidth;

/** The text color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceTextColor;

/** The background color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceBackgroundColor;

/** The style of the dialog/alert in case of error. */
@property (nonnull, nonatomic, strong) SBSDKUIDialogStyle *errorDialogStyle;

/** The style of the dialogs/alerts OK button in case of error. */
@property (nonnull, nonatomic, strong) SBSDKUIDialogButtonStyle *errorDialogButtonStyle;

@end
