//
//  SBSDKUIHealthInsuranceCardScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 06.08.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

/** Configuration for the textual contents of the detector screen for Health Insurance Card scanner.*/
@interface SBSDKUIHealthInsuranceCardScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/**
 * String being displayed as description.
 * Will be shown for 5 seconds when scanning starts with no health card being recognized.
 */
@property (nonnull, nonatomic, strong) NSString *finderTextHint;

/** String being displayed when health insurance card was found and recognized. */
@property (nonnull, nonatomic, strong) NSString *detectionStatusSuccessText;

/** String being displayed when health insurance card was not found. */
@property (nonnull, nonatomic, strong) NSString *detectionStatusFailedDetectionText;

/** String being displayed when health insurance card was found but not recognized. */
@property (nonnull, nonatomic, strong) NSString *detectionStatusFailedValidationText;

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

@end
