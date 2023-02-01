//
//  LoggingUtils.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#ifndef LoggingUtils_h
#define LoggingUtils_h

#import <ScanbotSDK/SBSDKScanbotSDK.h>
#import "SharedConfiguration.h"

static void SBSDKLog(NSString *format, ...) {
    if ([SharedConfiguration defaultConfiguration].loggingEnabled) {
        va_list argumentList;
        va_start(argumentList, format);
        NSMutableString *message = [[NSMutableString alloc] initWithFormat:format arguments:argumentList];
        NSLogv(message, argumentList);
        va_end(argumentList);
    }
}

#endif /* LoggingUtils_h */
