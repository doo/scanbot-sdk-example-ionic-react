//
//  SBSDKOrientationLock.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/30/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#ifndef SBSDKOrientationLock_h
#define SBSDKOrientationLock_h

#import "UIKit/UIKit.h"

/**
 * This enum describes the available orientation lock modes for the user interface.
 * Captured images are always top-oriented to the status bar.
 */
typedef NS_ENUM(NSInteger, SBSDKOrientationLock) {
    
    /**
     * The orientation is not locked. The captured image is orientated so that the
     * upper area of the image is directed towards the status bar.
     * The image either has a landscape or portrait aspect ratio.
     */
    SBSDKOrientationLockNone = 0,
    
    /**
     * The orientation is locked to the portrait modes. The captured image is orientated so that the
     * upper area of the image is directed towards the status bar. The image always
     * has a portrait aspect ratio.
     */
    SBSDKOrientationLockPortrait = 1,
    
    /**
     * The orientation is locked to the landscape modes. The captured image is orientated so that the
     * upper area of the image is directed towards the status bar. The image always
     * has a landscape aspect ratio.
     */
    SBSDKOrientationLockLandscape = 2
};

inline static UIInterfaceOrientationMask orientationsFromLock(SBSDKOrientationLock mode) {
    switch(mode) {
        case SBSDKOrientationLockNone: 
            return UIInterfaceOrientationMaskAll;
            break;
        case SBSDKOrientationLockPortrait:
            return UIInterfaceOrientationMaskPortrait;
            break;
        case SBSDKOrientationLockLandscape:
            return UIInterfaceOrientationMaskLandscape;
            break;
    }
}

#endif /* SBSDKOrientationLock_h */
