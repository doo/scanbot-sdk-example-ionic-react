//
//  SBSDKSaturationFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 22.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
* Adjusts the saturation of an image.
*/
@interface SBSDKSaturationFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of saturation to apply to the image. Valid values range from -1.0 (desaturated) to 1.0 (very high).
 */
@property(nonatomic, assign) float saturation;

@end

NS_ASSUME_NONNULL_END
