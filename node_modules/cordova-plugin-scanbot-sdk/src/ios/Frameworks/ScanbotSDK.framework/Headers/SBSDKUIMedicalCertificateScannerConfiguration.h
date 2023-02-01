//
//  SBSDKUIMedicalCertificateScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.01.22.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIMedicalCertificateScannerUIConfiguration.h"
#import "SBSDKUIMedicalCertificateScannerTextConfiguration.h"
#import "SBSDKUIMedicalCertificateScannerBehaviorConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class describes the look and feel, the behavior and the textual contents of the medical certificate scanner.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it as needed.
 */
@interface SBSDKUIMedicalCertificateScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIMedicalCertificateScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the scanners behavior.
 * @param cameraConfiguration A configuration for the scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIMedicalCertificateScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIMedicalCertificateScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIMedicalCertificateScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIMedicalCertificateScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIMedicalCertificateScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMedicalCertificateScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMedicalCertificateScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMedicalCertificateScannerBehaviorConfiguration *behaviorConfiguration;
@end

NS_ASSUME_NONNULL_END
