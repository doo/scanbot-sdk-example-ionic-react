//
//  SBSDKUIDocumentScannerConfiguration.h
//  SBSDK Internal Demo
//
//  Created by Yevgeniy Knizhnik on 3/1/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIDocumentScannerUIConfiguration.h"
#import "SBSDKUIDocumentScannerTextConfiguration.h"
#import "SBSDKUIDocumentScannerBehaviorConfiguration.h"

/**
 * This class describes the look and feel, the behavior, as well as the textual contents of the detection
 * screen for documents.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
 */
@interface SBSDKUIDocumentScannerConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUIDocumentScannerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the document scanning screen.
 * @param behaviorConfiguration A configuration for defining the behavior of the document scanning screen.
 * @param cameraConfiguration A configuration object for defining the camera of the document scanning screen.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIDocumentScannerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIDocumentScannerTextConfiguration *)textConfiguration
                         behaviorConfiguration:(nonnull SBSDKUIDocumentScannerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIDocumentScannerConfiguration' with default values.
 */
+ (nonnull SBSDKUIDocumentScannerConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIDocumentScannerUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIDocumentScannerTextConfiguration *textConfiguration;

/** The configuration controlling the scanning screens behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIDocumentScannerBehaviorConfiguration *behaviorConfiguration;

@end
