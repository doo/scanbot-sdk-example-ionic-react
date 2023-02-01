//
//  SBSDKCaptureInfo.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 01.03.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKDocumentDetectorResult.h"
#import "SBSDKImageMetadata.h"
#import "SBSDKLensCameraProperties.h"
#import "SBSDKPageImageSource.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Helper class, that gathers the image, camera and detection metadata of a document scan.
 */
@interface SBSDKCaptureInfo : NSObject

/** The document detector result of the captured image. */
@property (nullable, nonatomic, readonly) SBSDKDocumentDetectorResult *detectionResult;

/** The image metadata of the captured image. */
@property (nonatomic, readonly) SBSDKImageMetadata *imageMetadata;

/** The lens and camera properties of the camera system the image was captured with. */
@property (nonatomic, readonly) SBSDKLensCameraProperties *lensCameraProperties;

/** Whether the image was captured automatically or manually triggered by the shutter button. */
@property (nonatomic, readonly) BOOL isCapturedAutomatically __attribute__((deprecated("Please use pageImageSource.")));

/** The source the image was received from. */
@property (nonatomic, readonly) SBSDKPageImageSource pageImageSource;

@end

NS_ASSUME_NONNULL_END
