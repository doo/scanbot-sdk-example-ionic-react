//
//  SBSDKUICheckRecognizerViewController.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUICameraViewController.h"
#import "SBSDKUICheckRecognizerConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKUICheckRecognizerViewController;

/**
 * The delegation protocol for `SBSDKUICheckRecognizerViewController`.
 */
@protocol SBSDKUICheckRecognizerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that the `SBSDKUICheckRecognizerViewController` has recognized a check.
 * @param viewController The check scanner viewcontroller that recognized a check.
 * @param result The recognized check result.
 */
- (void)checkRecognizerViewController:(SBSDKUICheckRecognizerViewController *)viewController
                    didRecognizeCheck:(SBSDKCheckRecognizerResult *)result;

@optional
/**
 * Optional.
 * Informs the delegate that the `SBSDKUICheckRecognizerViewController` has been cancelled.
 * @param viewController The check scanner viewcontroller that cancelled scanning.
 */
- (void)checkRecognizerViewControllerDidCancel:(SBSDKUICheckRecognizerViewController *)viewController;

@end


/**
 * A Ready-To-Use viewcontroller to recognize checks using the camera.
 */
@interface SBSDKUICheckRecognizerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUICheckRecognizerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUICheckRecognizerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUICheckRecognizerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUICheckRecognizerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUICheckRecognizerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUICheckRecognizerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUICheckRecognizerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUICheckRecognizerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUICheckRecognizerViewControllerDelegate> delegate;

/** Enables or disables the recognition. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

@end

NS_ASSUME_NONNULL_END
