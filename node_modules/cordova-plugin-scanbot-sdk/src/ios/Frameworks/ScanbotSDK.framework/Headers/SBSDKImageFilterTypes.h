//
//  SBSDKImageFilterTypes.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 09.05.14.
//  Copyright (c) 2014 doo. All rights reserved.
//

#ifndef SBSDK_IMAGE_FILTER_TYPES_H
#define SBSDK_IMAGE_FILTER_TYPES_H
/**
 The ScanbotSDK image filter types.
 */
typedef enum SBSDKImageFilterType : int {

    /** Passthrough filter. Does not alter the image. */
    SBSDKImageFilterTypeNone = 0,

    /** Optimizes colors, contrast and brightness. Usecase: photos. */
    SBSDKImageFilterTypeColor = 1,

    /** Standard grayscale filter. Creates a grayscaled 8-bit image and optimizes contrast and
       dynamic range. */
    SBSDKImageFilterTypeGray = 2,

    /** Standard binarization filter with contrast optimization.
     Creates a grayscaled 8-bit image with mostly black or white pixels.
     Usecase: Preparation for optical character recognition.
     */
    SBSDKImageFilterTypeBinarized = 3,

    /** Fixes white-balance and cleans up the background.
     Usecase: images of paper documents. */
    SBSDKImageFilterTypeColorDocument = 4,

    /** A filter for binarizing an image. Creates an 8-bit image with pixel
     values set to eiter 0 or 255.
     Usecase: Preparation for optical character recognition.
     */
    SBSDKImageFilterTypePureBinarized = 11,

    /** Cleans up the background and tries to preserve photos
     within the image. Usecase: magazine pages, flyers. */
    SBSDKImageFilterTypeBackgroundClean = 13,

    /** Black and white filter with background cleaning.
     Creates a grayscaled 8-bit image with mostly black or white pixels.
     Usecase: Textual documents or documents with black and white illustrations.
     */
    SBSDKImageFilterTypeBlackAndWhite = 14,

    /** A filter for black and white conversion using OTSU binarization. */
    SBSDKImageFilterTypeOtsuBinarization = 15,

    /** A filter for black and white conversion primary used for low-contrast documents. */
    SBSDKImageFilterTypeDeepBinarization = 16,

    /** A filter that enhances edges in low-contrast documents. */
    SBSDKImageFilterTypeEdgeHighlight = 17,

    /** Binarization filter primary inteded to use on low-contrast documents with heavy shadows. */
    SBSDKImageFilterTypeLowLightBinarization = 18,

    /** Binarization filter primary intended to use on low-contrast documents with heavy shadows. */
    SBSDKImageFilterTypeLowLightBinarization2 = 19,

    /** Binarization filter for poor quality printed papers. */
    SBSDKImageFilterTypeSensitiveBinarization = 20,

    /** Standard grayscale filter. Creates a grayscaled 8-bit image. */
    SBSDKImageFilterTypePureGray = 21,

} SBSDKImageFilterType;

#endif
