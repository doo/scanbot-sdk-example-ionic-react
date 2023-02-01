//
//  SBSDKStorageLocation.h
//  ScanbotSDKBundle
//
//  Created by Yevgeniy Knizhnik on 4/20/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Descriptor and helper class for describing and creating a directory on the file system. */
@interface SBSDKStorageLocation : NSObject

/** The URL of the applications documents folder. */
+ (nonnull NSURL *)applicationDocumentsFolderURL;

/** The URL of the applications support folder. */
+ (nonnull NSURL *)applicationSupportFolderURL;

/** The URL of the applications caches folder. */
+ (nonnull NSURL *)applicationCachesFolderURL;

/**
 * Designated initializer.
 * @param baseURL The URL of the folder in which the new storage should be located.
 * If the folder does not exist, it is created. If nil the new location will reside in the 'defaultURL'.
 * @return The new storage location living at the given folder.
 */
- (nullable instancetype)initWithBaseURL:(nullable NSURL *)baseURL;

/**
 * Generates a file or folder URL with the given name in the folder of the receivers baseURL.
 * @param key The name of the file or folder within the receivers.
 * @return A file or folder URL with the given name in the folder of the receivers baseURL
 */
- (nullable NSURL *)URLWithKey:(nonnull NSString *)key;

/** The default base URL for new storage locations. **/
+ (nonnull NSURL *)defaultURL;

/** A temporary URL in the applications caches folder. **/
+ (nonnull NSURL *)temporaryURL;

/** A temporary storage location in the applications caches folder. **/
+ (nonnull SBSDKStorageLocation*) temporaryLocation;

/** The base folder URL of the receiver. **/
@property (nullable, nonatomic, strong, readonly) NSURL *baseURL;

@end
