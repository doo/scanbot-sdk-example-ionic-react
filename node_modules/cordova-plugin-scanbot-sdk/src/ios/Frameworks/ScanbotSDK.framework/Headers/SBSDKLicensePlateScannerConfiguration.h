//
//  SBSDKLicensePlateScannerConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.02.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** The strategy being used to scan a license plate. */
typedef NS_ENUM(NSInteger, SBSDKLicensePlateScannerStrategy) {
    /** Classic strategy using heuristic algorithms to find a license plate in an image. */
    SBSDKLicensePlateScannerStrategyClassic,
    
    /** Machine learning based strategy using neural networks to find a license plate in an image. */
    SBSDKLicensePlateScannerStrategyML
};


/** A class being used to configure the license plate scanner. */
@interface SBSDKLicensePlateScannerConfiguration: NSObject

/** The strategy being used to find a license plate in an image. Default value is SBSDKLicensePlateScannerStrategyML. */
@property(nonatomic, assign) SBSDKLicensePlateScannerStrategy strategy;

/**
 * The maximum number of subsequent video frames being analyzed and accumulated when scanning for license plates.
 * Default value is 3.
 */
@property(nonatomic, assign) NSUInteger maximumNumberOfAccumulatedFrames;

/**
 * The minimum number of accumulated video frames with equal results to trigger a successful license plate scan.
 * Default value is 2.
 * */
@property(nonatomic, assign) NSUInteger minimumNumberOfRequiredFramesWithEqualScanningResult;

@end


NS_ASSUME_NONNULL_END
