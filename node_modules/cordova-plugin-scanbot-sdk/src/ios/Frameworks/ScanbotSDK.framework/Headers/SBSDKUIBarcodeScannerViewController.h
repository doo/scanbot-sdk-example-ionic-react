//
//  SBSDKUIBarcodeScannerViewController.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 3/28/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIBarcodeScannerConfiguration.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKBarcodeScanner.h"

@class SBSDKUIBarcodeScannerViewController;

/** Delegate protocol for 'SBSDKUIBarcodeScannerViewController'. */
@protocol SBSDKUIBarcodeScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

@optional


/**
 * Informs the delegate that one or more barcodes have been detected.
 * @param viewController The detection view controller that detected barcode(s).
 * @param barcodeResults An array of SBSDKBarcodeScannerResult objects containing recently detected barcodes.
 *
 * Implementing this delegate function will use the new Scanbot barcode detector: see 'SBSDKBarcodeType'.
 */
- (void)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                        didDetectResults:(nonnull NSArray<SBSDKBarcodeScannerResult *> *)barcodeResults;

/**
 * Informs the delegate about capturing barcode image. Fires only if `barcodeImageGenerationType` behavior parameter is not SBSDKBarcodeImageGenerationTypeNone
 * @param viewController The detection view controller that detected barcode(s).
 * @param barcodeImage A device-orientation-corrected barcode image.
 * @param imageURL URL, where frameImage is saved. Stored in default storage of SBSDKUIBarcodeImageStorage.
 *
 * Implementing this delegate function will use the new Scanbot barcode detector: see 'SBSDKBarcodeType'.
 */
- (void)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                  didCaptureBarcodeImage:(nullable UIImage *)barcodeImage
                                imageURL:(nullable NSURL *)imageURL;

/**
 * Asks the delegate whether to highlight a barcode on the selection overlay or not.
 * Only called only when the selection overlay is enabled.
 * @param viewController The calling SBSDKUIBarcodeScannerViewController.
 * @param code The barcode scanner result that may be highlighted or not.
 * @return YES, if the provided barcode result should be highlighted on the selection overlay. NO otherwise.
 */
- (BOOL)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                   shouldHighlightResult:(nonnull SBSDKBarcodeScannerResult *)code;

/**
 * Asks the delegate for the string to be displayed for the given barcode result on the selection overlay.
 * Only called only when the selection overlay is enabled.
 * @param viewController The calling SBSDKUIBarcodeScannerViewController.
 * @param code The barcode scanner result the returned text will be displayed for.
 * @return A string to be displayed on the selection overlay for the given barcode result. If you return nil, the
 * default string is used (barcode content and type).
 */
- (nullable NSString *)qrBarcodeDetectionViewController:(nonnull SBSDKUIBarcodeScannerViewController *)viewController
                                selectionOverlayTextFor:(nonnull SBSDKBarcodeScannerResult *)code;

/**
 * Optional: informs the delegate that the 'SBSDKUIBarcodeScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUIBarcodeScannerViewController' that did dismiss.
 */
- (void)qrBarcodeDetectionViewControllerDidCancel:(nonnull SBSDKUIBarcodeScannerViewController *)viewController;

/**
 * Optional: informs the delegate that the 'SBSDKUIBarcodeScannerViewController' has been cancelled and dismissed by timeout.
 * @param viewController The 'SBSDKUIBarcodeScannerViewController' that did dismiss.
 * Note: If this method is not implemented, viewController will try to
 * call `-(void)qrBarcodeDetectionViewControllerDidCancel:(nonnull SBSDKUIBarcodeScannerViewController *)viewController`
 */
- (void)qrBarcodeDetectionViewControllerDidTimeout:(nonnull SBSDKUIBarcodeScannerViewController *)viewController;

@end

/**
 * A highly customizable camera-based view controller to detect QR and bar codes.
 */
@interface SBSDKUIBarcodeScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIBarcodeScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIBarcodeScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUIBarcodeScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIBarcodeScannerViewControllerDelegate>)delegate;


/**
 * Creates a new instance of 'SBSDKUIBarcodeScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIBarcodeScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIBarcodeScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIBarcodeScannerViewControllerDelegate>)delegate;

/** Enables or disables the QR/bar code detection. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIBarcodeScannerViewControllerDelegate> delegate;

/**
 * Freezes the cameras preview layer by stopping the camera session.
 */
- (void)freezeCamera;

/**
 * Unfreezes the previously frozen cameras preview layer by restarting the camera session.
 */
- (void)unfreezeCamera;

@end

