//
//  SBSDKLicensePlateScannerResult.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.02.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A class describing the result of a license plate scan.
 */
@interface SBSDKLicensePlateScannerResult : NSObject

/** The country code that recognized on the license plate. */
@property(nonnull, nonatomic, readonly) NSString *countryCode;

/** The actual license plate text that was recognized on the license plate. */
@property(nonnull, nonatomic, readonly) NSString *licensePlate;

/** The whole, raw text that was recognized on the license plate. */
@property(nonnull, nonatomic, readonly) NSString *rawString;

/** The text recognition confidence. */
@property(nonatomic, readonly) double confidence;

/** Whether the validation of the scanned license plate was successful or not. */
@property(nonatomic, readonly) BOOL isValidationSuccessful;

/** The image that was used for the detection. */
@property(nullable, nonatomic, readonly) UIImage *croppedImage;

@end

NS_ASSUME_NONNULL_END
