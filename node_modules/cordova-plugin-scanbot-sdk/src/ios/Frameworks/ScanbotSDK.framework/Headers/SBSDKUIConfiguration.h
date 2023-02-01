//
//  SBSDKUIConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 17.11.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUICameraConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The general configuration class for all RTU-UI components.
 * Component specific configurations are subclassed from this class.
 */
@interface SBSDKUIConfiguration : NSObject

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIConfiguration' and returns it.
 * @param cameraConfiguration A configuration for the camera device.
 */
- (nonnull instancetype)initWithCameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIConfiguration' with default values.
 */
+ (nonnull SBSDKUIConfiguration *)defaultConfiguration;

/** The camera configuration. */
@property(nonatomic, strong, readonly) SBSDKUICameraConfiguration *cameraConfiguration;

@end

NS_ASSUME_NONNULL_END
