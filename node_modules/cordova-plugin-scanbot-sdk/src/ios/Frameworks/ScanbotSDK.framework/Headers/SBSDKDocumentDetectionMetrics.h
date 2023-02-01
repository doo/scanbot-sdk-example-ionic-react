//
//  SBSDKDocumentDetectionMetrics.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.10.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import "SBSDKAspectRatio.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The metrics and additional properties returned by 'SBSDKDocumentDetector'.
 * Can be used to make decisions on polygon acceptance, automatic capturing and user guidance.
 **/
@interface SBSDKDocumentDetectionMetrics: NSObject<NSCopying>
/** The total score of the detected polygon (0 - 100). */
@property(readonly) double totalScore;

/** The size score of the detected polygon (0 - 100). Part of the total score. */
@property(readonly) double sizeScore;

/** The width score of the detected polygon (0 - 100). Part of the size score. */
@property(readonly) double widthScore;

/** The height score of the detected polygon (0 - 100). Part of the size score. */
@property(readonly) double heightScore;

/** The angles score of the detected polygon (0 - 100). Part of the total score. */
@property(readonly) double angleScore;

/** The distance-from-center score of the detected polygon (0 - 100). Part of the total score. */
@property(readonly) double distanceScore;

/** The unwarped aspect ratio of the detected polygon or -1, if no polygon was detected. */
@property(nonatomic, readonly) double unwarpedAspectRatio;

/** Returns YES, if the given aspect ratio matches the receivers unwarpedAspectRatio in a fuzzy way. **/
- (BOOL)matchesAspectRatio:(SBSDKAspectRatio *)aspectRatio;

/**
 * Returns the index of a matching aspect ratio in the given list of aspect ratios,
 * or NSNotFound if no matching aspect ratio was found.
 **/
- (NSInteger)indexOfMatchingAspectRatio:(NSArray<SBSDKAspectRatio*>*_Nullable)aspectRatios;

@end

NS_ASSUME_NONNULL_END
