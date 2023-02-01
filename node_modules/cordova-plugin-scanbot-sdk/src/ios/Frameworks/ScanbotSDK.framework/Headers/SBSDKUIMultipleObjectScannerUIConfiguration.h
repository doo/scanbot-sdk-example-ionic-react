//
//  SBSDKUIMultipleObjectScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 03.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKOrientationLock.h"


/** Configuration for user interface of the document scanning screen. */
@interface SBSDKUIMultipleObjectScannerUIConfiguration : NSObject

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of disabled items in the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Foreground color of enabled items in the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsActiveColor;

/** Whether the multi-page button is hidden or not. Default is NO.*/
@property (nonatomic, assign, getter=isBatchButtonHidden) BOOL batchButtonHidden;

/** Whether the flash button is hidden or not. Default is NO. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. Default is NO. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Color of the shutter buttons outer ring in manual-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonOuterColor;

/** Color of the shutter buttons inner ring in manual-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonInnerColor;

/** Color of the shutter buttons activity indicator when capturing an image. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonIndicatorColor;

/** Foreground color of the buttons in the bottom bar. **/
@property (nonnull, nonatomic, strong) UIColor *bottomBarButtonsColor;

/** Background color of the bottom bar. **/
@property (nonnull, nonatomic, strong) UIColor *bottomBarBackgroundColor;

/** Background color of the camera view. **/
@property (nonnull, nonatomic, strong) UIColor *cameraBackgroundColor;

/** Foreground color of the detected objects polygon, when the polygons quality is not acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonColor;

/** Background color of the detected objects polygon, when the polygons quality is not acceptable. **/
@property (nonnull, nonatomic, strong) UIColor *polygonBackgroundColor;

/** Width of the detected objects polygon in points. Default is 3. */
@property (nonatomic, assign) CGFloat polygonLineWidth;

/** Allowed orientations for automatic interface rotations. Default is UIInterfaceOrientationMaskPortrait. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

@end

