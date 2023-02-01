//
//  SBSDKUIPageFileStorage.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 4/25/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIPageFileType.h"
#import "SBSDKImageFileFormat.h"
#import "SBSDKStorageLocation.h"
#import "SBSDKStorageCrypting.h"

/**
 * A class to store and restore images in a memory-efficient way.
 * Stores added images on disk and restores them if requested.
 * Can generate preview images of optimal resolution for the devices screen.
 * Manages two types of images: original images (as from camera or photo library)
 * and document images (cropped and perspective-corrected).
 * Helps you efficiently managing and persisting larger images without keeping them in memory.
 *
 * Caution: Since all images stored here are being persisted to the disk forever, you are responsible for removing
 * unused images.
 */
@interface SBSDKUIPageFileStorage : NSObject

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

/** The default instance of this class. **/
+ (nonnull instancetype)defaultStorage;

/** Set default storage. If not used, default storage will be created with default parameters. */
+ (void)setDefaultStorage:(nonnull SBSDKUIPageFileStorage *)defaultStorage;

/**
 * If file format is set to JPEG, this property holds the compression quality of the stored images.
 * Values must be between 0 (high compression, small file size, bad quality)
 * and 100 (no compression, huge file size, good image quality).
 * Read-only. Defaults to 80.
 */
@property (nonatomic, readonly) NSInteger writingJpegImageCompressionQuality;

/** File format of the stored images. Read-only. Defaults to JPEG. */
@property (nonatomic, readonly) SBSDKImageFileFormat writingImageFileFormat;

/**
 * Adds an original image to the receiver.
 * @param image The UIImage instance to manage.
 * @return The uuid of the added image that can be used to reference the image.
 */
- (nullable NSUUID *)addImage:(nonnull UIImage *)image;

/**
 * Replaces or sets an image with given page file ID and type.
 * Use this function to update the document image.
 *
 * Caution: Setting/replacing the original image is not allowed and will result in an error!
 *
 * @param image The new image to store.
 * @param pageFileID The existing ID of the original image in the receiver.
 * Returns an error if the ID does not exist in the receiver.
 * @param type The type of the image to replace/set. Must not be 'SBSDKUIPageFileTypeOriginal'.
 * @param error An error pointer containing the error (if any) after the call.
 * @return YES, if the operation was successful, NO otherwise.
 */
- (BOOL)setImage:(nonnull UIImage *)image
forExistingPageFileID:(nonnull NSUUID *)pageFileID
    pageFileType:(SBSDKUIPageFileType)type
           error:(NSError * _Nullable * _Nullable)error;

/**
 * Returns the URL of the full resolution image with given page file ID of given type.
 * @param pageFileID The page file ID of the requested image.
 * @param type The type of the image.
 * @return A URL pointing to the image file. Or nil if the image was not found.
 */
- (nullable NSURL *)imageURLWithPageFileID:(nonnull NSUUID *)pageFileID pageFileType:(SBSDKUIPageFileType)type;

/**
 * Returns the full resolution image with given page file ID of given type.
 * @param pageFileID The page file ID of the requested image.
 * @param type The type of the image.
 * @return An UIImage or nil if the image was not found.
 */
- (nullable UIImage *)imageWithPageFileID:(nonnull NSUUID *)pageFileID pageFileType:(SBSDKUIPageFileType)type;

/**
 * Returns the URL of the preview resolution image with given page file ID of given type.
 * @param pageFileID The page file ID of the requested image.
 * @param type The type of the image.
 * @return A URL pointing to the image file. Or nil if the image was not found.
 */
- (nullable NSURL *)previewImageURLWithPageFileID:(nonnull NSUUID *)pageFileID pageFileType:(SBSDKUIPageFileType)type;

/**
 * Returns the preview resolution image with given page file ID of given type.
 * @param pageFileID The page file ID of the requested image.
 * @param type The type of the image.
 * @return An UIImage or nil if the image was not found.
 */
- (nullable UIImage *)previewImageWithPageFileID:(nonnull NSUUID *)pageFileID pageFileType:(SBSDKUIPageFileType)type;

/**
 * Removes stored images of given type with the given page file ID.
 * @param pageFileID The page file ID which should be removed from the receiver.
 * @param type The type of image to be removed. Images of type 'SBSDKUIPageFileTypeOriginal' cannot be removed.
 * @return YES, if the operation successful, NO otherwise.
 */
- (BOOL)removeImageForExistingPageFileID:(nonnull NSUUID *)pageFileID pageFileType:(SBSDKUIPageFileType)type;

/**
 * Removes stored images of all types with the given page file ID.
 * @param pageFileID The page file ID which should be removed from the receiver.
 */
- (void)removePageFileID:(nonnull NSUUID *)pageFileID;

/**
 * Removes all stored images of all types except those from the exception list.
 * @param pageFileIDs The page file IDs of the images which should not be removed.
 */
- (void)removeAllExceptPageFileIDs:(nonnull NSArray<NSUUID *> *)pageFileIDs;

/**
 * Clears the receiver. Removes all stored images files from disk.
 */
- (void)removeAll;

/** Returns all available IDs in storage */
- (nonnull NSArray <NSUUID *> *)allPageFileIDs;

@end
