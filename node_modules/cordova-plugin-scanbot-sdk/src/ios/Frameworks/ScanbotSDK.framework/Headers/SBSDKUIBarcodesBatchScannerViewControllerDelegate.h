//
//  SBSDKUIBarcodesBatchScannerViewControllerDelegate.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 09.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SBSDKUIBarcodesBatchScannerViewController;
@class SBSDKUIBarcodeMappedResult;

/** Delegate protocol for 'SBSDKUIBarcodesBatchScannerViewController'. */
@protocol SBSDKUIBarcodesBatchScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that one or more barcodes have been detected and the view controller has dismissed.
 * @param viewController The detection view controller that detected barcode(s).
 * @param barcodeResults An array of SBSDKBarcodeScannerResult objects containing detected barcodes.
 *
 */
- (void)barcodesBatchScannerViewController:(nonnull SBSDKUIBarcodesBatchScannerViewController *)viewController
                      didFinishWithResults:(nonnull NSArray<SBSDKUIBarcodeMappedResult *> *)barcodeResults;

@optional

/**
 * Optional: informs the delegate that the 'SBSDKUIBarcodesBatchScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUIBarcodesBatchScannerViewController' that did dismiss.
 */
- (void)barcodesBatchScannerViewControllerDidCancel:(nonnull SBSDKUIBarcodesBatchScannerViewController *)viewController;

@end
