//
//  SBSDKUIMRZScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 20.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/**
 * Configuration for the textual contents of the detector screens for machine readable zones.
 */
@interface SBSDKUIMRZScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed as description. */
@property (nonnull, nonatomic, strong) NSString *finderTextHint;

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

@end
