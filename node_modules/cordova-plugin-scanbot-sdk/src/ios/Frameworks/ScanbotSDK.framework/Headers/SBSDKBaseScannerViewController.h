//
//  SBSDKBaseScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 12.07.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKFeatures.h"
#import "SBSDKCameraSession.h"
#import "SBSDKBaseScannerGeneralConfiguration.h"
#import "SBSDKBaseScannerZoomConfiguration.h"
#import "SBSDKBaseScannerEnergyConfiguration.h"
#import "SBSDKBaseScannerViewFinderConfiguration.h"
#import "SBSDKOrientationLock.h"
#import "SBSDKApplicationState.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A highly customizable camera view controller that delivers a basic camera functionality along with video
 * frame extraction and preprocessing, orientation correction and still image capturing.
 *
 * Additionally you can opt-in several features using the SBSDKBaseScannerXXXConfiguration classes, e.g. zooming,
 * energy management and view finder.
 *
 * This class provides functions to be used and overwritten by subclasses to implement different detectors and recognizers.
 *
 */
@interface SBSDKBaseScannerViewController : UIViewController

/** The ScanbotSDK feature this view controller is used for. Readonly. */
@property (nonatomic, readonly) dooFeature feature;

/**
 * Sets or gets the used camera device. Can be used to toggle between the front and back cameras, tele and wide lens.
 */
@property (nonnull, nonatomic, strong) SBSDKCameraDevice* cameraDevice;

/**
 * Returns YES, after the receivers viewDidAppear method was called and NO after viewWillDisappear was called.
 */
@property (nonatomic, readonly) BOOL isVisible;

/**
 * Returns YES, if the video light is available on the device, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isFlashLightAvailable;

/**
 * Enables or disables the video light on the device.
 */
@property (nonatomic, assign, getter=isFlashLightEnabled) BOOL flashLightEnabled;

/**
 * A block being called when the flashlight is toggled. Defaults to nil.
 */
@property (nonatomic, copy, nullable) void (^flashLightDidChangeHandler)(void);

/**
 * A block being called when the application status was changed. Defaults to nil.
 */
@property (nonatomic, copy, nullable) void (^applicationStateDidChangeHandler)(SBSDKApplicationState);

/**
 * A block being executed when the zoom factor has changed. The new absolute zoom factor is provided as parameter.
 */
@property (nonatomic, copy, nullable) void (^zoomFactorDidChangeHandler)(CGFloat);

/**
 * A block being called whenever the view finder rectangle changes. 
 * Can be uses to layout UI elements with respect to the view finder position. Defaults to nil.
 * @param finderRect The new view finder rectangle in the coordinate system of the receivers view. 
 * Equals to CGRectZero, if the view finder is not active.
 */
@property (nonatomic, copy, nullable) void (^viewFinderRectDidChangeHandler)(CGRect finderRect);

/**
 * Set to NO, if you want to stop the recognition. Set to YES otherwise.
 * Make sure that you balance the calls to this properties setter.
 * Setting it twice to NO and only once to YES leaves the recognition still disabled.
 */
@property (atomic, assign, getter=isRecognitionEnabled) BOOL recognitionEnabled;

/**
 * Whether the camera permission status is accepted or not. Readonly.
 */
@property (atomic, readonly) BOOL isCameraUsageAuthorized;

/**
 * Whether the receiver is currently capturing a still image or not. Readonly.
 */
@property (atomic, readonly) BOOL isCapturingStillImage;

/** Return YES if energy saving currently is active and the recognition runs at a very low rate. Returns NO otherwise. */
@property (atomic, readonly, getter=isEnergySavingActive) BOOL energySavingActive;

/** 
 * The current camera zoom factor: a value between 0.0 (the minimum value of the zoom range) 
 * and 1.0 (the maximum value of the zoom range).
 */ 
@property (nonatomic, readonly) CGFloat cameraZoomFactor;

/**
 * The current absolute camera zoom factor: a value between 1.0x and the maximum video zoom factor of the camera device.
 */
@property (nonatomic, readonly) CGFloat cameraZoomFactorAbsolute;

/** The time interval since the last successful recognition. */
@property (nonatomic, readonly) NSTimeInterval timeIntervalSinceLastSuccessfulRecognition;

