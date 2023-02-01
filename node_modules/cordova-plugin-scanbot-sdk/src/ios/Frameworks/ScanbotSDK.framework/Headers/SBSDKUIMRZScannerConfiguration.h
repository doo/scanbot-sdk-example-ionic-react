//
//  SBSDKUIMRZScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 20.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIMRZScannerUIConfiguration.h"
#import "SBSDKUIMRZScannerTextConfiguration.h"
#import "SBSDKUIMRZScannerBehaviorConfiguration.h"

/**
 * This class describes the look and feel, as well as the textual contents of the detection
 * screens for machine readable zones.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
 */
@interface SBSDKUIMRZScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIMRZScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the MRZ scanner screen.
 * @param behaviorConfiguration A configuration for the MRZ scanners behavior.
 * @param cameraConfiguration A configuration for the MRZ scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIMRZScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIMRZScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIMRZScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIMRZScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIMRZScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMRZScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMRZScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMRZScannerBehaviorConfiguration *behaviorConfiguration;

@end

