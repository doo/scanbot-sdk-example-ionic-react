//
//  SBSDKUIWorkflowScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 13.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUICameraViewController.h"
#import "SBSDKUIWorkflowScannerConfiguration.h"
#import "SBSDKUIWorkflow.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKUIWorkflowScannerViewController;

/** Datasource protocol 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@protocol SBSDKUIWorkflowScannerViewControllerDatasource

/**
 * Asks the datasource for the next step of a dynamic workflow.
 * @param step The previously finished workflow step.
 * @param results The current step results of the workflow.
 * @return The next step to execute, or nil if the workflow should finish.
 */
- (nullable SBSDKUIWorkflowStep *)nextStepAfterFinishingStep:(SBSDKUIWorkflowStep *)step
                                                 withResults:(NSArray<SBSDKUIWorkflowStepResult *>*)results;

@end


/** Delegate protocol for 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@protocol SBSDKUIWorkflowScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that the workflow has finished.
 * @param viewController The workflow scanner view controller that processes the workflow.
 * @param workflow The workflow that finished.
 * @param results The array of workflow step results.
 */
- (void)workflowScanViewController:(nonnull SBSDKUIWorkflowScannerViewController *)viewController
                 didFinishWorkflow:(nonnull SBSDKUIWorkflow *)workflow
                       withResults:(nonnull NSArray<SBSDKUIWorkflowStepResult*>*)results;

@optional

/**
 * Informs the delegate that the workflow has been cancelled.
 * @param viewController The workflow scanner view controller that processes the workflow.
 */
- (void)workflowScanViewControllerDidCancel:(nonnull SBSDKUIWorkflowScannerViewController *)viewController;

/**
 * Informs the delegate that the workflow has finished.
 * @param viewController The workflow scanner view controller that processes the workflow.
 */
- (void)workflowScanViewControllerDidFinish:(nonnull SBSDKUIWorkflowScannerViewController *)viewController;

/**
 * Informs the delegate that the workflow has finished a workflow step.
 * @param viewController The workflow scanner view controller that processes the workflow.
 * @param step The workflow step that just finished.
 * @param result The result of the step.
 */
- (void)workflowScanViewController:(nonnull SBSDKUIWorkflowScannerViewController *)viewController
                     didFinishStep:(nonnull SBSDKUIWorkflowStep *)step
                        withResult:(nonnull SBSDKUIWorkflowStepResult *)result;

/**
 * Informs the delegate that the workflow has failed the validation of a single workflow step.
 * @param viewController The workflow scanner view controller that processes the workflow.
 * @param step The workflow step that just failed validation.
 * @param result The result of the step.
 */
- (void)workflowScanViewController:(nonnull SBSDKUIWorkflowScannerViewController *)viewController
             didFailStepValidation:(nonnull SBSDKUIWorkflowStep *)step
                        withResult:(nonnull SBSDKUIWorkflowStepResult *)result;

/**
 * Informs the delegate that the workflow has failed the validation.
 * @param viewController The workflow scanner view controller that processes the workflow.
 * @param workflow The workflow that just failed its validation.
 * @param results The results of all steps.
 * @param error The error of the workflow validation.
 */
- (void)workflowScanViewController:(nonnull SBSDKUIWorkflowScannerViewController *)viewController
         didFailWorkflowValidation:(nonnull SBSDKUIWorkflow *)workflow
                       withResults:(nonnull NSArray<SBSDKUIWorkflowStepResult *>*)results
                   validationError:(NSError *)error;

@end

/**
 * A View controller that processes a workflow.
 */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowScannerViewController: SBSDKUICameraViewController

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Initializes a static workflow.
 * @param workflow The static workflow that should be processed.
 * @param configuration The configuration object.
 * @param delegate The delegate.
 */
+ (nullable instancetype)createNewWithWorkflow:(nonnull SBSDKUIWorkflow *)workflow
                                 configuration:(nonnull SBSDKUIWorkflowScannerConfiguration *)configuration
                                      delegate:(nullable id<SBSDKUIWorkflowScannerViewControllerDelegate>)delegate;

/**
 * Initializes and presents a workflow scanner view controller with a static workflow.
 * @param presenter The view controller that should present the workflow scanner view controller.
 * @param workflow The static workflow that should be processed.
 * @param configuration The configuration object.
 * @param delegate The delegate.
 */
+ (nullable instancetype)presentOn:(nonnull UIViewController *)presenter
                          workflow:(nonnull SBSDKUIWorkflow *)workflow
                     configuration:(nonnull SBSDKUIWorkflowScannerConfiguration *)configuration
                          delegate:(nullable id<SBSDKUIWorkflowScannerViewControllerDelegate>)delegate;

/**
 * Initializes a dynamic workflow.
 * @param step The first step of the dynamic workflow.
 * @param configuration The configuration object.
 * @param datasource The datasource that delivers the following steps.
 * @param delegate The delegate.
 */
+ (nullable instancetype)createNewWithInitialWorkflowStep:(nonnull SBSDKUIWorkflowStep *)step
                                            configuration:(nonnull SBSDKUIWorkflowScannerConfiguration *)configuration
                                               datasource:(nonnull id<SBSDKUIWorkflowScannerViewControllerDatasource>)datasource
                                                 delegate:(nullable id<SBSDKUIWorkflowScannerViewControllerDelegate>)delegate;

/**
 * Initializes and presents a workflow scanner view controller with a dynamic workflow.
 * @param presenter The view controller that should present the workflow scanner view controller.
 * @param step The first step of the dynamic workflow.
 * @param configuration The configuration object.
 * @param datasource The datasource that delivers the following steps.
 * @param delegate The delegate.
 */
+ (nullable instancetype)presentOn:(nonnull UIViewController *)presenter
                       initialStep:(nonnull SBSDKUIWorkflowStep *)step
                     configuration:(nonnull SBSDKUIWorkflowScannerConfiguration *)configuration
                        datasource:(nonnull id<SBSDKUIWorkflowScannerViewControllerDatasource>)datasource
                          delegate:(nullable id<SBSDKUIWorkflowScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIWorkflowScannerViewControllerDelegate> delegate;

/** The receivers datasource. */
@property (nullable, nonatomic, readonly, weak) id <SBSDKUIWorkflowScannerViewControllerDatasource> datasource;

/** Resets the workflow and starts it again. */
- (void)resetWorkflow;

@end

NS_ASSUME_NONNULL_END
