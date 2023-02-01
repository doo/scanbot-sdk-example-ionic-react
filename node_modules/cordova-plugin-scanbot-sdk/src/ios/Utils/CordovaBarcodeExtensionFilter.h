//
//  CordovaBarcodeExtensionFilter.h
//  Scanbot SDK Example Ionic
//
//  Created by Mayank Patil on 28/07/22.
//

#import <Foundation/Foundation.h>
#import <ScanbotSDK/SBSDKScanbotSDK.h>

typedef enum BarcodeFilterType : NSUInteger {
    CordovaBarcodeExtensionFilterWithExtension,
    CordovaBarcodeExtensionFilterWithEAN2Extension,
    CordovaBarcodeExtensionFilterWithEAN5Extension
} BarcodeFilterType;

@interface CordovaBarcodeExtensionFilter : SBSDKUIBarcodeFilter

- (instancetype)init NS_UNAVAILABLE;
- (id)init:(BarcodeFilterType)filterType;
@end
