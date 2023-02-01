//
//  SBSDKImageStoring.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.05.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#ifndef SBSDKImageStoring_h
#define SBSDKImageStoring_h

#import <UIKit/UIKit.h>

/**
 * Protocol for an order-aware (array like) image storage.
 */
@protocol SBSDKImageStoring <NSObject, NSCopying>
@required

/** Number of images in the receiver. */
@property (nonatomic, readonly) NSUInteger imageCount;

/**
 Adds a UIImage into the storage.
 @param image The image to be added.
 @returns YES, if the operation was successful, NO otherwise.
 */
- (BOOL)addImage:(nonnull UIImage *)image;

/**
 Adds an image from a file into the storage.
 @param url The file URL of the image to be added.
 @returns YES, if the operation was successful, NO otherwise.
 */
- (BOOL)addImageFromURL:(nonnull NSURL *)url;

/**
 Returns the stored UIImage at the specified index.
 @param index A valid index of the image.
 @returns The image at the given index, or nil if the image could not be loaded.
 */
- (nullable UIImage *)imageAtIndex:(NSUInteger)index;

/**
 Returns the URL of the stored image at the specified index.
 @param index A valid index of the image.
 @returns The images URL at the given index, or nil if the image file does not exist.
 */
- (nullable NSURL *)imageURLAtIndex:(NSUInteger)index;

/**
 Removes the stored image at the given index from the image storage.
 @param index A valid index of the image to be removed.
 */
- (void)removeImageAtIndex:(NSUInteger)index;

/**
 Removes all stored images from the image storage.
 */
- (void)removeAllImages;

/**
 Creates a deep copy of the image storage.
 @returns A copy of the storage.
 */
- (nonnull id)copy;

@end

#endif /* SBSDKImageStoring_h */
