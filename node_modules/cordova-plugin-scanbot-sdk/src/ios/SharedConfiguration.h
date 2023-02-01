//
//  SharedConfiguration.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CDVScanbotSDKConfiguration.h"

@interface SharedConfiguration : NSObject

@property (nonatomic) BOOL loggingEnabled;
@property (nonatomic) BOOL isSDKInitialized;
@property (nonatomic) CDVScanbotSDKConfiguration* configuration;

+ (instancetype)defaultConfiguration;

@end
