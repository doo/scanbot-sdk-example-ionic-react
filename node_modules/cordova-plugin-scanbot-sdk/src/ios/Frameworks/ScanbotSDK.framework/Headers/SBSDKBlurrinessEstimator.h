//
//  SBSDKBlurrinessEstimator.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 17.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Class for image blurriness value estimation.
 */
@interface SBSDKBlurrinessEstimator : NSObject

/**
 * Estimate blurriness value on given UIImage instance
 * @param image Given image.
 * @return Estimation result. Closer to 0.0 - sharp, closer to 1.0 - blurred.
 */
- (double)estimateImageBlurriness:(nonnull UIImage *)image;

@end

NS_ASSUME_NONNULL_END
