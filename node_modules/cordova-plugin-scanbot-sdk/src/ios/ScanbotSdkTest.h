#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

@interface ScanbotSdkTest : CDVPlugin

- (void)saveFile:(CDVInvokedUrlCommand*)command;

@end