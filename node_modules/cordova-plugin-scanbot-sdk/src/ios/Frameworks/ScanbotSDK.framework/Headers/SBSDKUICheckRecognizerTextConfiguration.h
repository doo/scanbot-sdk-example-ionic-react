//
//  SBSDKUICheckRecognizerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/**
 * Configuration for the textual contents of the check scanner.
*/
@interface SBSDKUICheckRecognizerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed when starting scanning for a medical certificate. Lasts 3 secs. */
@property (nullable, nonatomic, strong) NSString *userGuidanceTitleStartScanning;

/** String being displayed when searching for a medical certificate. */
@property (nullable, nonatomic, strong) NSString *userGuidanceTitleSearching;

/** String being displayed when energy saving is active. */
@property (nullable, nonatomic, strong) NSString *userGuidanceTitleEnergySaving;

/** String being displayed as the title in the error alert that may occur when the recognition fails on captured high-resolution images. */
@property (nonnull, nonatomic, strong) NSString *errorAlertTitle;

/** String being displayed as the message in the error alert that may occur when the recognition fails on captured high-resolution images. */
@property (nonnull, nonatomic, strong) NSString *errorAlertMessage;

/** String being displayed as the button text in the error alert that may occur when the recognition fails on captured high-resolution images. */
@property (nonnull, nonatomic, strong) NSString *errorAlertButtonText;

@end
