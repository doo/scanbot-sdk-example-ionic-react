//
//  SBSDKVibranceFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 22.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Adjusts the vibrance of an image. Vibrance makes colors more brilliant.
 */
@interface SBSDKVibranceFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of vibrance to apply to the image. Valid values range from -1.0 (less brilliant) to 1.0 (very brilliant).
 */
@property(nonatomic, assign) float vibrance;

@end

NS_ASSUME_NONNULL_END
