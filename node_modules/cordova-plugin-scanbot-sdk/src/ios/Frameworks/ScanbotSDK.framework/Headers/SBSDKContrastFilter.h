//
//  SBSDKContrastFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 22.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
* Adjusts the contrast of an image.
*/
@interface SBSDKContrastFilter : SBSDKBaseAdjustableFilter

/**
 * The amount of contrast to apply to the image. Valid values range from -1.0 (very low) to 1.0 (very high).
 */
@property(nonatomic, assign) float contrast;

@end

NS_ASSUME_NONNULL_END
