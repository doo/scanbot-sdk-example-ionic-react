//
//  UIImageSBSDK.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 29.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SBSDKAspectRatio.h"

/**
 * @category UIImage(SBSDK)
 * An UIImage class extension to perform basic image processing operations.
 * Direct usage is not recommended for large images. Instead use SBSDKImageProcessor methods to employ
 * queues and proper memory management.
 */
@interface UIImage(SBSDK)

/**
 * Creates a UIImage instance from a pixel buffer.
 */
- (nullable id)sbsdk_initFromPixelBuffer:(nonnull CVPixelBufferRef)sampleBuffer;

/**
 * Creates a UIImage instance from a sample buffer.
 */
- (nullable id)sbsdk_initFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer;

/**
 * Converts a CVPixelBufferRef to an UIImage.
 * @param pixelBuffer The pixel buffer to convert.
 * @return An UIImage.
 */
+ (nullable UIImage *)sbsdk_imageFromPixelBuffer:(nonnull CVPixelBufferRef)pixelBuffer;

/**
 * Converts a CMSampleBuffer to an UIImage.
 * @param sampleBuffer The sample buffer to convert.
 * @return An UIImage.
 */
+ (nullable UIImage *)sbsdk_imageFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer;

/**
* Converts a CVPixelBufferRef to an UIImage.
* @param pixelBuffer The pixel buffer to convert.
* @param orientation The AVFoundation video orientation.
* @return An UIImage.
*/
+ (nullable UIImage *)sbsdk_imageFromPixelBuffer:(nonnull CVPixelBufferRef)pixelBuffer
                                     orientation:(AVCaptureVideoOrientation)orientation;

/**
 * Converts a CMSampleBuffer to an UIImage.
 * @param sampleBuffer The sample buffer to convert.
 * @param orientation The AVFoundation video orientation.
 * @return An UIImage.
 */
+ (nullable UIImage *)sbsdk_imageFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                      orientation:(AVCaptureVideoOrientation)orientation;

/**
 * Creates an UIImage of a given size and color.
 * @param color The color to fill the image with.
 * @param size The size of the image.
 * @return The resulting image.
 */
+ (nullable UIImage *)sbsdk_imageWithColor:(nonnull UIColor *)color andSize:(CGSize)size;

/**
 * Applies clockwise 90 degree rotations to the receiver.
 * @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 * @return The rotated UIImage.
 */
- (nullable UIImage *)sbsdk_imageRotatedClockwise:(NSInteger)times;

/**
 * Applies counter-clockwise 90 degree rotations to the receiver.
 * @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 * @return The rotated UIImage.
 */
- (nullable UIImage *)sbsdk_imageRotatedCounterClockwise:(NSInteger)times;

/**
 * Rotates the receiver for the given angle.
 * @return The rotated image.
 */
- (nullable UIImage *)sbsdk_imageRotatedByDegrees:(CGFloat)degrees;

/**
 * Rotates the receiver and corrects the orientation flag to UIImageOrientationUp.
 * @return The orientation fixed image.
 */
- (nullable UIImage *)sbsdk_imageWithNormalizedOrientation;

/**
 * Scales the receiver to the given size.
 * @return The rescaled image.
 */
- (nullable UIImage *)sbsdk_imageScaledToSize:(CGSize)size;

/**
 * Resets the orientation flag to UIImageOrientationUp without rotating the image data.
 * @return Image with modified orientation metadata.
 */
- (nullable UIImage *)sbsdk_imageWithFixedOrientation;

/**
 * Strips the alpha channel from an image.
 * @return The image without alpha channel.
 */
- (nullable UIImage *)sbsdk_imageWithStrippedAlpha;

/**
 * Inverts the colors of the receiver.
 * @return The inverted image.
 */
- (nullable UIImage *)sbsdk_invertedImage;

/**
 * Scales down the image to fit into the given size. Does no upscaling.
 * Does nothing, if width or height equal to zero.
 */
- (nullable UIImage *)sbsdk_limitedToSize:(CGSize)imageSize;

/**
 * Returns a center crop of the receiver with the given aspect ratio.
 * @param ratio The aspect ratio of the requested crop.
 * @return The cropped image.
 */
- (nullable UIImage *)sbsdk_imageByCenterCroppingToAspectRatio:(nonnull SBSDKAspectRatio *)ratio;

/**
 * Checks, if the receiver is monochromatic (grayscale).
 * @return YES, if the image is monochromatic, NO otherwise.
 */
- (BOOL)sbsdk_isMonochrome;

/**
 * Converts the receiver to a monochromatic image with less memory usage.
 * @return The monochromatic image or nil, if the conversion failed.
 */
- (nullable UIImage *)sbsdk_grayscaledImage;

/**
 * Resets the orientation flag to UIImageOrientationUp without rotating the image data.
 * @return A new NSData instance containing jpeg image data with corrected metadata.
 */
+ (nullable NSData *)sbsdk_imageDataWithFixedOrientation:(nullable NSData *)imageData;

/**
 * Since the camera sensor is, orientationwise, fixed to the device, a captured images orientation depends
 * on the orientation of the device. This function calculates the number of counterclockwise rotations needed
 * for a captured image to rotate it to the upside-down orientation.
 * @param deviceOrientation The orientation of the device when the image was captured.
 * @return The number of counterclockwise rotations needed to 'unrotate' the image.
 */
+ (NSInteger)proposedCounterClockwiseRotationsForOrientation:(UIDeviceOrientation)deviceOrientation;

@end
