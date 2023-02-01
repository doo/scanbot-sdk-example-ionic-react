//
//  SBSDKSmartFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 11.03.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"
#import "SBSDKImageFilterTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A wrapper around the more complex SBSDKImageFilterType based filters. Can be used to execute
 * SBSDKImageFilterType based filters at any place in a filter chain built from a SBSDKCompoundFilter.
 */
@interface SBSDKSmartFilter : SBSDKBaseAdjustableFilter

/** The SBSDKImageFilterType based filter to use. */
@property(nonatomic, assign) SBSDKImageFilterType filterType;

@end

NS_ASSUME_NONNULL_END
