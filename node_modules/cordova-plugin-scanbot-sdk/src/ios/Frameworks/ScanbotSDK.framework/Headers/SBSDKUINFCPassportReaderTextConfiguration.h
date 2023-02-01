//
//  SBSDKUINFCPassportReaderTextConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/**
 *  Configuration for the textual contents of the NFC reader screens.
 */
@interface SBSDKUINFCPassportReaderTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed as description. */
@property (nonnull, nonatomic, strong) NSString *finderTextHint;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed as a hint to hold device over the NFC chip. */
@property (nullable, nonatomic, strong) NSString *holdOverTheChipTitle;

/** A hint that notifies about downloading datagroups. */
@property (nullable, nonatomic, strong) NSString *downloadingDataTitle;

/** A title for the state when there is no NFC chip installed on the device, or it is not available. */
@property (nullable, nonatomic, strong) NSString *noChipErrorTitle;

/** A title for the error, when NFC reader failed to perform authentication. */
@property (nullable, nonatomic, strong) NSString *authenticationErrorTitle;

/** A title for the error, when NFC reader failed to download the data. */
@property (nullable, nonatomic, strong) NSString *downloadErrorTitle;

@end
