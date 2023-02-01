//
//  SBSDKUIWorkflowScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 21.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIWorkflowScannerUIConfiguration.h"
#import "SBSDKUIWorkflowScannerTextConfiguration.h"
#import "SBSDKUIWorkflowScannerBehaviorConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/** Configuration object that holds the subconfigurations for a 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowScannerConfiguration : SBSDKUIConfiguration

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIWorkflowScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the workflow scanner screen.
 * @param behaviorConfiguration A configuration for workflow scanner behavior.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIWorkflowScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIWorkflowScannerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIWorkflowScannerBehaviorConfiguration *)behaviorConfiguration
NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIWorkflowScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIWorkflowScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIWorkflowScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIWorkflowScannerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIWorkflowScannerBehaviorConfiguration *behaviorConfiguration;

@end

NS_ASSUME_NONNULL_END
