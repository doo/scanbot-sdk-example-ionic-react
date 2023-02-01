//
//  SBSDKUIMultipleObjectScannerViewController.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 02.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIMultipleObjectScannerConfiguration.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKUIDocument.h"

@class SBSDKUIMultipleObjectScannerViewController;

/** Delegate protocol for `SBSDKUIMultipleObjectScannerViewController`. */
@protocol SBSDKUIMultipleObjectScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that the scanning view controller has scanned objects
 * and the view controller has dismissed.
 * @param viewController The `SBSDKUIMultipleObjectScannerViewController` which generated the scanned objects and dismissed.
 * @param document The document containing the scanned objects.
 */
- (void)multipleObjectScannerViewController:(nonnull SBSDKUIMultipleObjectScannerViewController *)viewController
                      didFinishWithDocument:(nonnull SBSDKUIDocument *)document;

@optional
/**
 * Optional: informs the delegate that the `SBSDKUIMultipleObjectScannerViewController` has been cancelled and dismissed.
 * @param viewController The `SBSDKUIMultipleObjectScannerViewController` that did dismiss.
 */
- (void)multipleObjectScannerViewControllerDidCancel:(nonnull SBSDKUIMultipleObjectScannerViewController *)viewController;

@end

/**
 * A highly customizable camera-based view controller to scan multiple objects.
 */
@interface SBSDKUIMultipleObjectScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of `SBSDKUIMultipleObjectScannerViewController` and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of `SBSDKUIMultipleObjectScannerViewController`.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                withConfiguration:(nonnull SBSDKUIMultipleObjectScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIMultipleObjectScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of `SBSDKUIMultipleObjectScannerViewController`. Generates a new instance of `SBSDKUIDocument`.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of `SBSDKUIMultipleObjectScannerViewController`.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIMultipleObjectScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIMultipleObjectScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of `SBSDKUIMultipleObjectScannerConfiguration` and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param document The document to which the scanned objects will be added. If nil the receiver creates a new document.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of `SBSDKUIMultipleObjectScannerConfiguration`.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                     withDocument: (nullable SBSDKUIDocument *)document
                withConfiguration:(nonnull SBSDKUIMultipleObjectScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIMultipleObjectScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of `SBSDKUIMultipleObjectScannerConfiguration`.
 * @param document The document to which the scanned objects will be added. If nil the receiver creates a new document.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of `SBSDKUIMultipleObjectScannerConfiguration`.
 */
+ (nonnull instancetype)createNewWithDocument:(nullable SBSDKUIDocument *)document
                                configuration:(nonnull SBSDKUIMultipleObjectScannerConfiguration *)configuration
                                  andDelegate:(nullable id<SBSDKUIMultipleObjectScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIMultipleObjectScannerViewControllerDelegate> delegate;

@end
