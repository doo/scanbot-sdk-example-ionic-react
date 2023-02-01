//
//  SBSDKUINFCPassportReaderResult.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 05.08.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKNFCDatagroupDG1.h"
#import "SBSDKNFCDatagroupDG2.h"


/**
 * The result of a passport reading operation.
 */
@interface SBSDKUINFCPassportReaderResult : NSObject


/**
 * Designated initializer.
 * @param dataGroup1 The first dataGroup parsed from the passports NFC chip.
 * @param dataGroup2 The second dataGroup parsed from the passports NFC chip
 */
- (instancetype _Nonnull )initWithDataGroup1:(nullable SBSDKNFCDatagroupDG1 *)dataGroup1
                                  dataGroup2:(nullable SBSDKNFCDatagroupDG2 *)dataGroup2;

/** First datagroup. */
@property (nullable, nonatomic, strong, readonly) SBSDKNFCDatagroupDG1 *dataGroup1;

/** Second datagroup. */
@property (nullable, nonatomic, strong, readonly) SBSDKNFCDatagroupDG2 *dataGroup2;

/** The owner's photo URL. Storage for this URL can be controlled with `SBSDKUINFCPassportReaderStorage`. */
@property(nonatomic, strong, nullable) NSURL *photoURL;

@end
