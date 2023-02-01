//
//  SBSDKMRZScannerViewController.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 28.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBaseScannerViewController.h"
#import "SBSDKMachineReadableZoneRecognizer.h"
#import "SBSDKMachineReadableZoneRecognizerResult.h"

@class SBSDKMRZScannerViewController;

/**
 * The delegation protocol for the `SBSDKMRZScannerViewController` class.
 */
@protocol SBSDKMRZScannerViewControllerDelegate <NSObject>
/**
 * Informs the delegate that the scanner has detected a machine-readable zone.
 * @param controller The calling SBSDKMRZScannerViewController.
 * @param result The detected machine-readable zone result.
 */
- (void)mrzScannerController:(nonnull SBSDKMRZScannerViewController *)controller
                didDetectMRZ:(nonnull SBSDKMachineReadableZoneRecognizerResult *)result;


@optional
/**
 * Optional.
 * Asks the delegate if the scanner should detect machine-readable zones on the next video frame.
 * @param controller The calling SBSDKMRZScannerViewController.
 * @return Return YES if you want to detect machine-readable zones on the next video frame, NO otherwise.
 */
- (BOOL)mrzScannerControllerShouldDetectMRZ:(nonnull SBSDKMRZScannerViewController *)controller;

@end

NS_ASSUME_NONNULL_BEGIN

/**
 * A camera-enabled UIViewController subclass to scan machine-readable zones.
 * This class cannot be instantiated from a storyboard directly, instead it is installing 
 * itself as a child view controller onto a given parent view controller.
 */
@interface SBSDKMRZScannerViewController : SBSDKBaseScannerViewController

/**
 * The delegate. See SBSDKMRZScannerViewControllerDelegate protocol.
 */
@property (nonatomic, weak, nullable) id<SBSDKMRZScannerViewControllerDelegate> delegate;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * The number of frames to be accumulated results when recognizing machine readable zones. 
 * Lower values are more inaccurate but faster, higher values are more accurate but slower. 
 * Values less than or equal 1 effectively turn accumulation off.
 * The default value is 4.
 */
@property (nonatomic, assign) NSUInteger resultAccumulationCount;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * @param parentView The view the newly created instance is embedded into.
 * If nil the parentViewControllers view is used.
 * @param delegate The delegate of the receiver. If nil and the parentViewController conforms to the 
 * SBSDKMRZScannerViewControllerDelegate protocol, the parentViewController is automatically set as delegate.
 * @return New instance of SBSDKMRZScannerViewController.
 */
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)parentView
                                             delegate:(id<SBSDKMRZScannerViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

