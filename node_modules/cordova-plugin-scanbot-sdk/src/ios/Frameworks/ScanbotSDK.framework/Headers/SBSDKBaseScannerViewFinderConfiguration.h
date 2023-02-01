//
//  SBSDKBaseScannerViewFinderConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 13.09.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKAspectRatio.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The view finder configuration object for a 'SBSDKBaseScannerViewController' and its subclasses.
 * Sometimes it is necessary to limit a live video frame detection or recognition to a certain rectangular area with
 * a specific aspect ratio: the region or rectangle of interest. This is where a view finder comes in.
 * It crops the video frame to that region of interest before passing it to any detector or recognizer. Usually
 * the performance of detectors/recognizers gain a benefit from it because less pixels must be processed.
 * Additionally, to guide the user, the view finder visualizes the region of interest by drawing a rectangle around
 * on the user interface.
 *
 * Since the display resp. the camera view size differs from device to device specifying the region of interest
 * in absolute screen points would require some additional calculations and therefore be inconvenient.
 * Instead a combination of aspect ratio and minimum distances to the view(screen) edges is used.
 */
@interface SBSDKBaseScannerViewFinderConfiguration : NSObject

/**
 * Set to YES to enable and display the region of interest, to NO otherwise.
 * Defaults to NO.
 */
@property(nonatomic, assign, getter=isViewFinderEnabled) BOOL viewFinderEnabled;

/**
 * The aspect ratio of the region of interest. Defaults to 4:3.
 */
@property (nonatomic, strong, nonnull) SBSDKAspectRatio *aspectRatio;

/**
 * The minimum space from view finders outer edges to the view/screen edges.
 * The default value is {20, 20, 20, 20}.
 */
@property (nonatomic, assign) UIEdgeInsets minimumInset;

/**
 * If positive, the receiver will try to maintain the preferred height and the aspect ratio for the finder by dynamically
 * changing the inset. If negative this property will be ignored. The default value is -1;
 */
@property (nonatomic, assign) CGFloat preferredHeight;

/**
 * The aspect ratio of the secondary view finder that is displayed with dashed lines. 
 * If set to nil no secondary view finder is drawn.
 * Defaults to nil.
 */
@property (nonatomic, strong, nullable) SBSDKAspectRatio *secondaryAspectRatio;

/**
 * The minimum space from the primary view finder to the secondary view finder for each edge.
 * Defaults to 10 for the top, left, bottom and right edge.
 */
@property (nonatomic, assign) UIEdgeInsets secondaryMinimumInset;

/**
 * The line color of the view finders outline. Can be nil to not display the outline.
 * Defaults to a fully opaque white color.
 */
@property (nonatomic, strong, nullable) UIColor *lineColor;

/**
 * The color of the background outside the view finders outline. Use this color to mask the region
 * that is not of interest.
 * Defaults to a black color with an opacity of 0.66, slightly darkening the non-interest area of the screen.
 */
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

/**
 * The corner radius of the view finders outline.
 * Defaults to 8 points.
 */
@property (nonatomic, assign) CGFloat lineCornerRadius;

/**
 * The line width of the view finders outline.
 * Defaults to 2 points.
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 * Set to YES to animate the view finder when changing the aspect ratio or minimum insets,
 * to NO if changes should not be animated.
 */
@property (nonatomic, assign, getter=isAnimatingChanges) BOOL animateChanges;

/** The visual effect applied to the area outside the view finder. If nil, no effect is applied. Defaults to nil. */
@property (nonatomic, strong, nullable) UIVisualEffect *backgroundEffect;

/**
 * This is the default configuration with the properties initialized as mentioned in their description.
 * @return The default view finder configuration object which can be changed and then passed back to the
 * base scanner view controller.
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
