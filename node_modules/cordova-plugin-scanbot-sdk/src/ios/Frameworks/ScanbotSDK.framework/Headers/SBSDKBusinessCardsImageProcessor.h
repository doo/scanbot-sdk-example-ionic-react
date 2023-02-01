//
//  SBSDKBusinessCardsImageProcessor.h
//
//  Created by Yevgeniy Knizhnik on 12/17/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKImageStoring.h"
#import "SBSDKOCRResult.h"

/**
 * A class specifically designed to deal with images of business cards. It auto-rotates the images and extracts their
 * texts.
 * Can be subclassed and modified to your own needs.
 * Designed to work in conjunction with SBSDKMultipleObjectScannerViewController.
 */
@interface SBSDKBusinessCardsImageProcessor : NSObject

/**
 * If set to YES, performs text recognition on each image in the storage. Defaults to YES. Set to NO if you do not want
 * text recognition or if your license does not cover OCR.
 */
@property (nonatomic, assign) BOOL performOCR;

/**
 * If set to YES, performs automatic content based rotation of each image in the storage. Defaults to YES.
 * Set to NO if you do not want automatic rotation or if your license does not cover automatic rotation.
 */
@property (nonatomic, assign) BOOL performAutoRotation;

/**
 * Processes the images contained in an image storage. Asynchronously performs auto-rotation and text recognition OCR) and returns the OCR results
 * as well as the modified image storage in the completion handler.
 * @param storage The image storage containing the business card images. Will be modified to auto-rotate contained images.
 * @param languages A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param completion The completion block which delivers the (modified) image storage and an array of OCR results.
 **/
- (void)processImageStorage:(nonnull id<SBSDKImageStoring>)storage
               ocrLanguages:(nullable NSString *)languages
                 completion:(nonnull void (^)(_Nonnull id<SBSDKImageStoring>,
                                              NSArray<SBSDKOCRResult *>* _Nullable))completion;

@end
