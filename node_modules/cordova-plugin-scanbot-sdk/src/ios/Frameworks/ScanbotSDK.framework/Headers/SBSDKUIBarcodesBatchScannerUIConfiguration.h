//
//  SBSDKUIBarcodesBatchScannerUIConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 12.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"
#import "SBSDKOrientationLock.h"

NS_ASSUME_NONNULL_BEGIN

/** Configuration for user interface of the detector screens for barcodes. */
@interface SBSDKUIBarcodesBatchScannerUIConfiguration : NSObject

/** Foreground color of the top bar buttons on the scanning screen. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the flash button when flash is off. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Foreground color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Width of finder frame border. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/**
 * Aspect ratio of finder frame (width \ height), which is used to build actual finder frame.
 * Default is 1 - it is a square frame, which is good for QR capturing.
 */
@property (nonatomic, strong) SBSDKAspectRatio *finderAspectRatio;

/** Foreground color of the description label. */
@property (nonnull, nonatomic, strong) UIColor *finderTextHintColor;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Text color of the barcodes count label. */
@property (nonnull, nonatomic, strong) UIColor *barcodesCountTextColor;

/** Text color in the details barcodes list. Also affects image background, separator and progress spinner. */
@property (nonnull, nonatomic, strong) UIColor *detailsPrimaryColor;

/** Foreground color of the top bar buttons on the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsActionColor;

/** Background color of the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsBackgroundColor;

@end

NS_ASSUME_NONNULL_END
