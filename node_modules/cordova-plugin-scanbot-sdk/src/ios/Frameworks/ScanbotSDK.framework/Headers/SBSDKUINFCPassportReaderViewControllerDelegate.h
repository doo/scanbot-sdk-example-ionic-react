//
//  SBSDKUINFCReaderViewControllerDelegate.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUINFCPassportReaderResult.h"

@class SBSDKUINFCPassportReaderViewController;

/** Delegate protocol for 'SBSDKUINFCPassportReaderViewController'. */
@protocol SBSDKUINFCPassportReaderViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that one or more data groups have been downloaded and the view controller has dismissed.
 * @param viewController The NFC passport reader view controller that read passport data.
 * @param result An object, that contains received datagroups.
 *
 */
- (void)nfcPassportReaderViewController:(nonnull SBSDKUINFCPassportReaderViewController *)viewController
                didFinishWithResult:(nonnull SBSDKUINFCPassportReaderResult *)result;

@optional

/**
 * Optional: informs the delegate that the 'SBSDKUINFCPassportReaderViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUINFCPassportReaderViewController' that did dismiss.
 */
- (void)nfcPassportReaderViewControllerDidCancel:(nonnull SBSDKUINFCPassportReaderViewController *)viewController;

@end
