//
//  SBSDKOCRResult.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 25.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKPageAnalyzerResult.h"
#import "SBSDKOCRPage.h"

/**
 * This class summarizes the results of an optical character recognition (OCR) operation for number of pages.
 * It contains the array of SBSDKOCRPages.
 * For convenience this immutable class conforms to NSCopying protocol.
 */
@interface SBSDKOCRResult : NSObject <NSCopying>

/** The complete recognized text of the OCR operation. */
@property (nonatomic, readonly, nonnull) NSString *recognizedText;

/** Array of pages with OCR data */
@property (nonatomic, readonly, nonnull) NSArray<SBSDKOCRPage *> *pages;

@end
