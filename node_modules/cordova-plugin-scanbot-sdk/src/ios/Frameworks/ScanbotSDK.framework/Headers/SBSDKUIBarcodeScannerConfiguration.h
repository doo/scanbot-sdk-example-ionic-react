//
//  SBSDKUIBarcodeScannerConfiguration.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 3/29/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIBarcodeScannerUIConfiguration.h"
#import "SBSDKUIBarcodeScannerTextConfiguration.h"
#import "SBSDKUIBarcodeScannerBehaviorConfiguration.h"
#import "SBSDKUIBarcodeSelectionOverlayConfiguration.h"

/**
 * This class describes the look and feel, as well as the textual contents of the detection screens for barcodes.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
 */
@interface SBSDKUIBarcodeScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIBarcodeScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the barcode scanner screen.
 * @param behaviorConfiguration A configuration for barcode scanner behavior.
 * @param cameraConfiguration A configuration for the barcode scanners camera.
 * @param selectionOverlayConfiguration A configuration for the barcode scanners selection overlay.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIBarcodeScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIBarcodeScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIBarcodeScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration 
                  selectionOverlayConfiguration:(nonnull SBSDKUIBarcodeSelectionOverlayConfiguration *)selectionOverlayConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIBarcodeScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIBarcodeScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodeScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodeScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodeScannerBehaviorConfiguration *behaviorConfiguration;

/** The configuration for barcode overlays. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIBarcodeSelectionOverlayConfiguration *selectionOverlayConfiguration;

@end
