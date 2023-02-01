//
//  SBSDKNFCDatagroup.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 28.04.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKNFCDatagroupType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Data on passports NFC chips are chunked in groups. Each group has a specific category and contains a
 * number of elements, each making up a key-value pair. Groups have individual security levels. We are only
 * allowed to extract data groups 1 and 2.
 *
 * This class is an abstract base class for one data group of a passports NFC chip.
 */
@interface SBSDKNFCDatagroup : NSObject

/** The type of the data group. */
@property (nullable, nonatomic, readonly) SBSDKNFCDatagroupType *type;

/** @return The number of elements parsed from the passports data group. */
- (NSUInteger)numberOfElements;

/**
 * Elements of data groups are stored in a map/dictionary.
 * This function returns the key of the key-value pair at the given index.
 * @param index The index of the entry.
 * @return The key of the element in the passports data group.
 */
- (nullable NSString *)keyAtIndex:(NSUInteger)index;

/**
* Elements of data groups are stored in a map/dictionary.
* This function returns the value of the key-value pair at the given index.
* @param index The index of the entry.
* @return The value of the element in the passports data group.
*/
- (nullable id)valueAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
