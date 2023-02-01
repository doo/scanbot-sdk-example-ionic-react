//
//  SBSDKUINFCPassportReaderBehaviorConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 13.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Configuration for the behavior of  NFC reader.
*/
@interface SBSDKUINFCPassportReaderBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** Whether scanner screen should make a sound on successful MRZ detection. */
@property (nonatomic, assign, getter=isSuccessBeepEnabled) BOOL successBeepEnabled;

/** Defines, if photo image should be stored in internal storage (`SBSDKUINFCPassportReaderStorage`) on disk.
 *  If set to `NO`, the result `SBSDKUINFCPassportReaderResult`, that returns in `SBSDKUINFCPassportReaderViewControllerDelegate` will not have `photoURL`.
 *  Defaults to `NO`.
 */
@property (nonatomic, assign) BOOL shouldSavePhotoImageInStorage;

@end
