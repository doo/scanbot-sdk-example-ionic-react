//
//  SBSDKUITextDataScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 11.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUITextDataScannerUIConfiguration.h"
#import "SBSDKUITextDataScannerTextConfiguration.h"
#import "SBSDKUITextDataScannerBehaviorConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class describes the look and feel, the behavior and the textual contents of the detection screens for text line recognizer.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it as needed.
 */
@interface SBSDKUITextDataScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUITextDataScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the scanners behavior.
 * @param cameraConfiguration A configuration for the scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUITextDataScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUITextDataScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUITextDataScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUITextDataScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUITextDataScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUITextDataScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUITextDataScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUITextDataScannerBehaviorConfiguration *behaviorConfiguration;
@end

NS_ASSUME_NONNULL_END
