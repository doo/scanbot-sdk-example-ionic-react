//
//  SBSDKUICroppingScreenUIConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/17/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKOrientationLock.h"

/** Configuration for user interface of the page cropping screen. */
@interface SBSDKUICroppingScreenUIConfiguration : NSObject

/** Foreground color of the top bar buttons (Done, Cancel). */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Text color of the title in the top bar. */
@property (nonnull, nonatomic, strong) UIColor *titleColor;

/** Text color of the hint title. */
@property (nonnull, nonatomic, strong) UIColor *hintTitleColor;

/** Foreground color of the rotate button. */
@property (nonnull, nonatomic, strong) UIColor *bottomBarButtonsColor;

/** Background color of the bottom bar. */
@property (nonnull, nonatomic, strong) UIColor *bottomBarBackgroundColor;

/** The line color of the current polygon that crops the page. */
@property (nonnull, nonatomic, strong) UIColor *polygonColor;

/** The line color of the detected polygon that crops the page. */
@property (nonnull, nonatomic, strong) UIColor *polygonColorMagnetic;

/** The color of anchor points. */
@property(nonatomic, strong, nullable) UIColor *anchorPointsColor;

/** Background color of the view. Same as `viewController.view.backgroundColor`.*/
@property (nonnull, nonatomic, strong) UIColor *backgroundColor;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Whether the rotate button is hidden or not. */
@property (nonatomic, assign, getter=isRotateButtonHidden) BOOL rotateButtonHidden;

/** Whether the detect/reset button is hidden or not. */
@property (nonatomic, assign, getter=isDetectResetButtonHidden) BOOL detectResetButtonHidden;

/** Defines if the top and bottom buttons are swapped. Default is NO. */
@property (nonatomic, assign,getter=isTopAndBottomButtonsSwapped) BOOL topAndBottomButtonsSwapped;

/** Defines the width of the polygon line in the cropping view. The default value is 2. */
@property (nonatomic, assign) CGFloat polygonLineWidth;

@end
