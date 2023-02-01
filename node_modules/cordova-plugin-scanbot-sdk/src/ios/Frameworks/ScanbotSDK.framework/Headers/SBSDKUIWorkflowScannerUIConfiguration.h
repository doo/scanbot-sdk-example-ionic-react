//
//  SBSDKUIWorkflowScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 21.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKOrientationLock.h"

NS_ASSUME_NONNULL_BEGIN

/** User interface configuration object for a 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowScannerUIConfiguration : NSObject

/** Foreground color of the flash button when deactivated. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Foreground color of the cancel button and the flash button when activated. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsActiveColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the detection overlay. */
@property (nullable, nonatomic, strong) UIColor *finderLineColor;

/** Background color of the detection overlay. */
@property (nullable, nonatomic, strong) UIColor *finderBackgroundColor;

/** Foreground color of the step title label. */
@property (nonnull, nonatomic, strong) UIColor *titleTextColor;

/** Foreground color of the step message label. */
@property (nonnull, nonatomic, strong) UIColor *messageTextColor;

/** Background color of the bottom bar. */
@property (nonnull, nonatomic, strong) UIColor *bottomBarBackgroundColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Foreground color of the detected documents polygon, when the polygons quality is acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonColorOK;

/** Foreground color of the detected documents polygon, when the polygons quality is not acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonColor;

/** Background color of the detected documents polygon, when the polygons quality is acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonBackgroundColorOK;

/** Background color of the detected documents polygon, when the polygons quality is not acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonBackgroundColor;

/** Width of the detected documents polygon in points. */
@property (nonatomic, assign) CGFloat polygonLineWidth;

/** Background color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceBackgroundColor;

/** Foreground/text color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceTextColor;

@end

NS_ASSUME_NONNULL_END
