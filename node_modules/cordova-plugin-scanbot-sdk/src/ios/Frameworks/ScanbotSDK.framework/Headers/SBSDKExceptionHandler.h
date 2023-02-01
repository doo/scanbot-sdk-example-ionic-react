//
//  SBSDKExceptionHandler.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 26.11.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Helper class to catch NSExceptions from with Swift code.
 */
@interface SBSDKExceptionHandler : NSObject

/**
 * Call a function that may throw an NSException and catch it using the catchBlock.
 * @param tryBlock A block that contains the calls to the throwing functions.
 * @param catchBlock A block being called if an exception is thrown during the execution of the tryBlock.
 */
+ (void)tryBlock:(void (^_Nonnull)(void))tryBlock catchBlock:(void (^_Nonnull)(NSException * _Nonnull))catchBlock;

@end

NS_ASSUME_NONNULL_END
