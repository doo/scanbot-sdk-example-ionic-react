//
//  SBSDKUITextDataScannerStepResult.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 17.09.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGBase.h>

/**
 * Encapsulates the result of the text recognition of a 'SBSDKUITextDataScannerViewController's workflow step.
 */

@interface SBSDKUITextDataScannerStepResult : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * @param stepTag The tag of the workflow step that recognized this result.
 * @param text The recognized and validated text.
 * @param confidence The confidence of the text recognition.
 */
- (instancetype _Nullable )initWithStepTag:(nonnull NSString *)stepTag
                                      text:(nullable NSString *)text
                                confidence:(CGFloat)confidence;

/**
 * The tag of the workflow step.
 */
@property (nonatomic, strong, readonly, nonnull) NSString *stepTag;

/**
 * The recognized and validated text.
 */
@property (nonatomic, strong, readonly, nullable) NSString *text;

/**
 * The confidence of the text recognition.
 */
@property (nonatomic, assign, readonly) CGFloat confidence;

@end
