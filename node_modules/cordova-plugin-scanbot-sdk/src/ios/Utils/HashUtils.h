//
//  HashUtils.h
//
//  Created by Stefan Dragnev on 18.06.18.
//  Copyright © 2018 doo. All rights reserved.
//

#ifndef HashUtils_h
#define HashUtils_h

#import <CommonCrypto/CommonDigest.h>

#define PROBABILISTIC_HASH_WINDOW_SIZE 32768

static inline NSString* uriWithMinihash(NSURL* fileUri) {
    NSURLComponents* components = [NSURLComponents componentsWithURL:fileUri resolvingAgainstBaseURL:FALSE];
    
    unsigned long long fileSize = [[[NSFileManager defaultManager] attributesOfItemAtPath:components.path error:nil] fileSize];
    CC_MD5_CTX digest;
    CC_MD5_Init(&digest);
    CC_MD5_Update(&digest, &fileSize, sizeof(fileSize));
    
    FILE* f = fopen(components.path.UTF8String, "rb");
    const unsigned int bufSize = PROBABILISTIC_HASH_WINDOW_SIZE;
    if (fileSize > bufSize) {
        fseek(f, (long)((fileSize - bufSize) / 2), SEEK_SET);
    }
    char buffer[PROBABILISTIC_HASH_WINDOW_SIZE] = {};
    fread(buffer, bufSize, 1, f);
    fclose(f);
    CC_MD5_Update(&digest, buffer, bufSize);
    
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5_Final(result, &digest);
    
    NSMutableString *ret = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH*2];
    for(int i = 0; i<CC_MD5_DIGEST_LENGTH; i++)
    {
        [ret appendFormat:@"%02x", result[i]];
    }
    
    [components setQueryItems:@[ [NSURLQueryItem queryItemWithName:@"minihash" value:ret] ]];
    return components.string;
}

#endif /* HashUtils_h */
