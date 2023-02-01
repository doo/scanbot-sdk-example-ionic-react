//
//  SBSDKHealthInsuranceCardScannerViewController.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 11.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import "SBSDKBaseScannerViewController.h"
#import "SBSDKHealthInsuranceCardRecognizer.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKHealthInsuranceCardScannerViewController;

/**
 * The delegation protocol for the `SBSDKHealthInsuranceCardScannerViewController` class.
 */
@protocol SBSDKHealthInsuranceCardScannerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that a health insurance card has been scanned.
 * @param controller The SBSDKHealthInsuranceCardScannerViewController instance that scanned the health insurance card.
 * @param card The result of the scan.
 */
- (void)healthInsuranceCardScannerViewController:(SBSDKHealthInsuranceCardScannerViewController *)viewController
                      didScanHealthInsuranceCard:(SBSDKHealthInsuranceCardRecognitionResult *)card;
@end

/**
 * A UIViewController subclass to scan health insurance cards with the camera.
 */
@interface SBSDKHealthInsuranceCardScannerViewController : SBSDKBaseScannerViewController
/**
 * The delegate. See SBSDKHealthInsuranceCardScannerViewController protocol. Weak.
 */
@property(nonatomic, weak) id<SBSDKHealthInsuranceCardScannerViewControllerDelegate>delegate;

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
 * @return New instance of SBSDKHealthInsuranceCardScannerViewController.
*/
- (nullable instancetype)initWithParentViewController:(nullable UIViewController *)parentViewController
                                           parentView:(nullable UIView *)parentView
                                             delegate:(id<SBSDKHealthInsuranceCardScannerViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

