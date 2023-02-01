//
//  SBSDKUIBarcodeImageStorage.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 05.02.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageFileFormat.h"
#import "SBSDKStorageLocation.h"
#import "SBSDKStorageCrypting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class to store and remove barcode images from `SBSDKUIBarcodeScannerViewController`.
 */
@interface SBSDKUIBarcodeImageStorage : NSObject

/**
 * If file format is set to JPEG, this property holds the compression quality of the stored images.
 * Values must be between 0 (high compression, small file size, bad quality)
 * and 100 (no compression, huge file size, good image quality).
 * Read-only. Defaults to 80.
 */
@property (nonatomic, readonly) NSInteger writingJpegImageCompressionQuality;

/** File format of the stored images. Read-only. Defaults to JPEG. */
@property (nonatomic, readonly) SBSDKImageFileFormat writingImageFileFormat;

/** The default instance of this class. **/
+ (SBSDKUIBarcodeImageStorage *)defaultStorage;

/** Set default storage. If not used, default storage will be created with default parameters. */
+ (void)setDefaultStorage:(SBSDKUIBarcodeImageStorage *)storage;

/** Not available. Use 'defaultStorage'. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. Use 'defaultStorage'. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Initializes storage with given image file format and default JPEG compression quality using the default storage location.
 * @param format image file format.
 * @return An instance of storage.
 */
- (nonnull instancetype)initWithImageFileFormat:(SBSDKImageFileFormat)format;

/**
 * Initializes storage with JPEG image file format and given JPEG compression quality using the default storage location.
 * @param jpegImageCompressionQuality JPEG compression quality.
 * @return An instance of storage.
 */
- (nonnull instancetype)initWithJPEGFileFormatAndCompressionQuality:(NSInteger)jpegImageCompressionQuality;


/**
 * Initializes storage with given image file format and default JPEG compression quality.
 * @param format image file format.
 * @param location The storage location where image files are saved to. If nil, the default location is chosen.
 * @return An instance of storage.
 */
- (nonnull instancetype)initWithImageFileFormat:(SBSDKImageFileFormat)format
                                       location:(nullable SBSDKStorageLocation *)location;

/**
 * Initializes storage with JPEG image file format and given JPEG compression quality.
 * @param jpegImageCompressionQuality JPEG compression quality.
 * @param location The storage location where image files are saved to. If nil, the default location is chosen.
 * @return An instance of storage.
 */
- (nonnull instancetype)initWithJPEGFileFormatAndCompressionQuality:(NSInteger)jpegImageCompressionQuality
                                                           location:(nullable SBSDKStorageLocation *)location;

/**
 * Clears the receiver. Removes all stored images files from disk.
 */
- (void)removeAll;

/** Returns all available image URLs in the storage */
- (nonnull NSArray <NSURL *> *)allImageURLs;

@end

NS_ASSUME_NONNULL_END
