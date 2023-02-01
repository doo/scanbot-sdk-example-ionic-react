//
//  ScanbotSdkPlugin.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

@interface ScanbotSdkPlugin : CDVPlugin

- (void)initializeSdk:(CDVInvokedUrlCommand*)command;
- (void)isLicenseValid:(CDVInvokedUrlCommand*)command;
- (void)getLicenseInfo:(CDVInvokedUrlCommand*)command;
- (void)cleanup:(CDVInvokedUrlCommand*)command;

- (void)detectBarcodesOnImage:(CDVInvokedUrlCommand*)command;
- (void)detectBarcodesOnImages:(CDVInvokedUrlCommand*)command;
- (void)detectBarcodesFromBytes:(CDVInvokedUrlCommand*)command;
- (void)detectDocument:(CDVInvokedUrlCommand*)command;
- (void)applyImageFilter:(CDVInvokedUrlCommand*)command;
- (void)rotateImage:(CDVInvokedUrlCommand*)command;
- (void)createPdf:(CDVInvokedUrlCommand*)command;
- (void)writeTiff:(CDVInvokedUrlCommand *)command;
- (void)performOcr:(CDVInvokedUrlCommand *)command;
- (void)getOcrConfigs:(CDVInvokedUrlCommand *)command;

- (void)createPage:(CDVInvokedUrlCommand *)command;
- (void)setDocumentImage:(CDVInvokedUrlCommand *)command;
- (void)detectDocumentOnPage:(CDVInvokedUrlCommand *)command;
- (void)applyImageFilterOnPage:(CDVInvokedUrlCommand *)command;
- (void)rotatePage:(CDVInvokedUrlCommand *)command;
- (void)getFilteredDocumentPreviewUri:(CDVInvokedUrlCommand *)command;
- (void)removePage:(CDVInvokedUrlCommand *)command;
- (void)estimateBlur:(CDVInvokedUrlCommand *)command;
- (void)refreshImageUris:(CDVInvokedUrlCommand *)command;

@end
