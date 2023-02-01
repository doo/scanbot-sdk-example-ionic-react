//
//  SBSDKUIWorkflowStep.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SBSDKUIPage.h"
#import "SBSDKUIWorkflowStepResult.h"
#import "SBSDKScannerViewController.h"
#import "SBSDKAspectRatio.h"
#import "SBSDKBarcodeType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A block to validate the result of a workflow step. Return an error if your validation fails, otherwise return nil.
 */
typedef NSError* _Nullable (^SBSDKUIWorkflowStepValidationHandler)(SBSDKUIWorkflowStepResult *);


/**
 * A class describing one single step of a workflow. There are some pre-defined workflow steps but you also may
 * may subclass and create your own custom steps.
 */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowStep : NSObject

/** The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver. */
@property(nullable, nonatomic, readonly) NSString* title;

/** A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver. */
@property(nullable, nonatomic, readonly) NSString* message;

/**
 * A block to validate the results of the receiver.
 * In this block you validate the processing results of the receiver and return an error if the validation fails.
 * In case you return an error the step is repeated, otherwise (return nil) the workflow is being continued.
 * If set to nil, no validation is performed and the step is treated as being successful.
 */
@property(nullable, nonatomic, readonly) SBSDKUIWorkflowStepValidationHandler resultValidationHandler;

/** An array of required aspect ratios if this step uses document detection. */
@property(nullable, nonatomic, readonly) NSArray<SBSDKAspectRatio *>* requiredAspectRatios;

/** An array of accepted machine code types if this step QR- or barcode detection. */
@property(nullable, nonatomic, readonly) NSArray<SBSDKBarcodeType *>* acceptedMachineCodeTypes;

/** Set to YES, if the receiver requires a high-resolution still image shot for its processing. */
@property(nonatomic, readonly) BOOL wantsCapturedPage;

/** Set to YES, if the receiver requires a low-resolution video frame image for its processing. */
@property(nonatomic, readonly) BOOL wantsVideoFramePage;

/** Set to YES, if the receiver requires the detection of machine readable codes (QR, barcodes) for its processing. */
@property(nonatomic, readonly) BOOL wantsMachineReadableCodes;

/** If set to YES, step validation errors will be displayed as the message. Defaults to NO. */
@property(nonatomic, readonly) BOOL runsContinuousValidation;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param title The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param message A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param requiredAspectRatios An array of required aspect ratios if this step uses document detection.
 * @param wantsCapturedPage Set to YES, if the receiver requires a high-resolution still image shot for its processing.
 * @param wantsVideoFramePage Set to YES, if the receiver requires a low-resolution video frame image for its processing.
 * @param acceptedMachineReadableCodes An array of accepted machine code types if this step QR- or barcode detection.
 * @param resultValidationHandler A block to validate the results of the receiver.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                      message:(nullable NSString *)message
         requiredAspectRatios:(nullable NSArray<SBSDKAspectRatio*>*) requiredAspectRatios
            wantsCapturedPage:(BOOL)wantsCapturedPage
          wantsVideoFramePage:(BOOL)wantsVideoFramePage
acceptedMachineReadableCodeTypes:(nullable NSArray<SBSDKBarcodeType *>*)acceptedMachineReadableCodes
             resultValidation:(nullable SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;


/**
 * Subclasses may override this function to do additional configuration of the 'SBSDKScannerViewController'
 * when this step will be executed.
 * Caution: Changes made here are not automatically restored. You are responsible to revert changes made
 * here for other steps.
 */
- (void)configureScannerViewController:(SBSDKScannerViewController *)scanner;

/**
 * Subclasses may override this function to post-process the result, e.g. change filter of captured image,
 * run additional detectors etc.
 */
- (void)processResult:(SBSDKUIWorkflowStepResult *)result;

@end

NS_ASSUME_NONNULL_END
