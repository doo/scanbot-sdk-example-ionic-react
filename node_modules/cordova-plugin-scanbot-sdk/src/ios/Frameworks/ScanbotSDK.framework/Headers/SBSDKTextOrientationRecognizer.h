//
//  SBSDKTextOrientationRecognizer.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 12/4/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * The ScanbotSDK text orientation types.
 */
typedef NS_ENUM(NSInteger, SBSDKTextOrientation) {

    /** Text orientation was not recognized (bad image quality, etc). */
    SBSDKTextOrientationNotRecognized = -2,
    
    /** Text were recognized, but the confidence of recognition is too low. **/
    SBSDKTextOrientationLowConfidence = -1,
    
    /** Text is not rotated. */
    SBSDKTextOrientationNormal = 0,
    
    /** Text is rotated 90 degrees clockwise. */
    SBSDKTextOrientationRotated90 = 90,
    
    /** Text is rotated 180 degrees clockwise. */
    SBSDKTextOrientationRotated180 = 180,
    
    /** Text is rotated 270 degrees clockwise. */
    SBSDKTextOrientationRotated270 = 270,
    
};

/**
 * A class, that determines orientation of text on the image.
 * Initialization of this class can be resource-intensive, so in case you want to analyze multiple images,
 * it is better to create instance of SBSDKTextOrientationRecognizer once and use it multiple times.
 */
@interface SBSDKTextOrientationRecognizer : NSObject

/**
 * Synchronously recognizes text orientation on the image.
 * @param image An image to recognize text on it.
 * @return A SBSDKTextOrientation containing the result of the orientation recognition.
 */
- (SBSDKTextOrientation)textOrientationForImage:(UIImage *)image;

/**
 * Synchronously recognizes text orientation on the image.
 * @param image An image to recognize text on it.
 * @param requestedConfidence Minimum confidence level of orientation recognition. A value of 2 is a good quality.
 * If the confidence of recognition will be lower, then confidence parameter, `SBSDKTextOrientationLowConfidence` will
 * be returned. Setting it to 0 or lower will be the same, as calling `getTextOrientationForImage:`.
 * @return A SBSDKTextOrientation containing the result of the orientation recognition.
 */
- (SBSDKTextOrientation)textOrientationForImage:(UIImage *)image withConfidence:(float)requestedConfidence;

@end
