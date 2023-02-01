//
//  ScanbotStorageUtils.m
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import "ScanbotStorageUtils.h"
#import "LoggingUtils.h"

@implementation ScanbotStorageUtils

+ (NSURL *)pluginStorageDirectoryURL {
    return [NSURL fileURLWithPath: [ScanbotStorageUtils pluginStorageDirectoryPath] isDirectory:YES];
}

+ (NSString *)pluginStorageDirectoryPath {
    NSString* pluginStorageDirectoryPath;
    
    NSString* customStorageBaseDirectoryUrl = [SharedConfiguration defaultConfiguration].configuration.storageBaseDirectory;
    if (customStorageBaseDirectoryUrl) {
        NSString* customStorageBaseDirectoryPath = [NSURL URLWithString: customStorageBaseDirectoryUrl].path;
        pluginStorageDirectoryPath = [NSString stringWithFormat:@"%@/%@", customStorageBaseDirectoryPath, pluginStorageSubDirectory];
    } else {
        NSString* defaultStorageBaseDirectory = [ScanbotStorageUtils scanbotSDKApplicationSupportFolder].path;
        pluginStorageDirectoryPath = [NSString stringWithFormat:@"%@/%@", defaultStorageBaseDirectory, pluginStorageSubDirectory];
    }
    
    [ScanbotStorageUtils recreateFolderIfNeeded:pluginStorageDirectoryPath];
    return pluginStorageDirectoryPath;
}

+ (BOOL)pluginStorageDirectoryExists {
    return [[NSFileManager defaultManager] fileExistsAtPath:[ScanbotStorageUtils pluginStorageDirectoryPath]];
}

+ (NSURL *)applicationSupportFolderURL {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
    return [NSURL fileURLWithPath:(NSString *)paths.firstObject isDirectory:YES];
}

+ (NSURL *)scanbotSDKApplicationSupportFolder {
    NSURL *url = [ScanbotStorageUtils applicationSupportFolderURL];
    return [url URLByAppendingPathComponent:@"io.scanbot.sdk" isDirectory:YES];
}

+ (void)recreateFolderIfNeeded:(NSString *)folderPath {
    if (![[NSFileManager defaultManager] fileExistsAtPath:folderPath]) {
        [[NSFileManager defaultManager] createDirectoryAtPath:folderPath
                                  withIntermediateDirectories:YES
                                                   attributes:nil
                                                        error:nil];
    }
}

+ (NSString *)generateFileName:(NSString *)extension {
    NSUUID *UUID = [NSUUID UUID];
    NSString *stringUUID = [[UUID UUIDString] lowercaseString];
    return [NSString stringWithFormat:@"%@.%@", stringUUID, extension];
}

+ (NSString *)generatePluginStorageFilePath:(NSString *)extension {
    NSString *pluginStoragePath = [ScanbotStorageUtils pluginStorageDirectoryPath];
    return [NSString stringWithFormat:@"%@/%@", pluginStoragePath, [ScanbotStorageUtils generateFileName:extension]];
}

+ (UIImage *)loadImage:(NSString *)imageFilePath {
    if ([ScanbotStorageUtils imageFileExists:imageFilePath]) {
        UIImage *image = [UIImage imageWithData:[NSData dataWithContentsOfFile:imageFilePath]];
        if (!image) {
            image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:imageFilePath]]];
        }
        return image;
    } else {
        SBSDKLog(@"Image loading failed. File %@ does not exist.", imageFilePath);
        return nil;
    }
}

+ (BOOL)saveImage:(NSString *)imageFilePath image:(UIImage *)image quality:(CGFloat)quality {
    NSData *imageData = UIImageJPEGRepresentation(image, quality);
    return [imageData writeToFile:imageFilePath atomically:YES];
}

+ (NSError *)removeAllFilesFromPluginStorageDirectory {
    NSString *pluginStoragePath = [ScanbotStorageUtils pluginStorageDirectoryPath];
    NSFileManager *fileManager = [NSFileManager new];
    NSDirectoryEnumerator *enumerator = [fileManager enumeratorAtPath:pluginStoragePath];
    NSError *err = nil;
    BOOL result;
    
    NSString *fileName;
    while (fileName = [enumerator nextObject]) {
        result = [fileManager removeItemAtPath:[pluginStoragePath stringByAppendingPathComponent:fileName] error:&err];
        if (!result && err) {
            SBSDKLog(@"Cleanup encountered an error: %@", err);
            break;
        }
    }
    return err;
}

+ (BOOL)imageFileExists:(NSString *)imageFileUri {
    return [[NSFileManager defaultManager] fileExistsAtPath:[NSURL URLWithString:imageFileUri].path];
}

@end
