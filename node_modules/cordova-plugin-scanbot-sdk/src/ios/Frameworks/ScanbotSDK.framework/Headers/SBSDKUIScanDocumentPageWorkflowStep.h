//
//  SBSDKUIScanDocumentPageWorkflowStep.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import "SBSDKUIWorkflowStep.h"

NS_ASSUME_NONNULL_BEGIN

/** A block to post-process an 'SBSDKUIPage'. */
typedef void (^SBSDKUIScanPagePostProcessingHandler)(SBSDKUIPage *);

/** A 'SBSDKUIWorkflowStep' subclass specialized on capturing documents from high-res still images. */
@interface SBSDKUIScanDocumentPageWorkflowStep : SBSDKUIWorkflowStep

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param title The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param message A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param requiredAspectRatios An array of required aspect ratios if this step uses document detection.
 * @param pagePostProcessHandler A block to post-process the scanned page without subclassing.
 * @param resultValidationHandler A block to validate the results of the receiver.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                      message:(nullable NSString *)message
         requiredAspectRatios:(nullable NSArray<SBSDKAspectRatio*>*) requiredAspectRatios
           pagePostProcessing:(nullable SBSDKUIScanPagePostProcessingHandler)pagePostProcessHandler
             resultValidation:(nullable SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;

@end

NS_ASSUME_NONNULL_END
