//
//  SBSDKUITextDataScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 11.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/**
 * Configuration for the textual contents of the text line recognizer.
*/
@interface SBSDKUITextDataScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

@end
