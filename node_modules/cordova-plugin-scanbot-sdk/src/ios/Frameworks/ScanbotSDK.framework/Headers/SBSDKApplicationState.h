//
//  SBSDKApplicationState.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 14.09.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#ifndef SBSDKApplicationState_h
#define SBSDKApplicationState_h

#import <Foundation/Foundation.h>

/**
 * An enum describing the current state of the app.
 */
typedef enum : NSUInteger {
    /** The app is active and in foreground. */
    SBSDKApplicationStateActive,
    
    /** The app is inactive and in background. */
    SBSDKApplicationStateInactive,
    
    /** The app is in background. */
    SBSDKApplicationStateBackground,

} SBSDKApplicationState;

#endif /* SBSDKApplicationState_h */
