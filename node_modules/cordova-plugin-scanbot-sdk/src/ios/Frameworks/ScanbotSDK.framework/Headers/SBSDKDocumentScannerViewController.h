//
//  SBSDKDocumentScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import "SBSDKBaseScannerViewController.h"
#import "SBSDKDocumentDetector.h"
#import "SBSDKDocumentScannerStatusTextConfiguration.h"
#import "SBSDKDetectionStatusLabel.h"
#import "SBSDKShutterButton.h"
#import "SBSDKImageFilterTypes.h"
#import "SBSDKAutoSnappingMode.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKDocumentScannerViewController;

/**
 * The delegate protocol of 'SBSDKDocumentScannerViewController'. 
 */
@protocol SBSDKDocumentScannerViewControllerDelegate <NSObject>

/** 
 * Informs the delegate that the document scanner detected and captured a document and provides
 * the original image, the cropped document image and the result of the detection.
 * @param controller The document scanner controller that called this function.
 * @param documentImage The image of the document: cropped, filtered and perspective corrected.  
 * @param originalImage The original image the document was detected on.
 * @param result The result of the document detection. 
 * @param autoSnapped YES, if the result was automatically snapped, NO otherwise. 
 */
- (void)documentScannerViewController:(SBSDKDocumentScannerViewController *)controller 
                 didSnapDocumentImage:(UIImage *)documentImage 
                              onImage:(UIImage *)originalImage
                           withResult:(SBSDKDocumentDetectorResult *)result
                          autoSnapped:(BOOL)autoSnapped;

@optional
/**
 * Optional.
 * Asks the delegate whether it should run the document detection on the next video frame. 
 * Implement only if you need a very specific interruption of the detection. You do not need to implement this function
 * if you want to interrupt the detection when the scanner view controller is invisible or covered 
 * by a presented view controller.
 * @param controller The document scanner controller that called this function.
 * @return YES, if you want to run the document detection on the next video frame, NO otherwise.
 */
- (BOOL)documentScannerViewControllerShouldDetectDocument:(SBSDKDocumentScannerViewController *)controller;

/**
 * Optional.
 * Informs the delegate that the document scanner has processed a video frame. Called on main thread.
 * @param controller The document scanner controller that called this function.
 * @param videoFrameImage An UIImage with the contents of the video frame.
 * @param result The result of the document detection done on this video frame.
 */
- (void)documentScannerController:(nonnull SBSDKDocumentScannerViewController *)controller
              didSampleVideoFrame:(nonnull UIImage *)videoFrameImage
                  detectionResult:(nonnull SBSDKDocumentDetectorResult *)result;

/**
 * Optional.
 * Informs the delegate that the document scanner controller is going to capture an image.
 * @param controller The document scanner controller that called this function.
 */
- (void)documentScannerViewControllerWillSnapImage:(SBSDKDocumentScannerViewController *)controller;

/** 
 * Optional.
 * Informs the delegate that snapping an image failed.
 * @param controller The document scanner controller that called this function.
 * @param error The error describing why the snapping failed. 
 */
- (void)documentScannerViewControllerDidFailSnappingImage:(SBSDKDocumentScannerViewController *)controller 
                                                withError:(nullable NSError *)error;

/**
 * Optional.
 * Asks the delegate whether it should automatically snap an image when a document was detected on the video frame.
 * Is not called if autoSnappingMode is set to SBSDKAutosnappingModeDisabled or SBSDKAutosnappingModeDisabledWithGuidance.
 * @param controller The document scanner controller that called this function.
 * @param result The result of the document detection on the previous video frame.
 * @return YES, if you want to schedule automatic snapping, NO otherwise.
 */
- (BOOL)documentScannerViewController:(SBSDKDocumentScannerViewController *)controller 
shouldAutoSnapImageWithForDetectionResult:(SBSDKDocumentDetectorResult *)result;

