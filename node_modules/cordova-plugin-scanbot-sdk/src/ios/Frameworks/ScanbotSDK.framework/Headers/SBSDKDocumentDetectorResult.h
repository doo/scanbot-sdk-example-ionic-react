//
//  SBSDKDocumentDetectorResult.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.04.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKPolygon.h"
#import "SBSDKDocumentDetectionStatus.h"
#import "SBSDKDocumentDetectionMetrics.h"

/**
 * This class represents the result of a document detection on an image.
 */
@interface SBSDKDocumentDetectorResult : NSObject<NSCopying>

/** The status of the detection. */
@property(nonatomic, readonly) SBSDKDocumentDetectionStatus status;

/** The detected polygon or nil, if no polygon was detected. */
@property(nonatomic, readonly, nullable) SBSDKPolygon *polygon;

/** The metrics of the detection. **/
@property(nonatomic, readonly, nullable) SBSDKDocumentDetectionMetrics *metrics;

/** The size of the detector input image. For convenience. */
@property(nonatomic, readonly) CGSize detectorImageSize;

/**
 * Is YES, if the receiver has one of the following states:
 * SBSDKDocumentDetectionStatusOK, SBSDKDocumentDetectionStatusOK_SmallSize, SBSDKDocumentDetectionStatusOK_BadAngles,
 * SBSDKDocumentDetectionStatusOK_BadAspectRatio or SBSDKDocumentDetectionStatusOK_OffCenter.
 * Otherwise it is NO.
 */
@property(nonatomic, readonly) BOOL isDetectionStatusOK;

@end
