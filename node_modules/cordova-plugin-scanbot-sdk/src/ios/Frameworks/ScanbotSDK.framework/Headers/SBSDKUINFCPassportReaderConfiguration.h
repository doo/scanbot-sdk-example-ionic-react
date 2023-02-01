//
//  SBSDKUINFCPassportReaderConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUINFCPassportReaderUIConfiguration.h"
#import "SBSDKUINFCPassportReaderTextConfiguration.h"
#import "SBSDKUINFCPassportReaderBehaviorConfiguration.h"
/**
* This class describes the look and feel, as well as the textual contents of the NFC reader screen.
* Use the 'defaultConfiguration' class method to retrieve an instance and modify it.
*/
@interface SBSDKUINFCPassportReaderConfiguration : SBSDKUIConfiguration

/**
 * Designated initializer. Creates a new instance of 'SBSDKUINFCPassportReaderConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for text being displayed in the MRZ scanner screen.
 * @param behaviorConfiguration A configuration for the MRZ scanners behavior.
 * @param cameraConfiguration A configuration for the MRZ scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUINFCPassportReaderUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUINFCPassportReaderTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUINFCPassportReaderBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUINFCPassportReaderConfiguration' with default values.
 */
+ (nonnull SBSDKUINFCPassportReaderConfiguration *)defaultConfiguration;

/** The user interface subconfiguration. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUINFCPassportReaderUIConfiguration *uiConfiguration;

/** The configuration for displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUINFCPassportReaderTextConfiguration *textConfiguration;

/** The configuration for behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUINFCPassportReaderBehaviorConfiguration *behaviorConfiguration;

@end
