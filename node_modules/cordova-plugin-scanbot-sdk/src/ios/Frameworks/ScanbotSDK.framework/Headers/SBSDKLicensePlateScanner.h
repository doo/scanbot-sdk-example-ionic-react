//
//  SBSDKLicensePlateScanner.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.02.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "SBSDKLicensePlateScannerResult.h"
#import "SBSDKLicensePlateScannerConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class to scan a vehicle's license plate in a UIImage or SampleBufferRef and run a validation on the result.
 * Ideally you use an instance of this class on subsequent video frames. Each scanned frame will raise the
 * confidence of the scan.
 */
@interface SBSDKLicensePlateScanner: NSObject

/**
 * The configuration of the license plate scanner.
 * Can be set at any time.
 */
@property(nonnull, nonatomic, strong) SBSDKLicensePlateScannerConfiguration *configuration;

/** Unavailable. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param configuration The configuration of the license plate scanner.
 * @return A newly created instance of the class.
 */
- (instancetype)initWithConfiguration:(SBSDKLicensePlateScannerConfiguration *)configuration;

/**
 * The actual scan function. Scans a CMSampleBufferRef as received by AVFoundations camera API for a license
 * plate and accumulates the result.
 * @param sampleBufferRef The sample buffer reference.
 * @param videoOrientation Video frame orientation. Should be the orientation that the device currently has, not actual image orientation.
 * @param rect Rectangle in image coordinates in which to perform the scan. Must be within the boundaries of the video frame.
 * @return The result of the scan.
  */
- (nullable SBSDKLicensePlateScannerResult *)scanSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                  orientation:(AVCaptureVideoOrientation)videoOrientation
                                                       inRect:(CGRect)rect;

/**
 * The actual scan function. Scans a UIImage representation of a camera video frame for a license
 * plate and accumulates the result.
 * @param image The orientation corrected image to scan.
 * @param rect Rectangle in image coordinates in which to perform the scan. Must be within the boundaries of the video frame.
 * @return The result of the scan.
 *
 * Caution: This function is not for scanning single images.
  */
- (nullable SBSDKLicensePlateScannerResult *)scanVideoFrameImage:(UIImage *)image inRect:(CGRect)rect;

/** Cleans the video frame accumulator. This basically resets the scanner to start a new scan. */
- (void)clearFrameAccumulator;

@end

NS_ASSUME_NONNULL_END
