//
//  SBSDKAutoSnappingMode.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 22.06.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The Auto-snapping mode handles different auto-snap scenarios.
 */
typedef NS_ENUM(NSUInteger, SBSDKAutosnappingMode) {
    /** Auto-snapping and user guidance are enabled. */
    SBSDKAutosnappingModeEnabled,
    /** Auto-snapping and user guidance are disabled. */
    SBSDKAutosnappingModeDisabled,
    /** Auto-snapping is disabled while user guidance is enabled. */
    SBSDKAutosnappingModeDisabledWithGuidance
};
