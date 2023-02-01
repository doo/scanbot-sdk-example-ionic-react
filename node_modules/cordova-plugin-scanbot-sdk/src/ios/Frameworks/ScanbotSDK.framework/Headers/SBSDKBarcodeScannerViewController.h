//
//  SBSDKBarcodeScannerViewController.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 29.11.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBaseScannerViewController.h"
#import "SBSDKBarcodeScanner.h"
#import "SBSDKBarcodeImageGenerationType.h"
#import "SBSDKBarcodeAdditionalParameters.h"

@class SBSDKBarcodeScannerViewController;
/**
 * A delegate protocol to customize the behavior, look and feel of the SBSDKBarcodeScannerViewControllerDelegate.
 */
@protocol SBSDKBarcodeScannerViewControllerDelegate <NSObject>
@optional
/**
 * Asks the delegate if the receiver should detect barcodes on the next video frame.
 * Optional.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @return YES, if barcodes should be detected on the next video frame. No otherwise.
 */
- (BOOL)barcodeScannerControllerShouldDetectBarcodes:(nonnull SBSDKBarcodeScannerViewController *)controller;

/**
 * Asks the delegate to filter the detected barcodes.
 * Optional.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @param codes Array of SBSDKBarcodeScannerResult containing the detected barcodes.
 * @return The filtered array of barcodes to be delivered to the post-processing.
 */
- (nonnull NSArray<SBSDKBarcodeScannerResult *> *)barcodeScanner:(nonnull SBSDKBarcodeScannerViewController *)controller 
                                                   filterResults:(nonnull NSArray<SBSDKBarcodeScannerResult *> *)codes;

/**
 * Asks the delegate whether to highlight a barcode on the selection overlay or not.
 * Only called only when the selection overlay is enabled.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @param code The barcode scanner result that may be highlighted or not.
 * @return YES, if the provided barcode result should be highlighted on the selection overlay. NO otherwise.
 */
- (BOOL)barcodeScanner:(nonnull SBSDKBarcodeScannerViewController *)controller 
 shouldHighlightResult:(nonnull SBSDKBarcodeScannerResult *)code;

/**
 * Asks the delegate for the string to be displayed for the given barcode result on the selection overlay.
 * Only called only when the selection overlay is enabled.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @param code The barcode scanner result the returned text will be displayed for.
 * @return A string to be displayed on the selection overlay for the given barcode result. If you return nil, the
 * default string is used (barcode content and type).
 */
- (nullable NSString *)barcodeScanner:(nonnull SBSDKBarcodeScannerViewController *)controller
              selectionOverlayTextFor:(nonnull SBSDKBarcodeScannerResult *)code;

/**
 * Informs the delegate that the receiver has detected some barcodes.
 * Optional.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @param codes Array of SBSDKBarcodeScannerResult containing the detected barcodes.
 * @param image The image the barcodes have been detected on. The image is cropped to the visible area on the screen 
 * and to the view finder rectangle, if a view finder is enabled. 
 */
- (void)barcodeScannerController:(nonnull SBSDKBarcodeScannerViewController *)controller
               didDetectBarcodes:(nonnull NSArray<SBSDKBarcodeScannerResult *> *)codes
                         onImage:(nonnull UIImage *)image;


/**
 * Returns captured barcode image. Will fire only if `barcodeImageGenerationType` parameter is not `SBSDKBarcodeImageGenerationTypeNone`.
 * Optional.
 * @param controller The calling SBSDKBarcodeScannerViewController.
 * @param barcodeImage A captured device-orientation-corrected barcode image.
 */
- (void)barcodeScannerController:(nonnull SBSDKBarcodeScannerViewController *)controller
          didCaptureBarcodeImage:(nonnull UIImage *)barcodeImage;

@end

NS_ASSUME_NONNULL_BEGIN


/**
 * A UIViewController subclass to show a camera screen with the barcode detector.
 * This class cannot be instanced from a storyboard.
 * Instead it is installing itself as a child view controller onto a given parent view controller.
 */
@interface SBSDKBarcodeScannerViewController : SBSDKBaseScannerViewController
/**
 * The delegate. See SBSDKBarcodeScannerViewControllerDelegate protocol. Weak.
 */
@property (nonatomic, weak, nullable) id<SBSDKBarcodeScannerViewControllerDelegate> delegate;

/**
 * Machine code types (EAN, DataMatrix, Aztec, QR, etc) that can be returned in `didDetectBarcodes`
 * delegate method. When nil or empty - all codes can be returned.
 * Default is nil.
 */
@property (nonatomic, strong, nullable) NSArray<SBSDKBarcodeType *> *acceptedBarcodeTypes;

/**
 * Additional parameters for tweaking the detection of barcodes.
 */
@property (nonatomic, strong, nonnull) SBSDKBarcodeAdditionalParameters *additionalDetectionParameters;

/**
 * Bar code document types to limit detection results to. When nil or empty - all document can be returned.
 * Default is nil.
 */
@property (nonatomic, strong, nullable) NSArray<SBSDKBarcodeDocumentType *> *acceptedDocumentTypes;

/**
 * The barcode detectors engine mode.
 * The default value is SBSDKBarcodeEngineModeNextGen.
 */
@property (nonatomic, assign) SBSDKBarcodeEngineMode engineMode;

/**
 Specifies the way of barcode images generation or disables this generation at all.
 Use, if you want to receive a full sized image with barcodes.
 Defaults to SBSDKBarcodeImageGenerationTypeNone.
 */
@property (nonatomic, assign) SBSDKBarcodeImageGenerationType barcodeImageGenerationType;

/**
 * Displays an augmented reality view that draws the frames, content and type text of the found barcodes when it finds them. 
 * Defaults to NO.
 */
@property (nonatomic, assign) BOOL selectionOverlayEnabled;

/**
 * The color for the overlays polygons around the barcodes. The default color is a blueish green.
 */
@property (nonatomic, strong) UIColor *selectionPolygonColor;

/**
 * The color for the overlays polygons around the barcodes when highlighted. The default color is a blueish green.
 */
@property (nonatomic, strong) UIColor *selectionHighlightedPolygonColor;

/**
 * The text color for the selection overlay. The default color is black.
 */
@property (nonatomic, strong) UIColor *selectionTextColor;

/**
 * The text color for the selection overlay when highlighted. The default color is white.
 */
@property (nonatomic, strong) UIColor *selectionHighlightedTextColor;

/**
 * The background color for the selection overlay text. The default color is red.
 */
@property (nonatomic, strong) UIColor *selectionTextContainerColor;

/**
 * The background color for the selection overlay text when highlighted. The default color is red.
 */
@property (nonatomic, strong) UIColor *selectionHighlightedTextContainerColor;


/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * If parentViewController conforms to SBSDKBarcodeScannerViewControllerDelegate, it is automatically set as delegate.
 */
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * @param delegate The delegate for the receiver.
 * If parentViewController conforms to SBSDKBarcodeScannerViewControllerDelegate, it is automatically set as delegate.
 */
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView
                                             delegate:(nullable id<SBSDKBarcodeScannerViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
