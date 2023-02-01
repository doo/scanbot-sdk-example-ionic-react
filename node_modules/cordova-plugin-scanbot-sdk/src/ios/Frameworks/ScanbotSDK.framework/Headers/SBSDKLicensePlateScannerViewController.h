//
//  SBSDKLicensePlateScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 01.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKLicensePlateScanner.h"
#import "SBSDKBaseScannerViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKLicensePlateScannerViewController;

/** The delegate protocol for the SBSDKLicensePlateScannerViewController. */
@protocol SBSDKLicensePlateScannerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that a license plate has been recognized successfully.
 * @param controller The SBSDKLicensePlateScannerViewController instance that detected/recognized the license plate.
 * @param licensePlateResult The result of the detection or recognition.
 * @param image The original image where the ID card has been detected on.
 */
- (void)licensePlateScannerViewController:(SBSDKLicensePlateScannerViewController *)controller
                 didRecognizeLicensePlate:(SBSDKLicensePlateScannerResult *)licensePlateResult
                                  onImage:(UIImage *)image;

@optional

/**
 * Asks the delegate whether the next video frame should be scanned or not. Optional.
 * Use to skip frames or pause scanning for a while.
 * @param controller The SBSDKLicensePlateScannerViewController that wants to scan the video frame.
 * @return YES, if you want to scan the next video frame, NO otherwise.
 */
- (BOOL)licensePlateScannerViewControllerShouldRecognize:(SBSDKLicensePlateScannerViewController *)controller;

@end

/**
 * A UIViewController subclass to scan for license plates with the camera.
 */
@interface SBSDKLicensePlateScannerViewController : SBSDKBaseScannerViewController

/** The receivers configuration. */
@property (nonatomic, strong) SBSDKLicensePlateScannerConfiguration *configuration;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * If parentViewController conforms to SBSDKLicensePlateScannerViewControllerDelegate, it is automatically set as delegate.
 * @param parentView The view the newly created instance is embedded into.
 * If nil the parentViewControllers view is used.
 * @param delegate The delegate of the receiver.
 * @param configuration The configuration of the receiver. If nil, the default configuration is used.
 * @return New instance of SBSDKLicensePlateScannerViewController.
*/
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)parentView
                                             delegate:(id<SBSDKLicensePlateScannerViewControllerDelegate>)delegate
                                        configuration:(nullable SBSDKLicensePlateScannerConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
