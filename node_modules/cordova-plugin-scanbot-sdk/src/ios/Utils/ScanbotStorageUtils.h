//
//  ScanbotStorageUtils.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import <ScanbotSDK/ScanbotSDK.h>

static NSString *const pluginStorageSubDirectory = @"sbsdk-plugin-storage";

@interface ScanbotStorageUtils : NSObject

+ (NSURL *)pluginStorageDirectoryURL;
+ (NSString *)pluginStorageDirectoryPath;
+ (BOOL)pluginStorageDirectoryExists;
+ (NSString *)generateFileName:(NSString *)extension;
+ (NSString *)generatePluginStorageFilePath:(NSString*)extension;
+ (NSError *)removeAllFilesFromPluginStorageDirectory;

+ (UIImage *)loadImage:(NSString *)imageFilePath;
+ (BOOL)saveImage:(NSString *)imageFilePath image:(UIImage *)image quality:(CGFloat)quality;
+ (BOOL)imageFileExists:(NSString *)imageFileUri;

@end
