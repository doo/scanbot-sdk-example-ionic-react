//
//  SBSDKOCRPage.h
//  ScanbotSDKBundle
//
//  Created by Dmytro Makarenko on 3/21/19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKPageAnalyzerResult.h"
#import "SBSDKOCRResultBlock.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class summarizes the results of an optical character recognition (OCR) operation for a given page.
 * It contains the recognized text, and arrays for each type of SBSDKOCRResultBlock, as well as the result from the
 * page layout analysis.
 * For convenience this immutable class conforms to NSCopying protocol.
 */
@interface SBSDKOCRPage: NSObject <NSCopying>

/** The complete recognized text of the OCR operation. */
@property (nonatomic, readonly, nonnull) NSString *text;

/** An array of SBSDKOCRResultBlock objects containing all blocks of type paragraph. */
@property (nonatomic, readonly, nonnull) NSArray<SBSDKOCRResultBlock *> *paragraphs;

/** An array of SBSDKOCRResultBlock objects containing all blocks of type textline. */
@property (nonatomic, readonly, nonnull) NSArray<SBSDKOCRResultBlock *> *lines;

/** An array of SBSDKOCRResultBlock objects containing all blocks of type word. */
@property (nonatomic, readonly, nonnull) NSArray<SBSDKOCRResultBlock *> *words;

/** The result of the page analysis that is sometimes executed before the OCR operation. can be nil. */
@property (nonatomic, readonly, nullable) SBSDKPageAnalyzerResult *pageAnalyzerResult;

/**
 * Convenience method to append recognized text to the receivers text.
 * Can be used to merge results from multiple OCR operations into a single result.
 */
- (void)appendRecognizedText:(nullable NSString *)text;

/**
 * Convenience method to set the page analyzer result.
 * Can be used to merge results from multiple OCR operations into a single result.
 */
- (void)setPageAnalyzerResult:(nonnull SBSDKPageAnalyzerResult *)analyzerResult;

@end

NS_ASSUME_NONNULL_END