/** Returns YES, if focus lock is enabled, NO otherwise. Readonly. */
@property (nonatomic, readonly) BOOL isFocusLockEnabled;

/** The delay of recognition after appearance in seconds. Defaults to 0 seconds. */
@property (nonatomic, assign) NSTimeInterval initialScanDelay;

/**
 * The general configuration of the receiver. Lets you customize some of the basic behaviour.
 * It is copied on setting, so mutating the configuration after setting will not change the behaviour.
 * Instead, re-configure your instance and set it again.
 */
@property (nonatomic, copy) SBSDKBaseScannerGeneralConfiguration *generalConfiguration;

/**
 * The zoom configuration of the receiver. Lets you enable customize the zooming behaviour.
 * It is copied on setting, so mutating the configuration after setting will not change the behaviour.
 * Instead, re-configure your instance and set it again.
 */
@property (nonatomic, copy) SBSDKBaseScannerZoomConfiguration *zoomConfiguration;

/**
 * The energy configuration of the receiver. Lets you enable and customize the energy management.
 * It is copied on setting, so mutating the configuration after setting will not change the behaviour.
 * Instead, re-configure your instance and set it again.
 */
@property (nonatomic, copy) SBSDKBaseScannerEnergyConfiguration *energyConfiguration;

/**
 * The view finder configuration of the receiver. Lets you enable and customize the view finder.
 * It is copied on setting, so mutating the configuration after setting will not change the behaviour.
 * Instead, re-configure your instance and set it again.
 */
@property (nonatomic, copy) SBSDKBaseScannerViewFinderConfiguration *viewFinderConfiguration;

/**
 * A lazily generated transparent view that can be used to put UI elements too, like user guidance hints.
 */
@property (nonatomic, strong, readonly) UIView *overlayView;

/**
 * Readonly. Returns YES, if the camera session is currently being interrupted, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isSessionInterrupted;


/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

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
 * Sets the zoom factor to the specified value. 
 * @param zoomFactor A value between 0.0 (the minimum value of the zoom range) and 1.0 (the maximum value of the zoom range). 
 * The zoom range must be specified in the receivers zoomConfigurations zoomRange property.
 * Values outside the (0.0 - 1.0) range will be clipped. 
 * A zoom animation will be played if the receivers zoomConfigurations shouldAnimateZooming property is set to YES.
 */
- (void)setCameraZoomFactor:(CGFloat)zoomFactor;

/**
 * Sets the zoom factor to the specified value. 
 * @param zoomFactor A value between 0.0 (the minimum value of the zoom range) and 1.0 (the maximum value of the zoom range). 
 * The zoom range must be specified in the receivers zoomConfigurations zoomRange property.
 * Values outside the (0.0 - 1.0) range will be clipped. 
 * @param animated Set to YES, if the zooming should be animated, NO otherwise.
 */
- (void)setCameraZoomFactor:(CGFloat)zoomFactor animated:(BOOL)animated;

/**
 * Resets the zoom factor to the value 0.0: the minimum value of the zoom range 
 * specified in the receivers zoomConfigurations zoomRange property.
 */
- (void)resetZoom;

/** 
 * Manually starts energy saving mode. 
 */
- (void)startEnergySaving;

/** 
 * Manually ends energy saving mode. 
 */
- (void)endEnergySaving;

/**
 * Plays standart bleep sound.
 */
- (void)playBleepSound;

/**
 * Captures a still image asynchronously and passes the JPEG image data as NSData and if needed an error to the
 * completion handler.
 * @param completion The completion handler that is called when the still image has been captured.
 */
- (void)captureJPEGStillImageWithCompletionHandler:(nullable void (^)(UIImage* _Nullable, NSError* _Nullable))completion;

/** 
 * The current rect of the view finder in the coordinate system of the receivers view. 
 * If no view finder is active CGRectZero is returned. 
 */
- (CGRect)currentViewFinderRect;

/**
 * The current rect of the secondary view finder in the coordinate system of the receivers view.
 * If no secondary view finder is active CGRectZero is returned.
 */
- (CGRect)currentSecondaryViewFinderRect;

/**
 * Freezes the cameras preview layer by stopping the camera session.
 */
- (void)freezeCamera;

/**
 * Unfreezes the previously frozen cameras preview layer by restarting the camera session.
 */
- (void)unfreezeCamera;

@end

NS_ASSUME_NONNULL_END

