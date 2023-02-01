//
//  SBSDKTintAdjustFilter.h
//  ScanbotSDKBeta
//
//  Created by Sebastian Husche on 29.11.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Adjusts the tint of an image.
 */
@interface SBSDKTintAdjustFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of color tinting. Values range from -1.0 (green tinted) to 1.0 (magenta tinted).
 */
@property(nonatomic, assign) float tint;

@end

NS_ASSUME_NONNULL_END
