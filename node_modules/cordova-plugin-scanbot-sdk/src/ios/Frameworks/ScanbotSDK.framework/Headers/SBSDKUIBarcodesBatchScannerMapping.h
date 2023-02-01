//
//  SBSDKUIBarcodesBatchScannerMapping.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 09.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarcodeScannerResult.h"
#import "SBSDKUIBarcodeMappedData.h"

/** Protocol for 'SBSDKUIBarcodesBatchScannerViewController' barcode results mapping. */
@protocol SBSDKUIBarcodesBatchScannerMapping

/**
 * Method in which you should load and return information about barcode. The info is returned in block, so async loading is possible.
 * @param barcode Barcode, for which the info should be returned.
 * @param completion Block, where you should return mapped info about barcode.
 *
 */
- (void)loadMappedDataForBarcode:(nonnull SBSDKBarcodeScannerResult *)barcode
                      completion:(void(^_Nullable)(SBSDKUIBarcodeMappedData *_Nullable))completion;

@end
