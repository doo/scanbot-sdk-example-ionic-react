//
//  SBSDKAspectRatio.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 16.01.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** A class that describes an aspect ratio for a documents page. **/
@interface SBSDKAspectRatio : NSObject

/** The width of the documents page. Unit independent. **/
@property(nonatomic, readonly) double width;

/** The height of the documents page. Unit independent. **/
@property(nonatomic, readonly) double height;

/** The aspect ratio of the receiver expressed as a double value of width divided by height. **/
@property(nonatomic, readonly) double ratio;

/**
 * Designated initializer.
 * @param width The width of the documents page.
 * @param height The height of the documents page.
 **/
- (instancetype)initWithWidth:(double)width andHeight:(double)height;

/**
 * Returns an inverted copy of the receiver. Inverted here means that width and height are swapped and therefore
 * the resulting aspect ratio is the reciproke of the receivers aspect ratio.
 */
- (instancetype)inverted;

/**
 * Not available.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
