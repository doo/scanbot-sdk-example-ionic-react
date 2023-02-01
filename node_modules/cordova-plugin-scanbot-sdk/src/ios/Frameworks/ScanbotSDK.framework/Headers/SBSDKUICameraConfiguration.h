//
//  SBSDKUICameraConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 17.11.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKCameraDevice.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the camera of all RTU-UI components.
 */
@interface SBSDKUICameraConfiguration : NSObject

/** The camera to be used. Defaults to the back-facing wide angle camera. */
@property (nonnull, nonatomic, strong) SBSDKCameraDevice *camera;

@end

NS_ASSUME_NONNULL_END
