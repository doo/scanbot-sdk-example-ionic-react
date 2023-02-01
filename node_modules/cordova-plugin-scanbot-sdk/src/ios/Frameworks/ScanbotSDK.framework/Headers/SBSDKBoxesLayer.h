//
//  SBSDKBoxesLayer.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 03.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKBoxedObject.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A CAShapeLayer subclass to draw rectangles to mark detected objects.
 */
@interface SBSDKBoxesLayer : CAShapeLayer

/**
 * The boxes to display.
 */
@property (nonatomic, strong) NSArray<id<SBSDKBoxedObject>> *boxes;

/**
 * The color to draw the boxes outlines.
 */
@property (nonatomic, strong, nonnull) UIColor *lineColor;

/**
 * The color to fill the boxes with. Defaults to clear color.
 */
@property (nonatomic, strong, nonnull) UIColor *boxFillColor;


/**
 * The corner radius for the drawn boxes. Defaults to 4.0f;
 */
@property (nonatomic, assign) CGFloat boxCornerRadius;

/**
 * A transform for the boxes drawing. Defaults to identity.
 */
@property (nonatomic, assign) CGAffineTransform drawingTransform;

/**
 * Designated initializer.
 * @param boxes The boxes as NSValue encoded NSRects.
 * @param lineColor The initial color for the boxes outline color.
 * @param fillColor The initial color for the boxes fill color.
 */
- (nonnull instancetype)initWithBoxes:(NSArray<id<SBSDKBoxedObject>> *)boxes
                            lineColor:(UIColor *)lineColor
                         boxFillColor:(UIColor *)fillColor;

@end

NS_ASSUME_NONNULL_END
