//
//  SBSDKTemperatureFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 25.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Adjusts the color temperature of an image.
 */
@interface SBSDKTemperatureFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of color temperature. Values range from -1.0 (cold, blue) to 1.0 (red, hot).
 */
@property(nonatomic, assign) float temperature;

@end

NS_ASSUME_NONNULL_END
