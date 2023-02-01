//
//  SBSDKUILicensePlateScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the textual contents of the license plate scanner.
 */
@interface SBSDKUILicensePlateScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** The string being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** The string being displayed as description. */
@property (nonnull, nonatomic, strong) NSString *finderTextHint;

/** The title of the confirmation dialog. */
@property (nullable, nonatomic, strong) NSString *confirmationDialogTitle;

/** The message text of the confirmation dialog. */
@property (nullable, nonatomic, strong) NSString *confirmationDialogMessage;

/** The title of the confirmation dialog retry button. */
@property (nonnull, nonatomic, strong) NSString *confirmationDialogRetryButtonTitle;

/** The title of the confirmation dialog confirm button. */
@property (nonnull, nonatomic, strong) NSString *confirmationDialogConfirmButtonTitle;

@end

NS_ASSUME_NONNULL_END
