//
//  SBSDKUIMedicalCertificateScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.01.22.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Configuration for the behavior of medical certificates scanner.
 */
@interface SBSDKUIMedicalCertificateScannerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. The default value is NO. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** Whether the information of the patient (name, address) is extracted or not. The default value is YES. */
@property (nonatomic, assign, getter=isPatientInfoExtracted) BOOL extractPatientInfo;

/**
 * If set to YES a high-resolution photo of the medical certificate is captured to run the recognition on.
 * Upon successful recognition the recognition result also contains a high-resolution image of the medical certificate.
 * If set to NO, the video frames will be used for recognition and result image delivery.
 * The default value is YES.
 */
@property(nonatomic, assign) BOOL captureHighResolutionImage;


@end

