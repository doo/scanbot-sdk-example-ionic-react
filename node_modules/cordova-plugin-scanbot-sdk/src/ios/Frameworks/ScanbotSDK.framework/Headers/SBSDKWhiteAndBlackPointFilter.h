//
//  SBSDKWhiteAndBlackPointFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 25.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A filter that maps the brightness values of the images to the given black and white points.
 */
@interface SBSDKWhiteAndBlackPointFilter : SBSDKBaseAdjustableFilter

/**
 * The white point offset. Affects the brighter pixels of the image.
 * Values range from -1.0 (darkens bright pixels) to 1.0 (brightens bright pixels).
 */
@property(nonatomic, assign) float whitePointOffset;

/**
* The black point offset. Affects the darker pixels of the image.
* Values range from -1.0 (darkens dark pixels) to 1.0 (brightens dark pixels).
*/
@property(nonatomic, assign) float blackPointOffset;

@end

NS_ASSUME_NONNULL_END
