//
//  SBSDKUIHealthInsuranceCardScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 06.08.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIHealthInsuranceCardScannerUIConfiguration.h"
#import "SBSDKUIHealthInsuranceCardScannerTextConfiguration.h"
#import "SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration.h"

/**
* This class describes the look and feel, as well as the textual contents of the detection screen for Health Insurance Card scanner.
* Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
*/
@interface SBSDKUIHealthInsuranceCardScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIHealthInsuranceCardScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the Health Insurance Card scanner screen.
 * @param behaviorConfiguration A configuration for Health Insurance Card scanners behavior.
 * @param cameraConfiguration A configuration for Health Insurance Card scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIHealthInsuranceCardScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIHealthInsuranceCardScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIHealthInsuranceCardScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIHealthInsuranceCardScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIHealthInsuranceCardScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIHealthInsuranceCardScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration *behaviorConfiguration;

@end
