//
//  SBSDKUILicensePlateScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKLicensePlateScannerConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the behavior of the license plate scanner.
 */
@interface SBSDKUILicensePlateScannerBehaviorConfiguration : NSObject

/** Whether the flash light is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/**
 * The maximum number of accumulated video frames before the current recognition result is returned. Defaults to 3.
 */
@property(nonatomic, assign) NSUInteger maximumNumberOfAccumulatedFrames;

/**
 * The minimum equal results in accumulated video frames to count as valid. Defaults to 2.
 */
@property(nonatomic, assign) NSUInteger minNumberOfRequiredFramesWithEqualRecognitionResult;

/** The strategy being used to find a license plate in an image. Default value is SBSDKLicensePlateScannerStrategyML. */
@property(nonatomic, assign) SBSDKLicensePlateScannerStrategy scanStrategy;


@end

NS_ASSUME_NONNULL_END
