//
//  SBSDKUIMRZScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 20.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Configuration for the behavior of the machine readable zone scanner.
 */
@interface SBSDKUIMRZScannerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** Whether scanner screen should make a sound on MRZ detection. */
@property (nonatomic, assign, getter=isSuccessBeepEnabled) BOOL successBeepEnabled;

/**
 * The number of frames to be accumulated results when recognizing machine readable zones. 
 * Lower values are more inaccurate but faster, higher values are more accurate but slower. 
 * Values less than or equal 1 effectively turn accumulation off.
 * The default value is 4.
 */
@property (nonatomic, assign) NSUInteger resultAccumulationCount;

/**
 * Time in seconds until the screen is automatically cancelled.
 * Set to 0 to disable automatic cancellation. Defaults to 0 (disabled).
 * */
@property (nonatomic, assign) NSTimeInterval autoCancelTimeout;

@end

