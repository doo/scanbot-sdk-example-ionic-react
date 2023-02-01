//
//  SBSDKUIGenericDocumentRecognizerViewControllerDelegate.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKGenericDocumentRecognizer.h"

@class SBSDKUIGenericDocumentRecognizerViewController;

/** Delegate protocol for 'SBSDKUIGenericDocumentRecognizerViewController'. */
@protocol SBSDKUIGenericDocumentRecognizerViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that one or multiple generic documents have been recognized and the view controller has been dismissed.
 * @param viewController The view controller that recognized the documents.
 * @param documents An array of recognized generic documents.
 *
 */
- (void)genericDocumentRecognizerViewController:(nonnull SBSDKUIGenericDocumentRecognizerViewController *)viewController
                         didFinishWithDocuments:(nonnull NSArray<SBSDKGenericDocument *> *)documents;


@optional

/**
 * Optional: informs the delegate that the 'SBSDKUIGenericDocumentRecognizerViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUIGenericDocumentRecognizerViewController' that did dismiss.
 */
- (void)genericDocumentRecognizerViewControllerDidCancel:(nonnull SBSDKUIGenericDocumentRecognizerViewController *)viewController;

@end
