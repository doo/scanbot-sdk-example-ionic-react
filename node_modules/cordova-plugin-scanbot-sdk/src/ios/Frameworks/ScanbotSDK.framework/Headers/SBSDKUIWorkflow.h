//
//  SBSDKUIWorkflow.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 16.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIWorkflowStep.h"
#import "SBSDKUIScanDocumentPageWorkflowStep.h"
#import "SBSDKUIScanMachineReadableZoneWorkflowStep.h"
#import "SBSDKUIScanDisabilityCertificateWorkflowStep.h"
#import "SBSDKUIScanHealthInsuranceCardWorkflowStep.h"
#import "SBSDKUIScanBarCodeWorkflowStep.h"
#import "SBSDKUIScanPayFormWorkflowStep.h"
#import "SBSDKUIWorkflowStepResult.h"

NS_ASSUME_NONNULL_BEGIN

/** A block type to validate the results of all steps in a workflow. */
typedef NSError* _Nullable (^SBSDKUIWorkflowValidationHandler)(NSArray<SBSDKUIWorkflowStepResult *>*);

/**
 * Represents a scanning workflow, consisting of multiple steps, each of it performing an image scan.
 * You can combine document scanning with QR code detection or machine readable zone recognition.
 * Many steps can be run on a captured still image or a video frame, so a step can either be a live-detection or
 * a still-image capturing step.
 * In the end, when all steps have finished you can validate all step results in a single block, and restart
 * the whole workflow if the validation fails.
 * By subclassing 'SBSDKUIWorkflowStep' the creation of custom steps is possible.
 */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflow: NSObject

/** The array of steps to execute. */
@property(nonnull, nonatomic, readonly) NSArray<SBSDKUIWorkflowStep *>* steps;

/**
 * The workflow validation handler. Return an error if you want to fail the workflow validation.
 * Return nil to finish the workflow.
 */
@property(nullable, nonatomic, readonly) SBSDKUIWorkflowValidationHandler workflowValidationHandler;

/** The name of the workflow for identification purposes. */
@property(nullable, nonatomic, readonly) NSString *name;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param steps The array of steps the workflow consists of.
 * @param name The name of the workflow for identification.
 * @param validationHandler The workflow validation block.
 */
- (nullable instancetype)initWithSteps:(nonnull NSArray<SBSDKUIWorkflowStep *>*)steps
                                  name:(nullable NSString *)name
                     validationHandler:(nullable SBSDKUIWorkflowValidationHandler)validationHandler;

@end

NS_ASSUME_NONNULL_END
