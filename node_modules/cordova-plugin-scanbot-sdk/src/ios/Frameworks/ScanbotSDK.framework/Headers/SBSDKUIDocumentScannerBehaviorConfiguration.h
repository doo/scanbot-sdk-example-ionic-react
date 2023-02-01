//
//  SBSDKUIDocumentScannerBehaviorConfiguration.h
//  SBSDK Internal Demo
//
//  Created by Yevgeniy Knizhnik on 3/1/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageFileFormat.h"
#import "SBSDKVideoContentMode.h"
#import "SBSDKImageFilterTypes.h"
#import "SBSDKDocumentDetector.h"
#import "SBSDKCapturePhotoQualityPrioritization.h"

/** Configuration for the behavior of the document scanning screen. */
@interface SBSDKUIDocumentScannerBehaviorConfiguration : NSObject

/** Whether auto-snapping is enabled or not. */
@property (nonatomic, assign, getter=isAutoSnappingEnabled) BOOL autoSnappingEnabled;

/** Whether user guidance is enabled while auto-snapping is disabled. */
@property (nonatomic, assign) BOOL forceUserGuidance;

/** Whether multi-page snapping is enabled or not. */
@property (nonatomic, assign, getter=isMultiPageEnabled) BOOL multiPageEnabled;

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** The scaling factor for captured images. Values are clamped to the range 0.0 - 1.0. */
@property (nonatomic, assign) CGFloat imageScale;

/**
 * Limits the maximum size of the document image. If width or height are zero, this property is effectively ignored.
 * Defaults to CGSizeZero.
 */
@property (nonatomic, assign) CGSize documentImageSizeLimit;

/**
 * The sensitivity of auto-snapping. Values are clamped to the range 0.0 - 1.0.
 * A value of 1.0 triggers automatic snapping immediately, a value of 0.0 delays the automatic by 3 seconds.
 */
@property (nonatomic, assign) CGFloat autoSnappingSensitivity;

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
@property (nonatomic) SBSDKVideoContentMode cameraPreviewMode;

/** If set to YES, ignores the aspect ratio warning. */
@property (nonatomic, assign) BOOL ignoreBadAspectRatio;
        
/** The default image filter type for new documents pages. Defaults to SBSDKImageFilterTypeNone. */
@property (nonatomic, assign) SBSDKImageFilterType defaultPageFilter;

/**
 * If set to YES, the default, the camera session will be stopped entirely,
 * when the receiver disappears and restarts when the receiver reappears.
 * There is no CPU usage while the receiver is not on screen.
 *
 * NO will NOT stop the camera session, but pause the delivery of video frames and QR codes.
 * There is some very low CPU activity while the receiver is not on screen, but there is also no
 * lag when the receiver returns to the screen.
 */
@property (nonatomic, assign) BOOL stopsCameraSessionWhenDisappeared;

/** Maximum number of pages to scan. Ignored when set to nil, or when `multiPageEnabled` is NO. Default is nil. */
@property (nullable, nonatomic, strong) NSNumber *maxNumberOfPages;

/**
 * The mode of the document detector to be used for document outline detection.
 * The default value  can be set via `+ (void)setDefaultDetectorMode:(SBSDKDocumentDetectorMode)newDefaultDetectorMode;`.
 * If not set specifically the default value is `SBSDKDocumentDetectorModeMachineLearning`.
 */
@property (nonatomic, assign) SBSDKDocumentDetectorMode detectorMode;

/**
 * The priorization of still image quality and capturing speed.
 * Defaults to SBSDKCapturePhotoQualityPrioritizationBalanced.
 * If you experience lots of blurry still images try to set this property to SBSDKCapturePhotoQualityPrioritizationQuality.
 *
 * Note: Has no effect on devices prior to iOS 13.0!
 */
@property (nonatomic, assign) SBSDKCapturePhotoQualityPrioritization photoQualityPriorization;

@end
