//
//  SBSDKSpecialContrastFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 25.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A contrast image filter that works with shifting white and black point.
 */
@interface SBSDKSpecialContrastFilter : SBSDKBaseAdjustableFilter

/**
* The amount of contrast. Values range from -1.0 (low contrast) to 1.0 (high contrast).
*/
@property(nonatomic, assign) float amount;

@end

NS_ASSUME_NONNULL_END
