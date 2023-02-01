//
//  SBSDKUIBarcodesBatchScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 12.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIBarcodesBatchScannerUIConfiguration.h"
#import "SBSDKUIBarcodesBatchScannerTextConfiguration.h"
#import "SBSDKUIBarcodesBatchScannerBehaviorConfiguration.h"
#import "SBSDKUIBarcodeSelectionOverlayConfiguration.h"

/**
* This class describes the look and feel, as well as the textual contents of the detection screens for barcodes.
* Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
*/
@interface SBSDKUIBarcodesBatchScannerConfiguration : SBSDKUIConfiguration
/**
 * Designated initializer. Creates a new instance of 'SBSDKUIBarcodesBatchScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the barcode scanners behavior.
 * @param cameraConfiguration A configuration for the barcode scanners camera.
 * @param selectionOverlayConfiguration A configuration for the barcode scanners selection overlay.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIBarcodesBatchScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIBarcodesBatchScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIBarcodesBatchScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration
                  selectionOverlayConfiguration:(nonnull SBSDKUIBarcodeSelectionOverlayConfiguration *)selectionOverlayConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIBarcodesBatchScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIBarcodesBatchScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodesBatchScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodesBatchScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodesBatchScannerBehaviorConfiguration *behaviorConfiguration;

/** The configuration for barcode overlays. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodeSelectionOverlayConfiguration *selectionOverlayConfiguration;

@end

