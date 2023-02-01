//
//  SBSDKUILicensePlateScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUICameraViewController.h"
#import "SBSDKUILicensePlateScannerConfiguration.h"
#import "SBSDKLicensePlateScanner.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKUILicensePlateScannerViewController;

/** Delegate protocol for 'SBSDKUILicensePlateScannerViewController'. */
@protocol SBSDKUILicensePlateScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that a license plate has been recognized.
 * @param viewController The license plate scanner view controller instance.
 * @param result The result of the license plate scan.
 */
- (void)licensePlateScanner:(SBSDKUILicensePlateScannerViewController *)controller
   didRecognizeLicensePlate:(SBSDKLicensePlateScannerResult *)result;

@optional

/**
 * Optional: Informs the delegate that the 'SBSDKUILicensePlateScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUILicensePlateScannerViewController' that did dismiss.
 */
- (void)licensePlateScannerDidCancel:(SBSDKUILicensePlateScannerViewController *)controller;

@end

/**
 * A highly customizable camera-based view controller to scan vehicle license plates in realtime.
 * A view finder like rectangle shows the area where the license plate is recognized.
 * Once a license plate has been recognized within the view finder area the result is delivered to the receivers delegate.
 */
@interface SBSDKUILicensePlateScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUILicensePlateScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new license plate scanner view controller.
 * @param delegate The delegate of the new scanner view controller.
 * @return A new instance of 'SBSDKUILicensePlateScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUILicensePlateScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUILicensePlateScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUILicensePlateScannerViewController'.
 * @param configuration The configuration to define look and feel of the new license plate scanner view controller.
 * @param delegate The delegate of the new scanner view controller.
 * @return A new instance of 'SBSDKUILicensePlateScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUILicensePlateScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUILicensePlateScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUILicensePlateScannerViewControllerDelegate> delegate;

/** Enables or disables the recognition if license plates. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;


@end

NS_ASSUME_NONNULL_END
