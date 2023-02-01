//
//  SBSDKBaseScannerZoomConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 20.07.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKZoomRange.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The zoom configuration object for a 'SBSDKBaseScannerViewController' and its subclasses.
 * 'SBSDKBaseScannerViewController' and subclasses allow the user to zoom the camera.
 * This class lets you customize the zooming user experience.
 */
@interface SBSDKBaseScannerZoomConfiguration : NSObject

/**
 * The range (min and max factor) of the cameras zoom factor. Default value is (1.0; 3.0).
 */
@property(nullable, nonatomic, strong) SBSDKZoomRange *zoomRange;

/**
 * The initial zoom factor. Must be in the range of (0.0 - 1.0), where 0.0 equals to the lower limit of zoomRange and
 * 1.0 equals to the upper limit of zoomRange. Default value is 0.0. 
 */
@property(nonatomic, assign) CGFloat initialZoomFactor;

/**
 * When this property is set to YES, the zoom can be toggled between the minimum and maximum zoom factor, defined in
 * the zoomRange property, by just double-tapping anywhere in the base scanner view controllers view.
 * If set to NO, zooming by double-tapping will be disabled.
 * Defaults to YES.
 */
@property(nonatomic, assign, getter=isDoubleTapToZoomEnabled) BOOL doubleTapToZoomEnabled;

/**
 * When this property is set to YES, the camera zoom can be controlled by a pinch gesture
 * anywhere in the base scannner view controllers view.
 * If set to NO, zooming by pinching will be disabled.
 * Defaults to YES.
 */
@property(nonatomic, assign, getter=isPinchToZoomEnabled) BOOL pinchToZoomEnabled;

/**
 * Defines, if zooming in or out should be animated. This applies to double-tap zooming as well as to programmatically
 * triggered zooms.
 * Defaults to YES.
 */
@property (nonatomic, assign) BOOL shouldAnimateZooming;

/**
 * This is the default configuration with the properties initialized as mentioned in their description.
 * @return The default zoom configuration object which can be changed and then passed back to the
 * base scanner view controller.
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
