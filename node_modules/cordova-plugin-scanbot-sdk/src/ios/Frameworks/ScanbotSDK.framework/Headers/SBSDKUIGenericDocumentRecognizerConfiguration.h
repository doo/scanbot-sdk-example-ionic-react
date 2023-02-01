//
//  SBSDKUIGenericDocumentRecognizerConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIConfiguration.h"
#import "SBSDKUIGenericDocumentRecognizerUIConfiguration.h"
#import "SBSDKUIGenericDocumentRecognizerTextConfiguration.h"
#import "SBSDKUIGenericDocumentRecognizerBehaviorConfiguration.h"


/**
 * This class describes the look and feel, the behavior and the textual contents of the generic document recognizers screen.
 * Use the 'defaultConfiguration' class method to retrieve an instance and modify it as needed.
 */
@interface SBSDKUIGenericDocumentRecognizerConfiguration : SBSDKUIConfiguration
/**
 * Designated initializer. Creates a new instance of 'SBSDKUIGenericDocumentRecognizerConfiguration' and returns it.
 * @param uiConfiguration A configuration for the user interface. Defines colors and sizes.
 * @param textConfiguration A configuration for the text being displayed in the scanner screen.
 * @param behaviorConfiguration A configuration for the scanners behavior.
 * @param cameraConfiguration A configuration for the scanners camera.
 */
- (nonnull instancetype)initWithUIConfiguration:(nonnull SBSDKUIGenericDocumentRecognizerUIConfiguration *)uiConfiguration
                              textConfiguration:(nonnull SBSDKUIGenericDocumentRecognizerTextConfiguration *)textConfiguration
                          behaviorConfiguration:(nonnull SBSDKUIGenericDocumentRecognizerBehaviorConfiguration *)behaviorConfiguration
                            cameraConfiguration:(nonnull SBSDKUICameraConfiguration *)cameraConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * The default configuration.
 * @return A mutable instance of 'SBSDKUIGenericDocumentRecognizerConfiguration' with default values.
 */
+ (nonnull SBSDKUIGenericDocumentRecognizerConfiguration *)defaultConfiguration;

/** The configuration for the user interface. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIGenericDocumentRecognizerUIConfiguration *uiConfiguration;

/** The configuration for the displayed texts. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIGenericDocumentRecognizerTextConfiguration *textConfiguration;

/** The configuration for the behavior. */
@property (nonnull, nonatomic, strong, readonly) SBSDKUIGenericDocumentRecognizerBehaviorConfiguration *behaviorConfiguration;

@end


