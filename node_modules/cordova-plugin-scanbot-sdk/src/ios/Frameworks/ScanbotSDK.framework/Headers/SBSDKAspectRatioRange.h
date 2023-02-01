//
//  SBSDKAspectRatioRange.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 27.01.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKAspectRatio.h"

NS_ASSUME_NONNULL_BEGIN

/** A class that represents a range of aspect ratios. **/
@interface SBSDKAspectRatioRange : NSObject
/** Minimum aspect ratio. **/
@property(nonatomic, strong, readonly) SBSDKAspectRatio *minimumAspectRatio;

/** Maximum aspect ratio. **/
@property(nonatomic, strong, readonly) SBSDKAspectRatio *maximumAspectRatio;

/**
 * Designated initializer. It takes two aspect ratio and compares them to get minimum and maximum ones.
 * @param aspectRatio1 First aspect ratio.
 * @param aspectRatio2 Second aspect ratio.
 */
- (instancetype)initWithAspectRatio1:(SBSDKAspectRatio *)aspectRatio1
                        aspectRatio2:(SBSDKAspectRatio *)aspectRatio2;

/**
 * Not available.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Checks wether the given aspect ratio is within the bounds of the receiver
 * @param aspectRatio The aspect ratio to be checked for containment.
 * @return YES, if the aspect ration is within the bounds of the receiver. NO otherwise.
 */
- (BOOL)containsAspectRatio:(SBSDKAspectRatio *)aspectRatio;

@end

NS_ASSUME_NONNULL_END
