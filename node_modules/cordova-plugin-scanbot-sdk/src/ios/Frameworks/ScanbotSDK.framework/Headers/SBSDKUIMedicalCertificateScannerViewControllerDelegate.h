//
//  SBSDKUIMedicalCertificateScannerViewControllerDelegate.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.01.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKMedicalCertificateScannerViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKUIMedicalCertificateScannerViewController;

/**
 * The delegation protocol for `SBSDKUIMedicalCertificateScannerViewController`.
 */
@protocol SBSDKUIMedicalCertificateScannerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that the `SBSDKUIMedicalCertificateScannerViewController` has finished with a valid result.
 * @param viewController The medical certificate scanner viewcontroller that finished scanning.
 * @param result The successfully scanned medical certificate.
 */
- (void)medicalScannerViewController:(SBSDKUIMedicalCertificateScannerViewController *)viewController
                 didFinishWithResult:(SBSDKMedicalCertificateRecognizerResult *)result;

/**
 * Informs the delegate that the `SBSDKUIMedicalCertificateScannerViewController` has been cancelled.
 * @param viewController The medical certificate scanner viewcontroller that cancelled scanning.
 */
- (void)medicalScannerViewControllerDidCancel:(SBSDKUIMedicalCertificateScannerViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
