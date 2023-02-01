//
//  SBSDKUIPageStoragePreviewImageCreator.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/26/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * A helper class to generate thumbnails from existing UIImage instances.
 */
@interface SBSDKUIPageStoragePreviewImageCreator : NSObject

/**
 * Creates a screen sized preview image from the given image. The final size is calculated using the main screens
 * bounds and its display scale.
 * @param originalImage The image from which a preview is generated.
 * @return The downsized preview image.
 */
+ (UIImage *)createScreenSizePreviewImageFromImage:(UIImage *)originalImage;

/**
 * Creates a custom-sized preview image from the given image.
 * @param originalImage The image from which a preview is generated.
 * @param sizeLength The proposed side length of the preview image.
 * @return The downsized preview image.
 */
+ (UIImage *)createPreviewImageFromImage:(UIImage *)originalImage withSideLength:(CGFloat)sizeLength;

@end
