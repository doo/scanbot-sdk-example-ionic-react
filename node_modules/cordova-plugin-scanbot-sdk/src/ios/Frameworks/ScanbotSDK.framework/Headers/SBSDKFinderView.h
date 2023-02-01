//
//  SBSDKFinderView.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 03.05.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKFinderView;

/** The delegate protocol for the 'SBSDKFinderView' class. */
@protocol SBSDKFinderViewDelegate <NSObject>

/**
 * Informs the delegate, that the finder view has changed its finder rectangle.
 * @param view The finder view that changed its finder viewport rectangle. Can be nil, if it has been removed.
 * @param rect The new rectangle of the finder viewport.
 */
- (void)finderView:(nullable SBSDKFinderView *)view didChangeRect:(CGRect)rect;

@end

/**
 * A UIView subclass to display a view finder with colored background and transparent cutout with the given aspect ratio.
 */

@interface SBSDKFinderView : UIView

/** The receivers delegate. */
@property (nonatomic, weak, nullable) id<SBSDKFinderViewDelegate> finderDelegate;

/**
 * The aspect ratio of the viewport (cutout), if set to -1, no cutout is drawn. Defaults to -1.
 */
@property (nonatomic, assign) double displayedAspectRatio;

/**
 * The  aspect ratio of the secondary viewport drawn with dashed lines, if set to -1, no secondary viewport is drawn. 
 * Defaults to -1.
 */
@property (nonatomic, assign) double secondaryAspectRatio;

/**
 * Parameter that defines minimum inset of viewport from edge of the screen. The default value is {20, 20, 20, 20}.
 */
@property (nonatomic, assign) UIEdgeInsets minimumInset;

/**
 * Minimum inset of the secondary viewport, related to the primary viewport. The default value is {10, 10, 10, 10}. 
 */
@property (nonatomic, assign) UIEdgeInsets secondaryMinimumInset;

/**
 * If positive, the receiver will try to maintain the preferred height and the aspect ratio for the finder by dynamically
 * changing the inset. If negative this property will be ignored. The default value is -1;
 */
@property (nonatomic, assign) CGFloat preferredHeight;

/**
 * The color of the receivers border line. Can be nil.
 */
@property (nonatomic, strong, nullable) UIColor *lineColor;

/**
 * The corner radius of the receivers border line. Defaults to 8.
 */
@property (nonatomic, assign) CGFloat lineCornerRadius;

/**
 * The line width of the receivers border line. Defaults to 2.
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 * Set to YES for animated finder changes, to NO otherwise. Defaults to YES.
 */
@property (nonatomic, assign, getter=isAnimatingChanges) BOOL animateChanges;

/**
 * The current rect of the finders viewport in local coordinate system. Returns CGRectZero if the viewport is disabled.
 */
@property (nonatomic, readonly) CGRect finderRect;

/**
 * The current rect of the finders secondary viewport in local coordinate system.
 * Returns CGRectZero if the secondary viewport is disabled.
 */
@property (nonatomic, readonly) CGRect secondaryFinderRect;

/**
 * A function, that returns a rect of a finder, if it will be placed in view with certain bounds, with given aspect ratio and insets.
 * Useful for pre-calculations in some animation cases.
 * @param bounds The bounds of the view, where potential view will be placed.
 * @param aspectRatio An expected aspect ratio.
 * @param minimumInsets Minimal insets of finder.
 * @return A calculated rect of potential finder.
 */
+ (CGRect)potentialFinderRectWithBounds:(CGRect)bounds
                            aspectRatio:(double)aspectRatio
                          minimumInsets:(UIEdgeInsets)minimumInsets;


@end

NS_ASSUME_NONNULL_END
