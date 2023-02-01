//
//  SBSDKVideoContentMode.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/18/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#ifndef SBSDKVideoContentMode_h
#define SBSDKVideoContentMode_h

/** Enumeration of video preview content mode. */
typedef NS_ENUM(NSInteger, SBSDKVideoContentMode) {
    /**
     * The video layers content is filled into the video layer.
     * No visible borders. Video may be cropped to the visible screen area.
     */
    SBSDKVideoContentModeFillIn,
    
    /**
     * The video layers content is fit into the video layer.
     * Video may have visible borders. Video is fully visible within the screen.
     */
    SBSDKVideoContentModeFitIn
};

#endif /* SBSDKVideoContentMode_h */
