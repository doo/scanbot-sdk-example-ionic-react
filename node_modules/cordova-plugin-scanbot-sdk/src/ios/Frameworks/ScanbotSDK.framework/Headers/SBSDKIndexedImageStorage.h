//
//  SBSDKIndexedImageStorage.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 4/20/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageFileFormat.h"
#import "SBSDKStorageLocation.h"
#import "SBSDKImageStoring.h"
#import "SBSDKStorageCrypting.h"

/**
 * A simple thread-safe multiple-reader-single-writer index based disk image cache class.
 * Manages images in an array-like fashion.
 */
@interface SBSDKIndexedImageStorage : NSObject <SBSDKImageStoring>

/** The number of stored images. */
@property (nonatomic, readonly) NSUInteger imageCount;

/**
 * Array of all stored images URLs.
 * Note: If the storage is encrypted, the data at these URLs are encrypted and must be properly
 * decrypted before being used.
 */
@property (nonatomic, readonly, nonnull) NSArray<NSURL *> *imageURLs;

/** The JPEG compression if JPEG file format is used. Range: 0.0 - 1.0. */
@property (nonatomic, assign) CGFloat jpegCompressionQuality;

/** Image file format to be used to store the managed images. */
@property (nonatomic, readonly) SBSDKImageFileFormat fileFormat;

/**
 * Encrypter used to encrypt and decrypt the image data. If nil, no encryption/decryption is used.
 *
 * Note: When using encryption you still can access the unencrypted images in the receiver.
 * Of course, encrypted storages cannot be read without the proper encrypter being set here.
 * You are responsible for migrating image storages.
 *
 * Defaults to nil: no encryption is used.
 *
 * See `SBSDKAESEncrypter`for reference.
 */
@property (nonatomic, strong, nullable) id<SBSDKStorageCrypting> encrypter;


/**
 * Initializes a new 'SBSDKIndexedImageStorage' at a temporary location (application caches folder).
 * On deallocation the receiver will remove all its files from the file system.
 * @return A new 'SBSDKIndexedImageStorage' instance.
 */
+ (nullable instancetype)temporaryStorage;

/**
 * Initializes a new 'SBSDKIndexedImageStorage' at the given storage location.
 * @param storageLocation The storage location at which the new storage should reside.
 * @return A new 'SBSDKIndexedImageStorage' instance at the given storage location.
 */
- (nullable instancetype)initWithStorageLocation:(nullable SBSDKStorageLocation *)storageLocation;

/**
 * Initializes a new 'SBSDKIndexedImageStorage' at the given storage location with given image file format.
 * @param storageLocation The storage location at which the new storage should reside.
 * @param fileFormat The file format that should be used to store the images.
 * @param encrypter The encrypter used to encrypt/decrypt image data. If nil, no encryption is used.
 * @return A new 'SBSDKIndexedImageStorage' instance at the given storage location.
 */
- (nullable instancetype)initWithStorageLocation:(nullable SBSDKStorageLocation *)storageLocation
                                      fileFormat:(SBSDKImageFileFormat)fileFormat
                                   withEncrypter:(nullable id<SBSDKStorageCrypting>)encrypter;


/**
 * Initializes a new 'SBSDKIndexedImageStorage' at the given storage location with given image file format.
 * @param storageLocation The storage location at which the new storage should reside.
 * @param fileFormat The file format that should be used to store the images.
 * @param encrypter The encrypter used to encrypt/decrypt image data.If nil, no encryption is used.
 * @param encryptedImageURLs Array of URLs containing encrypted images. The images at these URLs must be encrypted with
 * the given encrypter (if not nil) and must have the same file format as specified in the fileFormat parameter.
 * @return A new 'SBSDKIndexedImageStorage' instance at the given storage location.
 */
- (nullable instancetype)initWithStorageLocation:(nullable SBSDKStorageLocation *)storageLocation
                                      fileFormat:(SBSDKImageFileFormat)fileFormat
                                   withEncrypter:(nullable id<SBSDKStorageCrypting>)encrypter
                             encryptedImagesURLs:(NSArray<NSURL *>*_Nonnull)encryptedImageURLs;

/**
 * Adds a new image to the receiver.
 * @param image The UIImage to be managed by the receiver.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)addImage:(nonnull UIImage *)image;

/**
 * Adds a new image to the receiver.
 * @param url The URL the image is read from.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)addImageFromURL:(nonnull NSURL *)url;

/**
 * Returns the image at the given index.
 * @param index The valid index at which the requested image is located at.
 * @return The stored UIImage or nil, if there was no image at that index.
 */
- (nullable UIImage *)imageAtIndex:(NSUInteger)index;

/**
 * Returns the images file URL at the given index.
 * @param index The valid index at which the requested image is located at.
 * @return The URL of the image file or nil, if there was no image at that index.
 *
 * Note: If the storage is encrypted, the data at this URL is encrypted and must be properly
 * decrypted before being used.
 */
- (nullable NSURL *)imageURLAtIndex:(NSUInteger)index;

/**
 * Inserts a new image into the receiver at the given index.
 * @param image The UIImage to be managed by the receiver.
 * @param index The valid index at which the new image should be inserted.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)insertImage:(nonnull UIImage *)image atIndex:(NSUInteger)index;

/**
 * Moves the image at the source index to the destination index.
 * @param sourceIndex The valid current index of the image to be moved.
 * @param destinationIndex The valid new index of the image to be moved.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)moveImageFromIndex:(NSUInteger)sourceIndex toIndex:(NSUInteger)destinationIndex;

/**
 * Replaces the receivers image at index with the given image.
 * @param index The valid current index of the image to be replaced.
 * @param image The new image that should be stored at the given index.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)replaceImageAtIndex:(NSUInteger)index withImage:(nonnull UIImage*)image;

/**
 * Replaces the receivers image at index with the image stored at the given URL.
 * @param index The valid current index of the image to be replaced.
 * @param url The URL of the new image that should be stored at the given index.
 * @return YES, if the operation was successfull, NO otherwise.
 */
- (BOOL)replaceImageAtIndex:(NSUInteger)index withImageAtURL:(nonnull NSURL*)url;

/**
 * Removes the image at the given index from the receiver as well as from the the file system.
 * @param index The valid index of the image to be removed.
 */
- (void)removeImageAtIndex:(NSUInteger)index;

/**
 * Removes all stored images from the receiver as well as from the file system.
 */
- (void)removeAllImages;

/**
 * Blocks the current thread until all enqueued writing operations have been finished.
 */
- (void)waitUntilWritingCompleted;

@end
