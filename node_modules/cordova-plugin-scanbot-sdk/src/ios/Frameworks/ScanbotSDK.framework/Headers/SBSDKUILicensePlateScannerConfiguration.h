//
//  SBSDKUILicensePlateScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUILicensePlateScannerBehaviorConfiguration.h"
#import "SBSDKUILicensePlateScannerTextConfiguration.h"
#import "SBSDKUILicensePlateScannerUIConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class describes the look and feel, the behavior and the textual contents of the detection screens for license plate scanner.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it as needed.
 */
@interface SBSDKUILicensePlateScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUILicensePlateScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for the text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the scanners behavior.
 * @param cameraConfiguration A configuration for the scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUILicensePlateScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUILicensePlateScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUILicensePlateScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUILicensePlateScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUILicensePlateScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUILicensePlateScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUILicensePlateScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUILicensePlateScannerBehaviorConfiguration *behaviorConfiguration;

@end

NS_ASSUME_NONNULL_END
