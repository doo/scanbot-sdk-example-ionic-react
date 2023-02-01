//
//  SBSDKCompoundFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 22.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import "SBSDKBaseAdjustableFilter.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A compound image filter to build a filter chain with minimal conversion and maximal performance.
 */
@interface SBSDKCompoundFilter : SBSDKBaseAdjustableFilter

/** Use initWithFilters. */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Designated initializer. 
 * @param filters An array of specific filters to chain together. The order of execution equals the order of the filters
 * in the array.
 */
- (instancetype)initWithFilters:(NSArray<SBSDKBaseAdjustableFilter *> *)filters;

@end

NS_ASSUME_NONNULL_END
