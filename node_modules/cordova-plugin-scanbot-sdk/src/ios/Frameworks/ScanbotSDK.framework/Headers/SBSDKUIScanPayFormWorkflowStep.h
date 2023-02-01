//
//  SBSDKUIScanPayFormWorkflowStep.h
//  ScanbotSDKBeta
//
//  Created by Sebastian Husche on 14.03.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKUIWorkflowStep.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A `SBSDKUIWorkflowStep` subclass specialized in recognizing payforms in a UIImage or CMSampleBufferRef.
 */
@interface SBSDKUIScanPayFormWorkflowStep : SBSDKUIWorkflowStep

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param title The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param message A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
 * @param wantsCapturedPage Set to YES, if the receiver requires a high-resolution still image shot for its processing.
 * @param resultValidationHandler A block to validate the results of the receiver.
 */
- (instancetype)initWithTitle:(NSString *)title
                      message:(NSString *)message
            wantsCapturedPage:(BOOL)wantsCapturedPage
             resultValidation:(SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;

@end

NS_ASSUME_NONNULL_END
