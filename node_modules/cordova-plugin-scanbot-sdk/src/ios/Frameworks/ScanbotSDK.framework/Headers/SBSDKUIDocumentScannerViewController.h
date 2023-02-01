//
//  SBSDKUIDocumentScannerViewController.h
//  SBSDK Internal Demo
//
//  Created by Yevgeniy Knizhnik on 2/28/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIDocumentScannerConfiguration.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUIDocument.h"
#import "SBSDKUICameraViewController.h"

@class SBSDKUIDocumentScannerViewController;

/** Delegate protocol for 'SBSDKUIDocumentScannerViewController'. */
@protocol SBSDKUIDocumentScannerViewControllerDelegate <SBSDKUIViewControllerDelegate>
/**
 * Informs the delegate that the document scanning view controller has scanned document pages
 * and the view controller has dismissed.
 * @param viewController The 'SBSDKUIDocumentScannerViewController' which generated the scanned pages and dismissed.
 * @param document The document containing the scanned pages.
 */
- (void)scanningViewController:(nonnull SBSDKUIDocumentScannerViewController *)viewController
         didFinishWithDocument:(nonnull SBSDKUIDocument *)document;

@optional
/**
 * Optional: informs the delegate that the 'SBSDKUIDocumentScannerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUIDocumentScannerViewController' that did dismiss.
 */
- (void)scanningViewControllerDidCancel:(nonnull SBSDKUIDocumentScannerViewController *)viewController;

@end

/**
 * A highly customizable camera-based view controller to scan documents.
 * An edge-detection based algorithm finds documents in the camera stream.
 * A manual or automatic high resolution snapshot can be made. Based on the detected area of the document in the photo,
 * the photo is cropped and perspective-corrected, so that a nice flattened image of the document only is created.
 */
@interface SBSDKUIDocumentScannerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIDocumentScannerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param document The document to which the scanned pages will be added. If nil the receiver creates a new document.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of 'SBSDKUIDocumentScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                     withDocument: (nullable SBSDKUIDocument *)document
                withConfiguration:(nonnull SBSDKUIDocumentScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIDocumentScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIDocumentScannerViewController' and presents it modally. Creates a new
 * 'SBSDKUIDocument' instance.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of 'SBSDKUIDocumentScannerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                withConfiguration:(nonnull SBSDKUIDocumentScannerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIDocumentScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIDocumentScannerViewController'.
 * @param document The document to which the scanned pages will be added. If nil the receiver creates a new document.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of 'SBSDKUIDocumentScannerViewController'.
 */
+ (nonnull instancetype)createNewWithDocument:(nullable SBSDKUIDocument *)document
                                configuration:(nonnull SBSDKUIDocumentScannerConfiguration *)configuration
                                  andDelegate:(nullable id<SBSDKUIDocumentScannerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIDocumentScannerViewController'. Generates a new instance of 'SBSDKUIDocument'.
 * @param configuration The configuration to define look and feel of the new scanning view controller.
 * @param delegate The delegate of the new scanning view controller.
 * @return A new instance of 'SBSDKUIDocumentScannerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIDocumentScannerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIDocumentScannerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIDocumentScannerViewControllerDelegate> delegate;

@end
