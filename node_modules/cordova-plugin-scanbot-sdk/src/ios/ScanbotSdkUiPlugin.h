//
//  ScanbotSdkUiPlugin.h
//  ScanbotSDKCordova
//
//  Created by Stefan Dragnev on 11.06.18.
//  Copyright © 2018 doo. All rights reserved.
//

#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

#import "UIColor+JSON.h"

@import ScanbotSDK;

@interface ScanbotSdkUiPlugin : CDVPlugin
- (void)startDocumentScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startCroppingScreen:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startMrzScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startBarcodeScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startBatchBarcodeScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startEHICScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startLicensePlateScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startDataScanner:(CDVInvokedUrlCommand*_Nonnull)command;
- (void)startGenericDocumentRecognizer:(CDVInvokedUrlCommand*_Nonnull)command;
@end

@interface DocumentScannerPromiseProxy : NSObject <SBSDKUIDocumentScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface CroppingScreenPromiseProxy : NSObject <SBSDKUICroppingViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface MRZScannerPromiseProxy : NSObject <SBSDKUIMRZScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface EHICScannerPromiseProxy : NSObject <SBSDKUIHealthInsuranceCardScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface BarcodeScannerPromiseProxy : NSObject <SBSDKUIBarcodeScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate
     andCallbackId:(NSString*_Nonnull)callbackId shouldWaitForGeneratedImage:
        (bool)shouldWaitForGeneratedImage NS_DESIGNATED_INITIALIZER;
@end

@interface BatchBarcodeScannerPromiseProxy : NSObject <SBSDKUIBarcodesBatchScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId;
@end

@interface LicensePlateScannerPromiseProxy : NSObject <SBSDKUILicensePlateScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface DataScannerPromiseProxy : NSObject <SBSDKUITextDataScannerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface GenericDocumentRecognizerPromiseProxy : NSObject <SBSDKUIGenericDocumentRecognizerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

@interface CheckRecognizerPromiseProxy : NSObject <SBSDKUICheckRecognizerViewControllerDelegate>
- init NS_UNAVAILABLE;
- initWithDelegate:(nonnull id<CDVCommandDelegate>)delegate andCallbackId:(NSString*_Nonnull)callbackId NS_DESIGNATED_INITIALIZER;
@end

static inline void applyLicensePlateStyleConfiguration(NSDictionary* _Nonnull configuration, SBSDKUILicensePlateScannerUIConfiguration* _Nonnull uiConfig) {
    NSString* accentColorString = [configuration objectForKey:@"confirmationDialogAccentColor"];
    if (accentColorString) {
        UIColor* accentColor = [UIColor colorFromHexString:accentColorString];
        UIColor* highlightedColor = [accentColor colorWithAlphaComponent:0.75];
        uiConfig.confirmationDialogRetryButtonStyle.textColor = accentColor;
        uiConfig.confirmationDialogRetryButtonStyle.highlightedTextColor = highlightedColor;
        uiConfig.confirmationDialogConfirmButtonStyle.textColor = accentColor;
        uiConfig.confirmationDialogConfirmButtonStyle.highlightedTextColor = highlightedColor;
    }
    Boolean confirmationDialogConfirmButtonFilled = [[configuration objectForKey:@"confirmationDialogConfirmButtonFilled"] boolValue];
    if (confirmationDialogConfirmButtonFilled) {
        uiConfig.confirmationDialogConfirmButtonStyle.backgroundColor = uiConfig.confirmationDialogRetryButtonStyle.textColor;
        uiConfig.confirmationDialogConfirmButtonStyle.highlightedBackgroundColor = [uiConfig.confirmationDialogRetryButtonStyle.textColor colorWithAlphaComponent:0.75];
        uiConfig.confirmationDialogConfirmButtonStyle.textColor = uiConfig.confirmationDialogStyle.dialogBackgroundColor;
        uiConfig.confirmationDialogConfirmButtonStyle.highlightedTextColor = [uiConfig.confirmationDialogStyle.dialogBackgroundColor colorWithAlphaComponent:0.75];
    }
    NSString* filledButtonTextColorString = [configuration objectForKey:@"confirmationDialogConfirmButtonFilledTextColor"];
    if (filledButtonTextColorString && confirmationDialogConfirmButtonFilled) {
        UIColor* textColor = [UIColor colorFromHexString:filledButtonTextColorString];
        UIColor* highlightedTextColor = [textColor colorWithAlphaComponent:0.75];
        uiConfig.confirmationDialogConfirmButtonStyle.textColor = textColor;
        uiConfig.confirmationDialogConfirmButtonStyle.highlightedTextColor = highlightedTextColor;
    }
}
