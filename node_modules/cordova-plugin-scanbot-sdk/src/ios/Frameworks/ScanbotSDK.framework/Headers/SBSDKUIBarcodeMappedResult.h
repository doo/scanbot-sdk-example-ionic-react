//
//  SBSDKUIBarcodeMappedResult.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 09.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarcodeScannerResult.h"
#import "SBSDKUIBarcodeMappedData.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Class that contains barcode result and mapped data.
 */
@interface SBSDKUIBarcodeMappedResult : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/** Initializer */
- (nonnull instancetype)initWithBarcodeResult:(SBSDKBarcodeScannerResult *)barcode;

/** Barcode result. */
@property (nonatomic, strong, readonly) SBSDKBarcodeScannerResult *barcode;

/** Mapped info about barcode. Is filled via `SBSDKUIBarcodesBatchScannerMapping` protocol. Can be nil. */
@property (nonatomic, strong, readonly, nullable) SBSDKUIBarcodeMappedData *mappedData;


@end

NS_ASSUME_NONNULL_END
