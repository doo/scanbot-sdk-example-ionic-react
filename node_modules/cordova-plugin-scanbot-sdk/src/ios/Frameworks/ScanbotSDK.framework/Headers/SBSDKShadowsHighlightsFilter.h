//
//  SBSDKShadowsHighlightsFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 25.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A filter that separately adjusts the contrast of darker and brighter image areas.
 */
@interface SBSDKShadowsHighlightsFilter : SBSDKBaseAdjustableFilter

/**
 * The highlights value. Affects the contrast in bright image areas.
 * Values range from -1.0 (lowers contrast in bright areas) to 1.0 (raises contrast in bright areas).
 */
@property(nonatomic, assign) float highlights;

/**
 * The shadows value. Affects the contrast in dark image areas.
 * Values range from -1.0 (raises contrast in dark areas) to 1.0 (lowers contrast in bright areas).
*/
@property(nonatomic, assign) float shadows;

@end

NS_ASSUME_NONNULL_END
