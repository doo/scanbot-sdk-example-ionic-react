//
//  SBSDKLog.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 17.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKScanbotSDKConstants.h"


@interface SBSDKLog : NSObject

+ (void)setLoggingEnabled:(BOOL)enabled;
+ (void)logInfo:(NSString *)formatString, ...;
+ (void)logError:(NSString *)formatString, ...;
+ (void)logWarning:(NSString *)formatString, ...;

+ (void)printInfo:(NSString *)message;
+ (void)printError:(NSString *)message;
+ (void)printWarning:(NSString *)message;

@end

@interface SBSDKError : NSObject

+ (NSError *)errorWithCode:(SBSDKErrorCode)errorCode;

@end
