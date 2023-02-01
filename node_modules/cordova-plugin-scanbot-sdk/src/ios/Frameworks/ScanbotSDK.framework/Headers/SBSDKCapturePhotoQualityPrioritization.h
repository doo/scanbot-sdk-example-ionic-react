//
//  SBSDKPhotoQualityPriorization.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 27.10.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#ifndef SBSDKPhotoQualityPriorization_h
#define SBSDKPhotoQualityPriorization_h

#import <Foundation/Foundation.h>
/**
 * The priorization of still image quality and capturing speed. Has no effect on devices prior to iOS 13.0.
 */
typedef NS_ENUM(NSUInteger, SBSDKCapturePhotoQualityPrioritization) {
    /**
     * Captures a still image at the highest possible speed. The quality of the image may be degraded.
     */
    SBSDKCapturePhotoQualityPrioritizationSpeed = 1,

    /**
     * Balances capturing speed and image quality equally. This is the default value.
     */
    SBSDKCapturePhotoQualityPrioritizationBalanced = 2,
    
    /**
     * Captures a still image with the best possible quality in terms of noise, frozen motion and detail in low light.
     * The speed of the capturing might be significantly reduced.
     */
    SBSDKCapturePhotoQualityPrioritizationQuality = 3
};

#endif /* SBSDKPhotoQualityPriorization_h */
