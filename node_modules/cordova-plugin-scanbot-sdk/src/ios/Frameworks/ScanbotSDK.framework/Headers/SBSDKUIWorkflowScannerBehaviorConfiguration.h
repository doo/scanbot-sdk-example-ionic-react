//
//  SBSDKUIWorkflowScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 21.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageFileFormat.h"
#import "SBSDKVideoContentMode.h"
#import "SBSDKOrientationLock.h"

NS_ASSUME_NONNULL_BEGIN

/** Behavior configuration object for a 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowScannerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. */
@property(nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** The scaling factor for captured images. Values are clamped to the range 0.0 - 1.0. */
@property(nonatomic, assign) CGFloat imageScale;

/**
 * The sensitivity of auto-snapping. Values are clamped to the range 0.0 - 1.0.
 * A value of 1.0 triggers automatic snapping immediately, a value of 0.0 delays the automatic by 3 seconds.
 */
@property(nonatomic, assign) CGFloat autoSnappingSensitivity;

/**
 * The minimum score in percent (0 - 100) of the perspective distortion to accept a detected document.
 * Default is 75.0. Set lower values to accept more perspective distortion.
 * Warning: Lower values result in more blurred document images.
 */
@property(nonatomic, assign) double acceptedAngleScore;

/**
 * The minimum size in percent (0 - 100) of the screen size to accept a detected document.
 * It is sufficient that height or width match the score. Default is 80.0.
 * Warning: Lower values result in low resolution document images.
 */
@property(nonatomic, assign) double acceptedSizeScore;

/** The video layers content mode. */
@property(nonatomic) SBSDKVideoContentMode cameraPreviewMode;

/** The preferred orientation of captured images. */
@property(nonatomic) SBSDKOrientationLock orientationLockMode;

/** If set to YES, ignores the aspect ratio warning. */
@property(nonatomic, assign) BOOL ignoreBadAspectRatio;

/**
 * Limits the maximum size of the document image. If width or height are zero, this property is effectively ignored.
 * Defaults to CGSizeZero.
 */
@property(nonatomic, assign) CGSize documentImageSizeLimit;

/** Whether scanner screen should make a sound on successful barcode or MRZ detection. */
@property(nonatomic, assign, getter=isSuccessBeepEnabled) BOOL successBeepEnabled;

/** If set to YES removes any stored images when the user cancels the workflow. Defaults to YES. */
@property(nonatomic, assign) BOOL cleanupOnCancel;

@end

NS_ASSUME_NONNULL_END
