//
//  SBSDKGenericTextLineRecognizerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 26.08.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import "SBSDKGenericTextLineRecognizer.h"
#import "SBSDKBaseScannerViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKGenericTextLineRecognizerViewController;


/**
 * The delegation protocol for 'SBSDKGenericTextLineRecognizerViewController'.
 */
@protocol SBSDKGenericTextLineRecognizerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that text line(s) has been recognized and validated and passes the result.
 * @param controller The SBSDKGenericTextLineRecognizerViewController that has recognized and validated the text line(s).
 * @param result The result of the recognition.
 */
- (void)textLineRecognizerViewController:(SBSDKGenericTextLineRecognizerViewController *)controller
                       didValidateResult:(SBSDKGenericTextLineRecognizerResult *)result;

@optional

/**
 * Asks the delegate whether the next video frame should be recognized or not. Optional.
 * Use to skip frames or pause recognition for a while.
 * @param controller The SBSDKGenericTextLineRecognizerViewController that wants to recognize the video frame.
 * @return YES, if you want to recognize the next video frame, NO otherwise.
 */
- (BOOL)textLineRecognizerViewControllerShouldRecognize:(SBSDKGenericTextLineRecognizerViewController *)controller;

@end


/**
 * A UIViewController subclass to show a camera screen with the text line recognizer.
 * A view finder like rectangle shows the area where text is recognized. The camera can be zoomed in and out using an action
 * or a double-tap to make aiming at the desired area easier.
 * Once some text is recognized within the view finder area, the result is delivered to the receivers delegate.
 * A customizable validation routine checks validates the result and sets a flag in the result.
 */
@interface SBSDKGenericTextLineRecognizerViewController : SBSDKBaseScannerViewController

/** The receivers configuration object. */
@property(nonatomic, strong) SBSDKGenericTextLineRecognizerConfiguration *configuration;

/** The receivers delegate object. It is captured as a weak property. */
@property(nullable, nonatomic, weak) id<SBSDKGenericTextLineRecognizerViewControllerDelegate> delegate;

/**
 * If word boxes should be shown. Default is YES.
 */
@property (nonatomic, assign) BOOL shouldShowWordBoxes;

/**
 * The color of word boxes filling. It is better to use colors with alpha < 0.5.
 */
@property (nonatomic, strong, nonnull) UIColor *wordBoxesFillColor;

/**
 * The color of word boxes border lines.
 */
@property (nonatomic, strong, nonnull) UIColor *wordBoxesLineColor;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Creates a new instance of SBSDKGenericTextLineRecognizerViewController and
 * embeds it into an existing viewcontroller/view hierarchy if needed.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * @param containerView The view the newly created instance is embedded into. If nil the parentViewControllers view is used.
 * @param configuration The configuration object to configure the receiver. If nil, the default configuration is used.
 * @param delegate The delegate of the receiver.
 */
- (nullable instancetype)initWithParentViewController:(nullable UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView
                                        configuration:(nullable SBSDKGenericTextLineRecognizerConfiguration *)configuration
                                             delegate:(id<SBSDKGenericTextLineRecognizerViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
