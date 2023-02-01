//
//  UIImage+SBSDKMetricsAnalysis.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 29.01.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageMetricsAnalyzer.h"

/**
 * @category UIImage(SBSDKMetricsAnalysis)
 * An UIImage class extension for receiving image metrics.
 */
@interface UIImage (SBSDKMetricsAnalysis)

/**
 * Analyzes and returns the metrics of the receiver.
 * @return A SBSDKImageChannelMetrics object.
 **/
- (nonnull NSArray<SBSDKImageChannelMetrics*>*)sbsdk_analyzeMetrics;

@end
