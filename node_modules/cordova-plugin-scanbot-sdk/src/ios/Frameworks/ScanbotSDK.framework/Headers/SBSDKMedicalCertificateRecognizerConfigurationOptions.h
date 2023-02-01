//
//  SBSDKMedicalCertificateRecognizerConfigurationOptions.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 07.06.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A class intended to store the configuration options for a medical certificate recognizer.
 */
@interface SBSDKMedicalCertificateRecognizerConfigurationOptions : NSObject

/** Enables the recognition of patient information box data. */
@property (nonatomic) BOOL patientInformationRecognitionEnabled;

/** Enables the recognition of barcode data. */
@property (nonatomic) BOOL barcodeRecognitionEnabled;

/** The default configuration. */
+ (instancetype)defaultConfigurationOptions;

@end

NS_ASSUME_NONNULL_END
