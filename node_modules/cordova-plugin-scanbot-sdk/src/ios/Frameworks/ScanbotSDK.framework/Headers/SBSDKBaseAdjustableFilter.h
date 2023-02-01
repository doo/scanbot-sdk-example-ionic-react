//
//  SBSDKBaseAdjustableFilter.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 21.02.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** An enum describing the various modes used to apply an adjustable filter. */
typedef NS_ENUM(NSInteger, SBSDKFilterMethod) {

    /** Automatically selects the fastest available method for filtering. */
    SBSDKFilterMethodAuto,
    
    /** Uses the CPU to run a filter on an image. Slowest option. */
    SBSDKFilterMethodCPU,

    /** Uses the GPU with Apple Metal to run a filter on an image. Fastest option. */
    SBSDKFilterMethodGPUMetal
};

/**
 * This is the abstract base class for any of the adjustable filters in ScanbotSDK.
 * It provides the basic logic for filtering images using the GPU or the CPU.
 * For GPU-based filtering the SDK uses preferrably Apples Metal API where available and falls back
 * to OpenGLES if Metal is not available. If GPU-based filtering is not supported at all, the slower CPU-based
 * filtering is used.
 */
@interface SBSDKBaseAdjustableFilter : NSObject

/**
 * Tests if the provided filtering method is supported on the device.
 * @param method The method to check.
 * @return YES, if the method is supported by the device, NO otherwise.
 */
- (BOOL)canUseMethod:(SBSDKFilterMethod)method;

/**
* Runs the filter on the given image. Automatically uses the fastest available filtering method: Metal > OpenGLES > CPU
* @param inputImage The image to be filtered.
* @return The filtered image.
*/
- (nullable UIImage *)runFilterOnImage:(UIImage *)inputImage;

/**
* Runs the filter on the given image.
* @param inputImage The image to be filtered.
* @param method The preferred method to use. If the filter method is not supported by the supported by the device it
* automatically selects the fastest available filtering method: Metal > OpenGLES > CPU.
* @return The filtered image.
*/
- (nullable UIImage *)runFilterOnImage:(UIImage *)inputImage preferredMethod:(SBSDKFilterMethod)method;

@end

NS_ASSUME_NONNULL_END
