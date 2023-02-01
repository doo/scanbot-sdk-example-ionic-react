//
//  SBSDKStorageCrypting.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 03.11.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Protocol for implementing encryption and decryption of data.
 *
 * ScanbotSDK comes with a built-in AES encryptor that currently supports AES128 and AES256. If these algorithms
 * are not meeting your requirements you can create and use your own encryption classes in ScanbotSDKs image storages
 * by simply conforming to this protocol and implementing the two methods.
 */
@protocol SBSDKStorageCrypting <NSObject>

/**
 * Encrypts the given data blob and returns the encrypted data blob.
 * @param data The data blob to encrypt.
 * @return The encrypted data.
 */
- (nonnull NSData*)encryptData:(nonnull NSData*)data;


/**
 * Decrypts the given encrypted data blob and returns the decrypted data blob.
 * @param data The data blob to decrypt.
 * @return The decrypted data.
 */
- (nonnull NSData*)decryptData:(nonnull NSData*)data;

@end

