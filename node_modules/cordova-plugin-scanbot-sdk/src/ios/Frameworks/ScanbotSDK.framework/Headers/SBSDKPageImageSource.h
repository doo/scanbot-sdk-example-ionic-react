//
//  SBSDKPageImageSource.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 16.08.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

/** The source from where the image of the page originated from. */
typedef NS_ENUM(NSInteger, SBSDKPageImageSource) {
    /**
     * Used by default. If the source is not defined
     */
    SBSDKPageImageSourceUndefined,
    /**
     * If the source image was captured manually. For example, when the user pressed a Snap button
     */
    SBSDKPageImageSourceManualSnap,
    /**
     * If the source image was captured automatically. For example, by auto snapping functions
     */
    SBSDKPageImageSourceAutoSnap,
    /**
     * If the source image was taken from the video frame
     */
    SBSDKPageImageSourceVideoFrame,
    /**
     * If the source image was imported from external source
     */
    SBSDKPageImageSourceImport
};
