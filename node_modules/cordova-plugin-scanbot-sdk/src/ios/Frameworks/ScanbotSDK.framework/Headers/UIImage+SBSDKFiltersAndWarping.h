//
//  UIImage+SBSDKFiltersAndWarping.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 01.02.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKLensCameraProperties.h"
#import "SBSDKImageFilterTypes.h"
#import "SBSDKPolygon.h"

/**
 * @category UIImage(SBSDK)
 * An UIImage class extension to perform image filtering and warping processing.
 * Direct usage is not recommended for large images. Instead use SBSDKImageProcessor methods to employ
 * queues and proper memory management.
 */
@interface UIImage (SBSDKFiltersAndWarping)

/**
 * Applies a filter to the receiver and returns the filtered image.
 * @param filter The type of the filter to be applied.
 * @return The filtered UIImage.
 */
- (nullable UIImage *)sbsdk_imageFilteredByFilter:(SBSDKImageFilterType)filter;

/**
 * Applies a polygon to the receiver and returns the cropped and perspective corrected image.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The cropped and perspective corrected UIImage.
 */
- (nullable UIImage *)sbsdk_imageWarpedByPolygon:(nonnull SBSDKPolygon *)polygon imageScale:(CGFloat)imageScale;

/**
 * Applies a polygon to the receiver and returns the cropped and perspective corrected image.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param lensCameraProperties Properties of the camera which captured the image or nil.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The cropped and perspective corrected UIImage.
 */
- (nullable UIImage *)sbsdk_imageWarpedByPolygon:(nonnull SBSDKPolygon *)polygon
                            lensCameraProperties:(nullable SBSDKLensCameraProperties *)lensCameraProperties
                                      imageScale:(CGFloat)imageScale;

/**
 * Applies a polygon and a filter to the receiver. Faster than two sequential operations.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param filter The type of the filter to be applied.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The cropped and perspective corrected UIImage.
 */
- (nullable UIImage *)sbsdk_imageWarpedByPolygon:(nonnull SBSDKPolygon *)polygon
                                   andFilteredBy:(SBSDKImageFilterType)filter
                                      imageScale:(CGFloat)imageScale;

/**
 * Applies a polygon and a filter to the receiver. Faster than two sequential operations.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param filter The type of the filter to be applied.
 * @param lensCameraProperties Properties of the camera which captured the image or nil.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The cropped and perspective corrected UIImage.
 */
- (nullable UIImage *)sbsdk_imageWarpedByPolygon:(nonnull SBSDKPolygon *)polygon
                                   andFilteredBy:(SBSDKImageFilterType)filter
                            lensCameraProperties:(nullable SBSDKLensCameraProperties *)lensCameraProperties
                                      imageScale:(CGFloat)imageScale;


/**
 * Applies counter-clockwise 90 degree rotations, polygon warping and filtering to the receiver and returns a
 * JPEG UIImage with given compression/quality.
 * @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param filter The type of the filter to be applied.
 * @param compression The JPEG compression/quality setting.
 * Range is 0.0 (low quality, small file) to 1.0 (high quality, large file).
 * @param lensCameraProperties Properties of the camera which captured the image or nil.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The processed UIImage.
 */
- (nullable UIImage *)sbsdk_imageByProcessingWithRotations:(NSInteger)times
                                                   polygon:(nullable SBSDKPolygon *)polygon
                                                    filter:(SBSDKImageFilterType)filter
                                               compression:(CGFloat)compression
                                      lensCameraProperties:(nullable SBSDKLensCameraProperties *)lensCameraProperties
                                                imageScale:(CGFloat)imageScale;

/**
 * Applies counter-clockwise 90 degree rotations, polygon warping and filtering to the receiver and returns
 * JPEG image data with given compression/quality.
 * @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 * @param polygon The polygon used to crop and perspective correct the image.
 * @param filter The type of the filter to be applied.
 * @param compression The JPEG compression/quality setting.
 * Range is 0.0 (low quality, small file) to 1.0 (high quality, large file).
 * @param lensCameraProperties Properties of the camera which captured the image or nil.
 * @param imageScale If the image has been scaled, compared to how it was captured from the camera,
 * you must set the scaling factor here for proper cropping. Otherwise the the resulting aspect ratio will be wrong.
 * Set to 1.0 if the image if of its original size.
 * @return The JPEG data of the processed image.
 */
- (nullable NSData *)sbsdk_imageDataByProcessingWithRotations:(NSInteger)times
                                                      polygon:(nullable SBSDKPolygon *)polygon
                                                       filter:(SBSDKImageFilterType)filter
                                                  compression:(CGFloat)compression
                                         lensCameraProperties:(nullable SBSDKLensCameraProperties *)lensCameraProperties
                                                   imageScale:(CGFloat)imageScale;


/**
 * Applies the an image filter to the receiver and returns JPEG image data with given compression/quality.
 * @param filter The type of the filter to be applied.
 * @param compression The JPEG compression/quality setting.
 * Range is 0.0 (low quality, small file) to 1.0 (high quality, large file).
 * @return The JPEG data of the processed image.
 */
- (nullable NSData *)sbsdk_imageDataByApplyingFilter:(SBSDKImageFilterType)filter compression:(CGFloat)compression;

@end
