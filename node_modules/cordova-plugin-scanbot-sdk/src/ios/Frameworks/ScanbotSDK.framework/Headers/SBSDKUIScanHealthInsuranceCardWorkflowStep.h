//
//  SBSDKUIScanHealthInsuranceCardWorkflowStep.h
//  ScanbotSDKBundle
//
//  Created by Danil Voitenko on 22.11.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKUIWorkflowStep.h"

NS_ASSUME_NONNULL_BEGIN

/**
* A 'SBSDKUIScanHealthInsuranceCardWorkflowStep' subclass specialized on recognizing health insurance card
* on low-res video frames (live detection).
*/
@interface SBSDKUIScanHealthInsuranceCardWorkflowStep : SBSDKUIWorkflowStep

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
* Designated initializer.
* @param title The title being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
* @param message A message being displayed in the 'SBSDKUIWorkflowScannerViewController' while it processes the receiver.
* @param requiredAspectRatios An array of required aspect ratios if this step uses document detection.
* @param resultValidationHandler A block to validate the results of the receiver.
*/
- (instancetype)initWithTitle:(nullable NSString *)title
                      message:(nullable NSString *)message
         requiredAspectRatios:(NSArray<SBSDKAspectRatio *> *)requiredAspectRatios
             resultValidation:(nullable SBSDKUIWorkflowStepValidationHandler)resultValidationHandler;

/**
 * Set to yes if the images to recognize on are consecutive video frames, set to NO if you want to recognize on a single
 * image. Defaults to YES.
 */
@property (nonatomic, assign) BOOL useLiveRecognition;

@end

NS_ASSUME_NONNULL_END
