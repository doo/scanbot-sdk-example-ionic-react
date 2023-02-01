//
//  SBSDKUICheckRecognizerConfiguration.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUICheckRecognizerUIConfiguration.h"
#import "SBSDKUICheckRecognizerTextConfiguration.h"
#import "SBSDKUICheckRecognizerBehaviorConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class describes the look and feel, the behavior and the textual contents of the medical certificate scanner.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it as needed.
 */
@interface SBSDKUICheckRecognizerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUICheckRecognizerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the scanners behavior.
 * @param cameraConfiguration A configuration for the scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUICheckRecognizerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUICheckRecognizerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUICheckRecognizerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUICheckRecognizer' with default values.
 */
+ (nonnull SBSDKUICheckRecognizerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUICheckRecognizerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUICheckRecognizerTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUICheckRecognizerBehaviorConfiguration *behaviorConfiguration;
@end

NS_ASSUME_NONNULL_END
