//
//  SBSDKUIBarcodesBatchScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 12.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the textual contents of the detector screens for barcodes.
 */
@interface SBSDKUIBarcodesBatchScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed as description. */
@property (nonnull, nonatomic, strong) NSString *finderTextHint;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the clear button. */
@property (nullable, nonatomic, strong) NSString *clearButtonTitle;

/** String being displayed on the delete button. */
@property (nullable, nonatomic, strong) NSString *deleteButtonTitle;

/** String being displayed on the view results button.  */
@property (nullable, nonatomic, strong) NSString *submitButtonTitle;

/** String used for displaying amount of scanned barcodes. Use %d for number formatting symbol. */
@property (nullable, nonatomic, strong) NSString *barcodesCountText;

/** String used to show process of fetching mapped data for barcodes. */
@property (nullable, nonatomic, strong) NSString *fetchingStateText;

/** String to show that no barcodes were scanned yet. */
@property (nullable, nonatomic, strong) NSString *noBarcodesTitle;

@end

NS_ASSUME_NONNULL_END
