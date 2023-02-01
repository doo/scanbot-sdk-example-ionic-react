//
//  SBSDKUITextDataScannerViewController.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 11.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUITextDataScannerConfiguration.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKUITextDataScannerViewControllerDelegate.h"
#import "SBSDKUITextDataScannerStep.h"
#import "SBSDKUITextDataScannerStepResult.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A highly customizable camera-based view controller to recognize and validate a small rectangular text area in realtime.
 * A view finder like rectangle shows the area where text is recognized. The camera is zoomed in and out automatically.
 * Once some text is recognized within the view finder area the result is delivered to the receivers delegate.
 */
@interface SBSDKUITextDataScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUITextDataScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUITextDataScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUITextDataScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUITextDataScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUITextDataScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUITextDataScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUITextDataScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUITextDataScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUITextDataScannerViewControllerDelegate> delegate;

/** Enables or disables the recognition. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

@end

NS_ASSUME_NONNULL_END
