//
//  SBSDKCameraSession.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 22.04.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "SBSDKFeatures.h"
#import "SBSDKCameraExposureSettings.h"
#import "SBSDKCapturePhotoQualityPrioritization.h"
#import "SBSDKCameraDevice.h"
#import "SBSDKVideoContentMode.h"

/**
 * A delegate protocol that gathers AVCaptureVideoDataOutputSampleBufferDelegate
 * and AVCaptureMetadataOutputObjectsDelegate protocols.
 */
@protocol SBSDKCameraSessionDelegate <AVCaptureVideoDataOutputSampleBufferDelegate,
AVCaptureMetadataOutputObjectsDelegate>
@end

/**
 * An easy-to-use wrapper around the AVFoundations video capture session. Sets up and configures the
 * camera device and the preview layer. Provides functionality to capture still images.
 */
@interface SBSDKCameraSession : NSObject

/**
 * The preview layer that the camera device uses to output the current video frames.
 * Can be added to any superlayer.
 */
@property (nonatomic, readonly, nonnull) AVCaptureVideoPreviewLayer *previewLayer;

/**
 * Returns the video resolution of the current video output. Orientation is taken into account.
 * Returns CGSizeZero, if the capture session is not running.
 */
@property (nonatomic, readonly) CGSize videoResolution;

/**
 * Sets or gets the current video orientation.
 */
@property (nonatomic, assign) AVCaptureVideoOrientation videoOrientation;

/**
 * The delegate object for camera output.
 * Its receives the video frames, still image captures and meta data capture, like QR code.
 * Delegates can implement all functions from AVCaptureVideoDataOutputSampleBufferDelegate and
 * AVCaptureMetadataOutputObjectsDelegate protocols.
 */
@property (nonatomic, weak, nullable) id<SBSDKCameraSessionDelegate> videoDelegate;

/**
 * Returns YES if the camera is currently in the process of taking a still image, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isCapturingStillImage;

/**
 * Returns YES if the camera device has a torch light and the torch light is available.
 */
@property (nonatomic, readonly) BOOL torchLightAvailable;

/**
 * Turns the torch light on or off.
 */
@property (nonatomic, assign, getter = isTorchLightEnabled) BOOL torchLightEnabled;

/**
 * A block being executed when the torch light status changes (mode or availability).
 */
@property (nonatomic, copy, nullable) void (^updateTorchlightBlock)(void);

/**
 * A block being executed when the zoom factor has changed. The new zoom factor is provided as parameter.
 */
@property (nonatomic, copy, nullable) void (^updateZoomBlock)(CGFloat);

/**
 * The AVCaptureSession object.
 */
@property (nonatomic, readonly, nullable) AVCaptureSession* captureSession;

/**
 * Returns the current cameras exposure settings.
 */
@property (nonatomic, readonly, nullable) SBSDKCameraExposureSettings* exposureSettings;

/**
 * The camera devices minimum zoom factor. Readonly.
 */
@property (nonatomic, readonly) CGFloat minZoom;

/**
* The camera devices maximum zoom factor. Readonly.
*/
@property (nonatomic, readonly) CGFloat maxZoom;

/**
 * Sets or gets the camera devices current zoom factor. Zooming is done without animation.
 * If the new value exceeds the minimum or maximum value for zooming it is clamped.
 */
@property (nonatomic, assign) CGFloat zoomValue;

/**
 * YES, if the camera currently is zooming, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isZooming;

/**
 * YES, if zooming is available. No otherwise.
 */
@property (nonatomic, readonly) BOOL isZoomAvailable;

/**
 * Returns YES, if focus lock is enabled, NO otherwise. Readonly.
 */
@property (nonatomic, readonly) BOOL isFocusLockEnabled;

/**
 * The priorization of still image quality and capturing speed.
 * Defaults to SBSDKCapturePhotoQualityPrioritizationBalanced.
 *
 * Note: Has no effect on devices prior to iOS 13.0!
 */
@property (nonatomic, assign) SBSDKCapturePhotoQualityPrioritization photoQualityPriorization;

/**
 * The content mode of the video preview layer: fit-in or fill-in. Defaults to SBSDKVideoContentModeFillIn.
 */
@property (nonatomic, assign) SBSDKVideoContentMode videoContentMode;

/**
 * The camera device to be used.
 */
@property (nonatomic, strong, readonly, nonnull) SBSDKCameraDevice *device;

/**
 * Returns YES, if the front side camera is used.
 */
