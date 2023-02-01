//
//  SBSDKUICroppingViewController.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 4/6/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUICroppingScreenConfiguration.h"
#import "SBSDKUIViewController.h"
#import "SBSDKUIPage.h"

@class SBSDKUICroppingViewController;

/** Delegate protocol for 'SBSDKUICroppingViewController'. */
@protocol SBSDKUICroppingViewControllerDelegate <SBSDKUIViewControllerDelegate>

/**
 * Informs the delegate that the polygon or orientation of the edited page was changed
 * and the cropping view controller did dismiss.
 * @param viewController The editing crop view controller that initiated the change and that did dismiss.
 * @param changedPage The page that was changed.
 */
- (void)croppingViewController:(nonnull SBSDKUICroppingViewController *)viewController
                     didFinish:(nonnull SBSDKUIPage *)changedPage;

@optional
/**
 * Optional: informs the delegate that the 'SBSDKUICroppingViewController' has been cancelled and dismissed.
 * @param viewController The 'SBSDKUICroppingViewController' that did dismiss.
 */
- (void)croppingViewControllerDidCancel:(nonnull SBSDKUICroppingViewController *)viewController;

@end

/**
 * A highly customizable view controller to edit a pages polygon or the page's orientation.
 */
@interface SBSDKUICroppingViewController: SBSDKUIViewController

/**
 * Creates a new instance of 'SBSDKUICroppingViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param page The page to be cropped or rotated.
 * @param configuration The configuration to define look and feel of the new page cropping view controller.
 * @param delegate The delegate of the new page cropping view controller.
 * @return A new instance of 'SBSDKUICroppingViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                         withPage:(nonnull SBSDKUIPage *)page
                withConfiguration:(nonnull SBSDKUICroppingScreenConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUICroppingViewControllerDelegate>)delegate;

/**
 * Creates a new instance of 'SBSDKUICroppingViewController'.
 * @param page The page to be cropped or rotated.
 * @param configuration The configuration to define look and feel of the new page cropping view controller.
 * @param delegate The delegate of the new page cropping view controller.
 * @return A new instance of 'SBSDKUICroppingViewController'.
 */
+ (nonnull instancetype)createNewWithPage:(nonnull SBSDKUIPage *)page
                        withConfiguration:(nonnull SBSDKUICroppingScreenConfiguration *)configuration
                              andDelegate:(nullable id<SBSDKUICroppingViewControllerDelegate>)delegate;

/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUICroppingViewControllerDelegate> delegate;

@end
