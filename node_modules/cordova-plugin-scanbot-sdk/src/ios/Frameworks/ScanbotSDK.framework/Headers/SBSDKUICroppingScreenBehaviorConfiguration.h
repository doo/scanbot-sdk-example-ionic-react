//
//  SBSDKUICroppingScreenBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 30.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKDocumentDetector.h"

NS_ASSUME_NONNULL_BEGIN

/** Configuration for the behavior of the cropping screen. */
@interface SBSDKUICroppingScreenBehaviorConfiguration : NSObject

/**
 * The mode of the document detector to be used for document outline detection.
 * The default value  can be set via `+ (void)setDefaultDetectorMode:(SBSDKDocumentDetectorMode)newDefaultDetectorMode;`.
 * If not set specifically the default value is `SBSDKDocumentDetectorModeMachineLearning`.
 */
@property (nonatomic, assign) SBSDKDocumentDetectorMode detectorMode;

/** Enables or disables crop functionality. Default is YES.*/
@property(nonatomic, assign, getter=isCropEnabled) BOOL cropEnabled;

/** Enables or disables rotation functionality. Default is YES.*/
@property(nonatomic, assign, getter=isRotationEnabled) BOOL rotationEnabled;

@end

NS_ASSUME_NONNULL_END
