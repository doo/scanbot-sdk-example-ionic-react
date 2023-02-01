//
//  SBSDKUIMultipleObjectScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 02.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIMultipleObjectScannerUIConfiguration.h"
#import "SBSDKUIMultipleObjectScannerTextConfiguration.h"
#import "SBSDKUIMultipleObjectScannerBehaviorConfiguration.h"

/**
 * This class describes the look and feel, the behavior, as well as the textual contents of the detection
 * screen for multiple objects detector.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
 */
@interface SBSDKUIMultipleObjectScannerConfiguration : SBSDKUIConfiguration

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIMultipleObjectScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the document scanning screen.
 * @param behaviorConfiguration A configuration for defining the behavior of the document scanning screen.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIMultipleObjectScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIMultipleObjectScannerTextConfiguration *)textConfiguration
                         behaviorConfiguration:(nonnull SBSDKUIMultipleObjectScannerBehaviorConfiguration *)behaviorConfiguration
                        NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIMultipleObjectScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIMultipleObjectScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMultipleObjectScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMultipleObjectScannerTextConfiguration *textConfiguration;

/** The configuration controlling the scanning screens behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIMultipleObjectScannerBehaviorConfiguration *behaviorConfiguration;

@end
