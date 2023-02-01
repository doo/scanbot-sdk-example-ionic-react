//
//  SBSDKUIHealthInsuranceCardScannerViewController.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 06.08.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKHealthInsuranceCardRecognitionResult.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKUIHealthInsuranceCardScannerConfiguration.h"

@class SBSDKUIHealthInsuranceCardScannerViewController;

/** Delegate protocol for 'SBSDKUIHealthInsuranceCardScannerViewController'. */
@protocol SBSDKUIHealthInsuranceCardScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that a health insurance card has been detected.
 * @param viewController The detection view controller that detected the health insurance card.
 * @param card the detected health insurance card.
 */
- (void)healthInsuranceCardDetectionViewController:(nonnull SBSDKUIHealthInsuranceCardScannerViewController *)viewController
                         didDetectCard:(nonnull SBSDKHealthInsuranceCardRecognitionResult *)card;

@optional

/**
 * Optional: Informs the delegate that the 'SBSDKUIHealthInsuranceCardScannerViewController' has been canceled and dismissed.
 * @param viewController The 'SBSDKUIHealthInsuranceCardScannerViewController' that did dismiss.
 */
- (void)healthInsuranceCardDetectionViewControllerDidCancel:(nonnull SBSDKUIHealthInsuranceCardScannerViewController *)viewController;

@end

/** A view controller for camera-based detection of health insurance cards. */
@interface SBSDKUIHealthInsuranceCardScannerViewController : SBSDKUICameraViewController

/** 
 * Creates a new instance of 'SBSDKUIHealthInsuranceCardScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIHealthInsuranceCardScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                withConfiguration:(nonnull SBSDKUIHealthInsuranceCardScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIHealthInsuranceCardScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIHealthInsuranceCardScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIHealthInsuranceCardScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIHealthInsuranceCardScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIHealthInsuranceCardScannerViewControllerDelegate>)delegate;

/** Enables or disables the detection. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIHealthInsuranceCardScannerViewControllerDelegate> delegate;

@end
