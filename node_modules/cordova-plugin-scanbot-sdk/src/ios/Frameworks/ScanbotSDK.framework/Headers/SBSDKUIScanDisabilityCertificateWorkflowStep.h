//
//  SBSDKUIScanDisabilityCertificateWorkflowStep.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.12.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import "SBSDKUIWorkflowStep.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A 'SBSDKUIWorkflowStep' subclass specialized on recognizing disability certificates (DC) on either high-res
 * still images or low-res video frames (live detection).
 */
__deprecated_msg("Deprecated.")
@interface SBSDKUIScanDisabilityCertificateWorkflowStep : SBSDKUIWorkflowStep

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
 * If set to NO, and no requiredAspectRatios are set, it works as a live video frame detector.
 * @param resultValidationHandler A block to validate the results of the receiver.
 */
- (instancetype)initWithTitle:(NSString *)title
                      message:(NSString *)message
         requiredAspectRatios:(NSArray<SBSDKAspectRatio *> *)requiredAspectRatios
            wantsCapturedPage:(BOOL)wantsCapturedPage
             resultValidation:(SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;

@end

NS_ASSUME_NONNULL_END
