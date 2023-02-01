//
//  ObjectMapper.h
//  Scanbot SDK Cordova Plugin
//
//  Created by Stefan Dragnev on 01.06.18.
//  Copyright © 2018 doo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <ScanbotSDK/SBSDKScanbotSDK.h>

@interface ObjectMapper : NSObject

// map of configuration property name -> (map of configuration string -> int value)
+ (void)setEnumerationMapping:(NSDictionary<NSString*, NSDictionary<NSString*, NSNumber*>*>*)enumerationMapping;

+ (void)populateInstance:(id)instance
          fromDictionary:(NSDictionary*)dictionary;

+ (SBSDKOrientationLock)extractOrientationLockMode:(NSDictionary*)configuration;

+ (SBSDKDocumentDetectorMode)documentDetectorMode:(NSDictionary*)configuration;

+ (NSString *) normalizeJsonString:(NSString *)strValue;
+ (NSURL *) normalizeJsonFileURL:(NSString *)fileUrl;
+ (NSString *)normalizeJsonFileURLAsString:(NSString *)fileUrl;

@end
