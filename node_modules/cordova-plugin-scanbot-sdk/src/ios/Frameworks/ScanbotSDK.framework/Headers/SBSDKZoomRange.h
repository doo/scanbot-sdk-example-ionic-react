//
//  SBSDKZoomRange.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 14.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** Helper class to define a range for zooming. */
@interface SBSDKZoomRange: NSObject

/** The minimum zoom scale. Defaults to 1.0. */
@property (readonly) CGFloat minZoom;

/** The maximum zoom scale. Defaults to 3.0. */
@property (readonly) CGFloat maxZoom;

/**
 * Designated initializer.
 * @param minZoom The minimum zoom scale.
 * @param maxZoom The maximum zoom scale.
 */
- (instancetype)initWithMinZoom:(CGFloat)minZoom andMaxZoom:(CGFloat)maxZoom;

@end


NS_ASSUME_NONNULL_END
