//
//  SBSDKUIDocumentScannerUIConfiguration.h
//  SBSDK Internal Demo
//
//  Created by Yevgeniy Knizhnik on 3/1/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKOrientationLock.h"

/** Configuration for the user interface of the document scanning screen. */
@interface SBSDKUIDocumentScannerUIConfiguration : NSObject

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of disabled items in the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Foreground color of enabled items in the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsActiveColor;

/** Whether the multi-page button is hidden or not. */
@property (nonatomic, assign, getter=isMultiPageButtonHidden) BOOL multiPageButtonHidden;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Whether the auto-snapping button is hidden or not. Has no effect, if shutterButtonHidden is set to YES. */
@property (nonatomic, assign, getter=isAutoSnappingButtonHidden) BOOL autoSnappingButtonHidden;

/**
 * Hides the shutter button if set to YES. Shows it otherwise. Defaults to NO.
 * If set to YES, auto-snapping is enabled and the property autoSnappingEnabled of the behavior configuration will
 * have no effect.
 * Also the auto-snapping button will be hidden.
 */
@property (nonatomic, assign, getter=isShutterButtonHidden) BOOL shutterButtonHidden;

/** Color of the shutter buttons outer ring in auto-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonAutoOuterColor;

/** Color of the shutter buttons inner ring in auto-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonAutoInnerColor;

/** Color of the shutter buttons outer ring in manual-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonManualOuterColor;

/** Color of the shutter buttons inner ring in manual-capture mode. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonManualInnerColor;

/** Color of the shutter buttons activity indicator when capturing an image. */
@property (nonnull, nonatomic, strong) UIColor *shutterButtonIndicatorColor;

/** Foreground color of the buttons in the bottom bar. **/
@property (nonnull, nonatomic, strong) UIColor *bottomBarButtonsColor;

/** Background color of the bottom bar. **/
@property (nonnull, nonatomic, strong) UIColor *bottomBarBackgroundColor;

/** Background color of the camera view. **/
@property (nonnull, nonatomic, strong) UIColor *cameraBackgroundColor;

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

/**
 * The radius to use when drawing rounded corners of the detected documents polygon. Default is 8.0.
 */
@property (nonatomic, assign) CGFloat polygonCornerRadius;

/** Background color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceBackgroundColor;

/** Foreground/text color of the user guidance label. */
@property (nonnull, nonatomic, strong) UIColor *userGuidanceTextColor;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Stroke color of polygon auto snap progress animation. */
@property (nonnull, nonatomic, strong) UIColor *polygonAutoSnapProgressColor;

/** Line width of polygon auto snap progress animation. Default is 5.0. */
@property (nonatomic, assign) CGFloat polygonAutoSnapProgressLineWidth;

/** Whether polygon auto snap progress animation is enabled or no. Default is enabled.*/
@property (nonatomic, assign, getter=isPolygonAutoSnapProgressEnabled) BOOL polygonAutoSnapProgressEnabled;

@end
