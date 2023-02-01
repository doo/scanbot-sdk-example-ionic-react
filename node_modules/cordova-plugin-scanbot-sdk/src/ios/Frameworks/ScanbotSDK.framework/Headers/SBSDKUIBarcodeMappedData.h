//
//  SBSDKUIBarcodeMappedData.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 09.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Class that contains barcode name and description.
 */
@interface SBSDKUIBarcodeMappedData : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/** Initializer */
- (instancetype)initWithName:(NSString *)name description:(NSString *)codeDescription;

/** Name of barcode. */
@property (nonatomic, strong, readonly) NSString *name;

/** Description of barcode. */
@property (nonatomic, strong, readonly) NSString *codeDescription;

@end

NS_ASSUME_NONNULL_END
