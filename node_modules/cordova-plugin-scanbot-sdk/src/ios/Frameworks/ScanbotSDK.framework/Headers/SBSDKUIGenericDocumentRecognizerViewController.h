//
//  SBSDKUIGenericDocumentRecognizerViewController.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUICameraViewController.h"
#import "SBSDKUIGenericDocumentRecognizerConfiguration.h"
#import "SBSDKUIGenericDocumentRecognizerViewControllerDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A highly customizable camera-based view controller to recognize generic documents.
 */
@interface SBSDKUIGenericDocumentRecognizerViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUIGenericDocumentRecognizerViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIGenericDocumentRecognizerViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                    configuration:(nonnull SBSDKUIGenericDocumentRecognizerConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUIGenericDocumentRecognizerViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUIGenericDocumentRecognizerViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUIGenericDocumentRecognizerViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUIGenericDocumentRecognizerConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUIGenericDocumentRecognizerViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUIGenericDocumentRecognizerViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
