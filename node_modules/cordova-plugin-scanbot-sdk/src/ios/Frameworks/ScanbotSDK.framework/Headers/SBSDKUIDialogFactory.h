//
//  SBSDKUIDialogFactory.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 23.02.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Factory class for creating instances of iOS system style alerts with extended functionality, e.g. displaying an image.
 */
@interface SBSDKUIDialogFactory : NSObject

/**
 * Creates and returns an instance of an alert for modal presentation.
 * @param title The title of the alert.
 * @param message The message of the  alert.
 * @param buttonTitle The confimration buttons title of the alert.
 * @param image The image to be shown within the alert. Can be zoomed and scrolled.
 * @param handler The completion handler to be called when the confirm button is pressed.
 * @return The instance of the alert view controller.
 */
+ (UIViewController *)createWithTitle:(nullable NSString *)title
                              message:(nullable NSString *)message
                   confirmButtonTitle:(nullable NSString *)buttonTitle
                                image:(nullable UIImage *)image
                didPressConfirmButton:(void (^ __nullable)(void))handler;

@end

NS_ASSUME_NONNULL_END
