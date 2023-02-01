//
//  CordovaBarcodeExtensionFilter.m
//  Scanbot SDK Example Ionic
//
//  Created by Mayank Patil on 28/07/22.
//

#import "CordovaBarcodeExtensionFilter.h"

@implementation CordovaBarcodeExtensionFilter {
    BarcodeFilterType mFilterType;
}

-(id)init:(BarcodeFilterType)filterType
{
    if(self = [super init]) {
        mFilterType = filterType;
    }

    return self;
}

- (BOOL)acceptsBarcode:(nonnull SBSDKBarcodeScannerResult *)barcode {
    if (![super acceptsBarcode: barcode]) {
        return false;
    }
    
    NSString* extension = barcode.metadata[SBSDKBarcodeMetadataEANUPCExtensionKey];
    if (extension == nil || [extension length] == 0) {
        return false;
    }
    
    switch (mFilterType) {
        case CordovaBarcodeExtensionFilterWithExtension:
            return true;
        case CordovaBarcodeExtensionFilterWithEAN2Extension:
            return trim(extension).length == 2;
        case CordovaBarcodeExtensionFilterWithEAN5Extension:
            return trim(extension).length == 5;
        default:
            return false;
    }
}

- (BOOL)shouldAdd:(nonnull SBSDKBarcodeScannerResult *)barcode
       toBarcodes:(nonnull NSArray<SBSDKBarcodeScannerResult *>*)codes
{
    return [super shouldAdd:barcode toBarcodes:codes];
}

static inline NSString* trim(NSString* text) {
    return [text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
}

@end
