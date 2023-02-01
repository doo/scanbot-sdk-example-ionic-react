//
//  SBSDKZoomingImageScrollView.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 18.02.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A scrollable and zoomable UIScrollView subclass that displays images and an overlay view.
 * Zooming and scrolling can be controlled using the standard UIScrollView properties.
 */
@interface SBSDKZoomingImageScrollView : UIScrollView<UIScrollViewDelegate>

/**
 * The image to be displayed. Can be zoomed and scrolled. If the image is zoomed out, it will be automatically centered.
 */
@property (strong, nonatomic, nullable) UIImage *image;

/**
 * The margins of the displayed image to the bounds of the receiver. Defaults to (20.0, 20.0, 20.0, 20.0).
 */
@property (assign, nonatomic) UIEdgeInsets margins;

/**
 * Pass a transparent view here to display it as a HUD style view above the image view.
 * If set, it will automatically be laid out to match the frame of the image view.
 * By default it is nil.
 */
@property (strong, nonatomic, nullable) UIView *overlayView;

@end

NS_ASSUME_NONNULL_END
