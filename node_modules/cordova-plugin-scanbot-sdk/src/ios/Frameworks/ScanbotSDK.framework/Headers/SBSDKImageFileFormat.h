//
//  SBSDKImageFileFormat.h
//  ScanbotSDKDemo
//
//  Created by Yevgeniy Knizhnik on 3/5/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#ifndef SBSDKImageFileFormat_h
#define SBSDKImageFileFormat_h

/** Enumeration of supported image file types. */
typedef NS_ENUM(NSInteger, SBSDKImageFileFormat) {
    /** The image file is a PNG. */
    SBSDKImageFileFormatPNG,

    /** The image file is a JPEG. */
    SBSDKImageFileFormatJPEG
};

#endif /* SBSDKImageFileFormat_h */
