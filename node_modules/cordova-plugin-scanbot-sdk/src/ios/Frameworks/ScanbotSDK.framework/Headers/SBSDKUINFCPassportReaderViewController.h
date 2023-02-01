//
//  SBSDKUINFCPassportReaderViewController.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import "SBSDKUIViewController.h"
#import "SBSDKUICameraViewController.h"
#import "SBSDKUINFCPassportReaderConfiguration.h"
#import "SBSDKUINFCPassportReaderViewControllerDelegate.h"
#import "SBSDKUINFCPassportReaderStorage.h"

API_AVAILABLE(ios(13.0))

/**
 * A highly customizable camera-based view controller to extract the data from a passport's Near Field Communication (NFC) chip.
 */
@interface SBSDKUINFCPassportReaderViewController : SBSDKUICameraViewController

/**
 * Creates a new instance of 'SBSDKUINFCPassportReaderViewController' and presents it modally.
 * @param presenter The view controller the new instance should be presented on.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUINFCPassportReaderViewController'.
 */
+ (nonnull instancetype)presentOn:(nonnull UIViewController *)presenter
                withConfiguration:(nonnull SBSDKUINFCPassportReaderConfiguration *)configuration
                      andDelegate:(nullable id<SBSDKUINFCPassportReaderViewControllerDelegate>)delegate;


/**
 * Creates a new instance of 'SBSDKUINFCPassportReaderViewController'.
 * @param configuration The configuration to define look and feel of the new detection view controller.
 * @param delegate The delegate of the new detection view controller.
 * @return A new instance of 'SBSDKUINFCPassportReaderViewController'.
 */
+ (nonnull instancetype)createNewWithConfiguration:(nonnull SBSDKUINFCPassportReaderConfiguration *)configuration
                                       andDelegate:(nullable id<SBSDKUINFCPassportReaderViewControllerDelegate>)delegate;


/** The receivers delegate. */
@property (nullable, nonatomic, weak) id <SBSDKUINFCPassportReaderViewControllerDelegate> delegate;

@end

