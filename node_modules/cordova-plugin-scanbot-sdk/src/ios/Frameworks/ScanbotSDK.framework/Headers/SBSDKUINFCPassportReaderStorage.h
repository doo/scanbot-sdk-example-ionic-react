//
//  SBSDKUINFCPassportReaderStorage.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 05.08.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  A class to store and remove images from `SBSDKUINFCPassportReaderViewController`.
 */
@interface SBSDKUINFCPassportReaderStorage : NSObject

/**
 * Sets base folder for images storing. A separate folder for NFC passport reader images will be created in this folder.
 * @param url URL which will be used as a base storage folder. In case of nil - default URL will be used.
 */
+ (void)setBaseStorageURL:(NSURL *_Nullable)url;

/**
 * Removes folder with NFC passport reader card images. Does not affect base folder.
 */
+ (void)cleanUpStorage;

@end
