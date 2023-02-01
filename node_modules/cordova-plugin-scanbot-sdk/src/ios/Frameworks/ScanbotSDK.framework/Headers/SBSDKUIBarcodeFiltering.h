//
//  SBSDKUIBarcodeFiltering.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 26.11.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarcodeScannerResult.h"

/**
 * A class for a barcode filtering that can be used in barcode scanning RTU-UI components.
 * You can customize the filtering of barcode results coming from RTU-UI barcode scanners by implementing a
 * subclass of this class and pass the instance of your filtering class to the barcode scanning RTU-UI component.
 *
 */
@interface SBSDKUIBarcodeFilter: NSObject

/**
 * Accepts or rejects a scanned barcode.
 * @param barcode The barcode to be accepted or rejected by the filter.
 * @return YES if the given barcode should be accepted, NO otherwise.
 */
- (BOOL)acceptsBarcode:(nonnull SBSDKBarcodeScannerResult *)barcode;

/**
 * Accepts or rejects a scanned barcode in the context of already accepted barcodes.
 * Accepts a barcodes, if it is not yet contained in the given array of accepted barcodes. Prevents duplicate barcodes.
 * @param barcode The barcode to be accepted or rejected by the filter.
 * @param codes List of current already accepted barcodes.
 * @return YES if the given barcode should be accepted, NO otherwise.
 */
- (BOOL)shouldAdd:(nonnull SBSDKBarcodeScannerResult *)barcode
       toBarcodes:(nonnull NSArray<SBSDKBarcodeScannerResult *>*)codes;

@end


/**
 * Subclass of SBSDKUIBarcodeFilter that only accepts barcodes with extensions.
 */
@interface SBSDKUIBarcodeExtensionsFilter: SBSDKUIBarcodeFilter
@end
