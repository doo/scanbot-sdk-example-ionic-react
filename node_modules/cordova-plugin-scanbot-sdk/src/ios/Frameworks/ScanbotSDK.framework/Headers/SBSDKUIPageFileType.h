//
//  SBSDKUIPageFileType.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/25/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#ifndef SBSDKUIPageFileType_h
#define SBSDKUIPageFileType_h

/** Enumeration of image type classifiers. **/
typedef NS_ENUM(NSInteger, SBSDKUIPageFileType) {
    /** The image is the uncropped full image that was captured from the camera. */
    SBSDKUIPageFileTypeOriginal,
    
    /** The image only contains the cropped and perspective-corrected document portion of the original camera image. */
    SBSDKUIPageFileTypeDocumentUnfiltered,
    
    /** The image contains the cropped, perspective-corrected and filtered document portion of the original camera image. */
    SBSDKUIPageFileTypeDocument
};

#endif /* SBSDKUIPageFileType_h */
