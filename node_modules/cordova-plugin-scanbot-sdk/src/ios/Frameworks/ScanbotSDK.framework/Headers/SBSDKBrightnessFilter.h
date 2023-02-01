//
//  SBSDKBrightnessFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 21.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Adjusts the brightness of an image.
 */
@interface SBSDKBrightnessFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of brightness to apply to the image. Valid values range from -1.0 (very dark) to 1.0 (very bright).
 */
@property(nonatomic, assign) float brightness;

@end

NS_ASSUME_NONNULL_END