/**
 * Optional.
 * Asks the delegate for the line color of the polygon that surrounds the detected polygon on the screen, depending on
 * the document detection status.
 * @param controller The document scanner controller that called this function.
 * @param status The status of the current document detection.
 * @return The line color for the displayed polygon.
 */
- (UIColor *)documentScannerViewController:(SBSDKDocumentScannerViewController *)controller 
                 polygonLineColorForStatus:(SBSDKDocumentDetectionStatus)status;

/**
 * Optional.
 * Asks the delegate for the fill color of the polygon that surrounds the detected polygon on the screen, depending on
 * the document detection status.
 * @param controller The document scanner controller that called this function.
 * @param status The status of the current document detection.
 * @return The fill color for the displayed polygon.
 */
- (UIColor *)documentScannerViewController:(SBSDKDocumentScannerViewController *)controller 
                 polygonFillColorForStatus:(SBSDKDocumentDetectionStatus)status;

/**
 * Optional.
 * Lets you configure the document detections status label, depending on the document detection status. 
 * You can change the visibility, colors, font and the text of the label here.
 * @param controller The document scanner controller that called this function.
 * @param label The label to be configured.
 * @param result The result of the current document detection.
 */
- (void)documentScannerViewController:(SBSDKDocumentScannerViewController *)controller
        configureStatusDetectionLabel:(SBSDKDetectionStatusLabel *)label
                   forDetectionResult:(SBSDKDocumentDetectorResult *)result;

@end


/**
 * A UIViewController subclass to show a camera screen and run a user guiding document detector.
 * The detection result is visualized using a polygonal bezier path.
 * This class cannot be instanced from a storyboard.
 * Instead it is installing itself as a child view controller onto a given parent view controller.
 * This is a simpler version of 'SBSDKScannerViewController' that is more in-line with other classic UI SDK components.
 * As a subclass of 'SBSDKBaseScannerViewController' it benefits from all its advantages, e.g. zooming, view finder,
 * and energy management.
 */
@interface SBSDKDocumentScannerViewController : SBSDKBaseScannerViewController

/**
* Designated initializer. Installs the receiver as child view controller onto the parent view controllers
* view using its entire bounds area.
* @param parentViewController The view controller in which the newly created instance is embedded into.
* If parentViewController conforms to SBSDKScannerViewControllerDelegate, it is automatically set as delegate.
* @param containerView The view in which the newly created instance is embedded into.
* If nil the parentViewControllers view is used.
* @param delegate The delegate of the receiver.
*/
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView
                                             delegate:(nullable id<SBSDKDocumentScannerViewControllerDelegate>)delegate;

/**
 * The delegate of the receiver.
 */
@property (nonatomic, weak) id<SBSDKDocumentScannerViewControllerDelegate> delegate;

/**
 * The mode of the document detector to be used for document outline detection.
 * The default value can be set via `+ (void)setDefaultDetectorMode:(SBSDKDocumentDetectorMode)newDefaultDetectorMode;`.
 * If not set specifically the default value is `SBSDKDocumentDetectorModeMachineLearning`.
 */
@property (nonatomic, assign) SBSDKDocumentDetectorMode detectorMode;

/** 
 * The preferred aspect ratios for the document detector.
 * If nil or empty, the aspect ratio will not be taken into account when selecting the best document polygon.
 * If set, polygons with an aspect ratio in this list will be selected more preferrably.
 * Defaults to nil.
 */
@property(nonatomic, strong, nullable) NSArray<SBSDKAspectRatio *> *preferredAspectRatios;

/** 
 * The required aspect ratios for the document detector.
 * If nil or empty, the aspect ratio will not be taken into account when detecting documents.
 * Otherwise the detector will only detect documents with one of the given required aspect ratios.
 * Defaults to nil.
 */
@property(nonatomic, strong, nullable) NSArray<SBSDKAspectRatio *> *requiredAspectRatios;

/** 
 * If set to YES, the documents aspect ratio is not compared to the screens aspect ratio, 
 * the bad aspect ratio warning will never appear. Defaults to NO. 
 */
