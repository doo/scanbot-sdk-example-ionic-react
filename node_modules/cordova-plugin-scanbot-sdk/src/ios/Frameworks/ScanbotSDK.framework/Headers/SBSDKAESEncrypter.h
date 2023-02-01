//
//  SBSDKAES256Encrypter.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 04.11.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKStorageCrypting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * An enum containing the available encryption modes for the SBSDKAESEncrypter.
 */
typedef NS_ENUM(NSUInteger, SBSDKAESEncrypterMode) {
    /** AES128 mode with a key length of 16 bytes. Secure and fast. */
    SBSDKAESEncrypterModeAES128,

    /** AES256 mode with a key length of 32 bytes. More secure, but slower. */
    SBSDKAESEncrypterModeAES256
};

/**
 * ScanbotSDKs default data encrypter. Provides AES128 and AES 256 encryption to your data.
 *
 *
 */
@interface SBSDKAESEncrypter: NSObject <SBSDKStorageCrypting>

/**
 * The key used for encryption and decryption of the data. It is being derived from the
 * given password, the salt and the iterations using the PBKDF2 function.
 * https://en.wikipedia.org/wiki/PBKDF2
 *
 * For decryption you can use this key directly or generate it using salt, password and the number of iterations.
 * Readonly.
 */
@property(nonatomic, readonly) NSData *key;

/**
 * The salt data used to derive the encryption key from the password.
 * A fixed value that may be needed for manual decryption key derivation on the backend side.
 * Readonly.
 */
@property(nonatomic, readonly) NSData *salt;

/**
 * The number of iterations used to derive the encryption key from the salt data and the password.
 * A fixed value that may be needed for manual decryption key derivation on the backend side.
 * Readonly.
 */
@property(nonatomic, readonly) NSUInteger iterations;

/**
 * The encryption initialization vector.
 * A fixed value that is needed for decryption on the backend side.
 */
@property(nonatomic, readonly) NSData *iv;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * Creates a new AES encrypter/decrypter with either AES128 or AES256 encryption.
 * The encryption/decryption key is derived from the password, the salt and the number of iterations
 * using the PBKDF2 function. See https://en.wikipedia.org/wiki/PBKDF2
 *
 * @param password The password phrase used to encrypt or decrypt the data. See notes in class info.
 * @return The new encrypter object or nil if the encrypter could not be created due to an empty password.
 */
- (nullable instancetype)initWithPassword:(NSString *)password mode:(SBSDKAESEncrypterMode)mode;

@end

NS_ASSUME_NONNULL_END
