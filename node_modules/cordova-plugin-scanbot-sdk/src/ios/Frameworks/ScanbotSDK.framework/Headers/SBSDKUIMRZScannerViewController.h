//
//  SBSDKUIMRZScannerViewController.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 4/3/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIMRZScannerConfiguration.h"
#import "SBSDKMachineReadableZoneRecognizerResult.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"

@class SBSDKUIMRZScannerViewController;

/** Delegate protocol for 'SBSDKUIMRZScannerViewController'. */
@protocol SBSDKUIMRZScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that a machine readable zone has been detected.
 * @param viewController The detection view controller that detected the machine readable zone.
 * @param zone The detected machine readable zone.
 */
- (void)mrzDetectionViewController:(nonnull SBSDKUIMRZScannerViewController *)viewController
                         didDetect:(nonnull SBSDKMachineReadableZoneRecognizerResult *)zone;

@optional
/**
 * Optional: informs the delegate that the 'SBSDKUIMRZScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUIMRZScannerViewController' that did dismiss.
 */
- (void)mrzDetectionViewControllerDidCancel:(nonnull SBSDKUIMRZScannerViewController *)viewController;
@end

/**
 * A highly customizable camera-based view controller to detect machine readable zones.
 */
@interface SBSDKUIMRZScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIMRZScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIMRZScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                withConfiguration:(nonnull SBSDKUIMRZScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIMRZScannerViewControllerDelegate>)delegate;


/**
 * Creates a new instance of 'SBSDKUIMRZScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIMRZScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIMRZScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIMRZScannerViewControllerDelegate>)delegate;

/** Enables or disables the machine readable zones detection. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIMRZScannerViewControllerDelegate> delegate;

@end
