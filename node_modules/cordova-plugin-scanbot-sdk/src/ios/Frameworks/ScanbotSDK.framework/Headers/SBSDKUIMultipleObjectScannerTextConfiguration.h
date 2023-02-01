//
//  SBSDKUIMultipleObjectScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 03.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/** Configuration for the textual contents of the document scanning screen. */
@interface SBSDKUIMultipleObjectScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the batch mode button. */
@property (nullable, nonatomic, strong) NSString *batchButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the objects-amount button additionally. Use %d as number formatting symbol. */
@property (nullable, nonatomic, strong) NSString *objectsCounterButtonTitle;

/** String being displayed on the label describing that the app is in split mode and needs to go fullscreen to work with camera. */
@property (nonnull, nonatomic, strong) NSString *cameraUnavailableExplanationText;

@end