@property (nonatomic, readonly) BOOL isFrontCameraUsed;

/**
 * The designated initializer of the class. Does not start the capture session.
 * @param feature The feature you want to use the camera for.
 * @return Newly created and configured instance.
 */
- (nonnull instancetype)initForFeature:(dooFeature)feature;

/**
 * Extended initializer of the class. Does not start the capture session.
 * @param feature The feature you want to use the camera for.
 * @param preset The camera session preset the receiver wants to use.
 * @return Newly created and configured instance or nil, if preset is not supported or setup failed.
 */
- (nullable instancetype)initForFeature:(dooFeature)feature withPreset:(AVCaptureSessionPreset _Nonnull)preset;

/**
 * Extended initializer of the class. Does not start the capture session.
 * @param feature The feature you want to use the camera for.
 * @param device The camera device to be used.
 * @return Newly created and configured instance or nil, if preset is not supported or setup failed.
 */
- (nullable instancetype)initForFeature:(dooFeature)feature
                             withDevice:(SBSDKCameraDevice  * _Nonnull)device;

/**
 * Starts the camera capture session asynchronously and calls the completion block when finished.
 * @param completion Completion handler with boolean flag, indicating if the session is running or not.
 */
- (void)startSession:(void (^_Nullable)(BOOL))completion;

/**
 * Stops the camera capture session. Does nothing if the session is already stopped.
 */
- (void)stopSession;

/**
 * Returns YES if the camera session has already been started, NO otherwise.
 */
- (BOOL)isSessionRunning;

/** 
 * Pauses the detection of documents and QR codes.
 */
- (void)pauseDetection;

/**
 * Resumes the detection of documents and QR codes.
 */
- (void)resumeDetection;

/**
 * Freezes the camera session.
 */
- (void)freezeSession;

/**
 * Unfreezes the camera session.
 */
- (void)unfreezeSession;

/**
 * Returns YES, if detection is paused, NO otherwise.
 */
- (BOOL)isDetectionPaused;

/**
 * Captures a still image asynchronously and passes the CMSampleBufferRef and if needed an error to the
 * completion handler. The CMSampleBufferRef can be converted to any image format/object like UIImage.
 * @param completion The completion handler that is called when the still image has been captured.
 */
- (void)captureStillImageWithCompletionHandler:(nullable void (^)(CVPixelBufferRef _Nullable,  NSError* _Nullable))completion;

/**
 * Captures a still image asynchronously and passes the JPEG image data as NSData and if needed an error to the
 * completion handler.
 * @param completion The completion handler that is called when the still image has been captured.
 */
- (void)captureJPEGStillImageWithCompletionHandler:(nullable void (^)(NSData* _Nullable, NSError* _Nullable))completion;

/**
 * Returns YES, if the camera is currently adjusting autofocus, exposure or white balance, NO otherwise.
 */
- (BOOL)isCameraAdjusting;

/**
 * Sets the camera devices current zoom factor.
 * If the new value exceeds the minimum or maximum value for zooming it is clamped.
 * @param zoomValue The new zoom factor to be set.
 * @param animated If YES, the zooming is animated, otherwise the change is applied without an animation.
 */
- (void)setZoomValue:(CGFloat)zoomValue animated:(BOOL) animated;

/**
 * Resets the zoom factor to the minimum zoom value.
 * @param animated If YES, the zooming is animated, otherwise the change is applied without an animation.
 */
- (void)resetZoomAnimated:(BOOL)animated;

/**
 * Disables auto-focus and locks the lens at the specified lens position.
 * @param lensPosition The position of the lens. Values can be between 0.0f (minimum focusing distance) and
 * 1.0f (maximum focusing distance). The value will be clamped to [0.0f, 1.0f].
 * @return YES, if the attempt to lock the focus was successful, NO if the attempt failed or if focus lock is
 * not available.
 */
- (BOOL)beginFocusLockAtLensPosition:(CGFloat)lensPosition;

/**
 * Ends the focus lock and returns to standard continous auto-focus.
 */
- (void)endFocusLock;

/**
 * Converts a view space rectangle into the image space of a sample buffer.
 * @param The rectangle to convert in view coordinates of the view the sessions preview layer is attached to.
 * @param The sample buffer into which space the rectangle should be converted.
 * @return The rectangle transformed into the sample buffers image space.
 */
- (CGRect)transformedRegionOfInterestForViewRect:(CGRect)viewRect
                                  inSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer;

@end
