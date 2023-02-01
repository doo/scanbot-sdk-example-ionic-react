//
//  SBSDKTIFFImageWriter.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 08.02.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SBSDKTIFFImageWriterParameters.h"
#import "SBSDKStorageCrypting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Class used to convert and write images in TIFF format
 */
@interface SBSDKTIFFImageWriter : NSObject

/**
 * Write single-page TIFF file
 * @param images The array of source images the TIFF file will be created from.
 * @param fileURL File URL for newly created TIFF file
 * @param parameters The parameters for the TIFF generation.
 * @return Operation result. YES if file created and saved successfully, NO otherwise.
 */
+ (BOOL)writeTIFF:(NSArray<UIImage *> *)images
          fileURL:(NSURL *)fileURL
       parameters:(SBSDKTIFFImageWriterParameters *)parameters;


/**
 * Write single-page TIFF file
 * @param images The array of source images the TIFF file will be created from.
 * @param fileURL File URL for newly created TIFF file
 * @param encrypter The encrypter used to encrypt the TIFF file. If nil, no encryption is used.
 * @param parameters The parameters for the TIFF generation.
 * @return Operation result. YES if file created and saved successfully, NO otherwise.
 */
+ (BOOL)writeTIFF:(NSArray<UIImage *> *)images
          fileURL:(NSURL *)fileURL
        encrypter:(id<SBSDKStorageCrypting>)encrypter
       parameters:(SBSDKTIFFImageWriterParameters *)parameters;

/**
 * Write single-page TIFF file
 * @param imageURLs The array of URLs to the source images the TIFF file will be created from.
 * @param fileURL File URL for newly created TIFF file
 * @param parameters The parameters for the TIFF generation.
 * @return Operation result. YES if file created and saved successfully, NO otherwise.
 */
+ (BOOL)writeTIFFFromURLs:(NSArray<NSURL *> *)imageURLs
                  fileURL:(NSURL *)fileURL
               parameters:(SBSDKTIFFImageWriterParameters *)parameters;

/**
 * Write single-page TIFF file
 * @param imageURLs The array of URLs to the source images the TIFF file will be created from.
 * @param fileURL File URL for newly created TIFF file
 * @param encrypter The encrypter used to encrypt the TIFF file. If nil, no encryption is used.
 * @param parameters The parameters for the TIFF generation.
 * @return Operation result. YES if file created and saved successfully, NO otherwise.
 */
+ (BOOL)writeTIFFFromURLs:(NSArray<NSURL *> *)imageURLs
                  fileURL:(NSURL *)fileURL
                encrypter:(id<SBSDKStorageCrypting>)encrypter
               parameters:(SBSDKTIFFImageWriterParameters *)parameters;

/**
 * Returns the TIFF data for an array of images.
 * @param images The array of source images the TIFF data will be created from.
 * @param parameters The parameters for the TIFF generation.
 * @return The TIFF data generated from the source array of images.
 */
+ (nullable NSData *)tiffDataForImages:(NSArray<UIImage *> *)images
                            parameters:(SBSDKTIFFImageWriterParameters *)parameters;


@end

NS_ASSUME_NONNULL_END
