//
//  SBSDKBaseCameraViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.08.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKFeatures.h"
#import "SBSDKCameraSession.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A basic camera view controller. Can be used for custom video frame detection.
 */
@interface SBSDKBaseCameraViewController : UIViewController

/**
 * The controllers camera session.
 */
@property (nonatomic, strong, readonly, nonnull) SBSDKCameraSession *cameraSession;

/**
 * If set to YES (default), the camera session will be stopped entirely,
 * when the receiver disappears and restarts when the receiver reappears.
 * There is no CPU usage while the receiver is not on screen.
 *
 * NO will NOT stop the camera session, but pause the delivery of video frames and QR codes.
 * There is some very low CPU activity while the receiver is not on screen, but there is also no
 * lag when the receiver returns to the screen.
 */
@property (nonatomic, assign) BOOL stopsCameraSessionWhenDisappeared;

/**
 * The desired maximum detection rate of the receiver. The maximum number of video frames per second to
 * be analyzed. Defaults to 20.
 */
@property (nonatomic, assign) NSUInteger detectionRate;


/**
 * Sets or gets the used camera device. Can be used to toggle between the front and back cameras, tele and wide lens.
 */
@property (nonnull, nonatomic, strong) SBSDKCameraDevice* cameraDevice;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 */
- (nullable instancetype)initWithParentViewController:(nullable UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView
                                              feature:(dooFeature)feature;

/**
 * This function is called whenever a new video frame is being delivered.
 */
- (void)willReceiveVideoFrame;

/**
 * This function is called when a new video frame is being delivered and the frame limiter does not skip
 * the frame. Do your custom recognition here.
 * @param sampleBuffer The CMSampleBufferRef containing the video frame data.
 * @param orientation The cameras orientation. Can be used to rotate the sample buffer if needed.
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer videoOrientation:(AVCaptureVideoOrientation)orientation;

/**
 * Updates utility and helper layer frames. Subclasses can override this function to update their own subviews and
 * sublayers.
 */
- (void)updateLayerFrames;

@end

NS_ASSUME_NONNULL_END