@property (nonatomic, assign) BOOL ignoreBadAspectRatio;

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

/** The auto-snapping mode. Default is SBSDKAutosnappingModeEnabled. */
@property (nonatomic, assign) SBSDKAutosnappingMode autoSnappingMode;

/**
 * The sensitivity of auto-snapping. Values are clamped to the range 0.0 - 1.0.
 * A value of 1.0 triggers automatic snapping immediately, a value of 0.0 delays the automatic by 3 seconds.
 */
@property (nonatomic, assign) CGFloat autoSnappingSensitivity;

/** The default snap button. */
@property (nonatomic, readonly) SBSDKShutterButton *snapButton;

/** 
 * Sets a custom snapping button. If not nil, it replaces the default snapping button. 
 * The setter configures the customs buttons action-target automatically and hides the default snapping button.
 * You are responsible for placing the button in the view hierarchy and layout.
 * If the custom button is of class SBSDKShutterButton, the buttons status will be automatically updated.
 * Setting it to nil, will restore the default snapping button, you are responsible for removing it from the view hierarchy.
 */
@property (nullable, nonatomic, strong) UIButton *customSnapButton;

/** Whether the snap button is hidden or not. Defaults to NO. */
@property (nonatomic, assign) BOOL hideSnapButton;

/** The configuration object for the document detection status text. */
@property (nonatomic, strong) SBSDKDocumentScannerStatusTextConfiguration *statusTextConfiguration;

/** Whether the detection status label is hidden or not. Defaults to NO. */
@property (nonatomic, assign) BOOL hideDetectionStatusLabel;

/** The scaling factor for captured images. Values are clamped to the range 0.0 - 1.0. */
@property (nonatomic, assign) CGFloat imageScale;

/**
 * Limits the maximum size of the document image. If width or height are zero, this property is effectively ignored.
 * Defaults to CGSizeZero.
 */
@property (nonatomic, assign) CGSize documentImageSizeLimit;

/**
 * The filter to be applied to the snapped document image. Defaults to SBSDKImageFilterTypeNone.
 */
@property (nonatomic, assign) SBSDKImageFilterType documentImageFilter;

/** The line width for the polygon displayed around the detected document. */
@property (nonatomic, assign) CGFloat polygonLineWidth;

/**
 * The line color for the polygon displayed over the detected document when the
 * document detection status is SBSDKDocumentDetectionStatusOK.
 */
@property (nonatomic, strong) UIColor *polygonLineColorAccepted;

/**
 * The line color for the polygon displayed over the detected document when the
 * document detection status is not SBSDKDocumentDetectionStatusOK.
 */
@property (nonatomic, strong) UIColor *polygonLineColorRejected;

/**
 * The fill color for the polygon displayed over the detected document when the
 * document detection status is SBSDKDocumentDetectionStatusOK.
 */
@property (nonatomic, strong) UIColor *polygonFillColorAccepted;

/**
 * The fill color for the polygon displayed over the detected document when the
 * document detection status is not SBSDKDocumentDetectionStatusOK.
 */
@property (nonatomic, strong) UIColor *polygonFillColorRejected;

/**
 * Whether the polygon auto snap progress animation is enabled or not. Defaults to YES.
 */
@property (nonatomic, assign) BOOL polygonAutoSnapProgressEnabled;

/**
 * Stroke color of polygon auto snap progress animation. Defaults to blue.
 */
@property (nonatomic, strong) UIColor *polygonAutoSnapProgressColor;

/**
 * Line width of polygon auto snap progress animation. Defaults to 5.0.
 */
@property (nonatomic, assign) CGFloat polygonAutoSnapProgressLineWidth;

/**
 * The radius to use when drawing rounded corners of the polygon. Defaults to 8.0.
 */
@property (nonatomic, assign) CGFloat polygonCornerRadius;

/**
 The font size of the user guidance label. Defaults to 17.
 */
@property (nonatomic, assign) CGFloat detectionStatusFontSize;

@end

NS_ASSUME_NONNULL_END
