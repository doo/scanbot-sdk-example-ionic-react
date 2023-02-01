//
//  SBSDKUITextDataScannerViewControllerDelegate.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 14.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SBSDKUITextDataScannerViewController;
@class SBSDKUITextDataScannerStepResult;
@class SBSDKUITextDataScannerStep;

/** Delegate protocol for 'SBSDKUITextDataScannerViewController'. */
@protocol SBSDKUITextDataScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that the text has been recognized and validated.
 * @param viewController The text data scanner view controller instance.
 * @param step The step that this result was recognized for.
 * @param result An object, that contains recognized text.
 *
 */
- (void)textLineRecognizerViewController:(nonnull SBSDKUITextDataScannerViewController *)viewController
                           didFinishStep:(nonnull SBSDKUITextDataScannerStep *)step
                              withResult:(nonnull SBSDKUITextDataScannerStepResult *)result;

@optional

/**
 * Optional: Informs the delegate that the 'SBSDKUITextDataScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUITextDataScannerViewController' that did dismiss.
 */
- (void)textLineRecognizerViewControllerDidCancel:(nonnull SBSDKUITextDataScannerViewController *)viewController;

@end
