//
//  SBSDKBaseScannerEnergyConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 18.08.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The energy management configuration object for a 'SBSDKBaseScannerViewController' and its subclasses.
 * 'SBSDKBaseScannerViewController' and subclasses sport a customizable energy management system.
 *
 * Since detectors and recognizers running on a live video feed can put a lot of load onto the CPU and/or GPU
 * of the device, causing the battery to drain quickly and running the device hot, you can customize the energy
 * consumption using this class by configuring the rate of detections/recognitions per second in performance mode as
 * well as in energy saving mode.
 *
 * In performance mode the detectors/recognizers will be fed with a higher, configurable rate of
 * video frames per second.
 * After a certain, configurable period of inactivity the energy save mode will be engaged and the rate
 * of detections/recognitions will be reduced to a lower (configurable) rate.
 * You can also configure the time of inactivity before the automatic mode switches from performance to energy save mode.
 
 * Inactivity here means that both of the following conditions are met:
 * 1) The device did not register significant motion for this period.
 * 2) No positive detector/recognizer results have been registered during this period.
 *
 * Once in energy save mode the device can only return to performance mode if it is moved significantly or a positive
 * detection/recognition result was registered.
 */
@interface SBSDKBaseScannerEnergyConfiguration : NSObject

/**
 * Set to YES, if automatic energy saving should be enabled. With automatic energy saving enabled the
 * base scanner view controller will, after a certain time of inactivity, enter the energy save mode by lowering the
 * detection/recognition rate.
 *
 * Defaults to YES.
 */
@property(nonatomic, assign, getter=isEnergySavingEnabled) BOOL energySavingEnabled;

/**
 * The rate of detections/recognitions per second in normal performance mode.
 *
 * Defaults to 20, meaning that 20 frames per second are detected/recognized, equally distributed over one second.
 * When the video frame rate is 30, 10 frames will be skipped and 20 frames will be detected/recognized.
 *
 * Note: if you set the detection rate greater to or equal to the video frame rate, no frames will be skipped,
 * the actual detection rate is limited by the video frame rate.
 */
@property(nonatomic, assign) NSUInteger detectionRate;

/**
 * The rate of detections/recognitions per second in energy save mode.
 *
 * Defaults to 1, meaning that 1 frame per second is detected/recognized.
 * When the video frame rate is 30, 29 frames will be skipped, 1 frame is detected/recognized.
 *
 * Note: if you set the detection rate greater to or equal to the video frame rate, no frames will be skipped,
 * the actual detection rate is limited by the video frame rate.
 *
 * Note: Usually you set a much lower value here as for the detectionRate property to save energy.
 */
@property(nonatomic, assign) NSUInteger energySaveDetectionRate;

/**
 * The amount of time in seconds of no activity in performance mode before the energy save mode will be engaged.
 * Defaults to 4 seconds.
 */
@property(nonatomic, assign) NSTimeInterval inactivityTimeout;

/**
 * This is the default configuration with the properties initialized as mentioned in their description.
 * @return The default energy configuration object which can be changed and then passed back to the
 * base scanner view controller.
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
