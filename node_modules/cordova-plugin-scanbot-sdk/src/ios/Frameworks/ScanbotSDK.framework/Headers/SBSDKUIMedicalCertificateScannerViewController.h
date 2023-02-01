//
//  SBSDKUIMedicalCertificateScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.01.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUICameraViewController.h"
#import "SBSDKUIMedicalCertificateScannerConfiguration.h"
#import "SBSDKUIMedicalCertificateScannerViewControllerDelegate.h"

NS_ASSUME_NONNULL_BEGIN


/**
 * A Ready-To-Use viewcontroller to scan medical certificates.
 */
@interface SBSDKUIMedicalCertificateScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIMedicalCertificateScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIMedicalCertificateScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUIMedicalCertificateScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIMedicalCertificateScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIMedicalCertificateScannerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIMedicalCertificateScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIMedicalCertificateScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIMedicalCertificateScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIMedicalCertificateScannerViewControllerDelegate> delegate;

/** Enables or disables the recognition. */
@property (nonatomic, getter=isRecognitionEnabled) BOOL recognitionEnabled;

@end

NS_ASSUME_NONNULL_END
