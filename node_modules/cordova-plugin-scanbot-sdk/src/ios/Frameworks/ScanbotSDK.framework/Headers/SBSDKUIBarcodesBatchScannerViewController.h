//
//  SBSDKUIBarcodesBatchScannerViewController.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 12.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIBarcodesBatchScannerConfiguration.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKBarcodeScanner.h"
#import "SBSDKUIBarcodesBatchScannerViewControllerDelegate.h"
#import "SBSDKUIBarcodesBatchScannerMapping.h"
#import "SBSDKUIBarcodeMappedResult.h"

/**
* A highly customizable camera-based view controller to detect barcodes batches.
*/
@interface SBSDKUIBarcodesBatchScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIBarcodesBatchScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIBarcodesBatchScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUIBarcodesBatchScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIBarcodesBatchScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIBarcodesBatchScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIBarcodesBatchScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIBarcodesBatchScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIBarcodesBatchScannerViewControllerDelegate>)delegate;


/** Enables or disables the barcode detection. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIBarcodesBatchScannerViewControllerDelegate> delegate;

/**
 * The mapper object, that conforms to the `SBSDKUIBarcodesBatchScannerMapping` protocol. Used to get additional info for barcodes.
 * Does not hold strong reference to the object. Can be nil.
 */
@property (nullable, nonatomic, weak) id <SBSDKUIBarcodesBatchScannerMapping> dataMapper;

/**
 * Freezes the cameras preview layer by stopping the camera session.
 */
- (void)freezeCamera;

/**
 * Unfreezes the previously frozen cameras preview layer by restarting the camera session.
 */
- (void)unfreezeCamera;

@end
