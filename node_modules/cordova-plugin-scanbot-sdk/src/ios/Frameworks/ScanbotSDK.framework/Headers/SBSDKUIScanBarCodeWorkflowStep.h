//
//  SBSDKUIScanBarCodeWorkflowStep.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.12.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import "SBSDKUIWorkflowStep.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A 'SBSDKUIWorkflowStep' subclass specialized on recognizing barcodes/QR codes on low-res video frames (live detection).
 */

@interface SBSDKUIScanBarCodeWorkflowStep : SBSDKUIWorkflowStep

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param title The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param message A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param acceptedMachineCodeTypes An array of accepted machine code types.
 * @param finderViewAspectRatio The aspect ratio of finder view area. Sets `SBSDKScannerViewController.capturingFrameAspectRatio`.
 * The barcodes that are in finder view will be scanned. Pass zero aspect ratio or nil to disable finder view.
 * @param resultValidationHandler A block to validate the results of the receiver.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                      message:(nullable NSString *)message
            acceptedCodeTypes:(nullable NSArray<SBSDKBarcodeType *>*)acceptedMachineCodeTypes
        finderViewAspectRatio:(nullable SBSDKAspectRatio *)finderViewAspectRatio
             resultValidation:(nullable SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;

@end

NS_ASSUME_NONNULL_END
