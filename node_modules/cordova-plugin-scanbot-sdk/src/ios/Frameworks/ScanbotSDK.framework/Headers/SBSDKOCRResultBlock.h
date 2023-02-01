//
//  SBSDKOCRResultBlock.h
//  ScanbotSDK
//
//  Created by Dmytro Makarenko on 3/21/19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * When an OCR operation finishes it returns an array of result blocks containing e.g.
 * the position and type of recognized text. Each of the result blocks has a specific type.
 */
typedef NS_ENUM(NSUInteger, SBSDKOCRResultBlockType) {
    /** The result block represents a text paragraph. */
    SBSDKOCRResultBlockTypeParagraph = 1 << 0,
    
    /** The result block represents a line of text. */
    SBSDKOCRResultBlockTypeLine = 1 << 1,
    
    /** The result block represents a word. */
    SBSDKOCRResultBlockTypeWord = 1 << 2
};

/**
 * Part of the optical character recognitions result. This result contains multiple SBSDKOCRResultBlock objects.
 * Each block represents a text paragraph, a text line or a word and contains information about it, like the found text,
 * the bounding box, where in the image the paragraph/line/word can be found, the confidence value and the type.
 * For convenience this immutable class conforms to NSCopying protocol.
 */
@interface SBSDKOCRResultBlock : NSObject<NSCopying>

/** The recognized text within the receivers bounding box. */
@property (nonatomic, readonly, nonnull) NSString *text;

/**
 The bounding box of the receiver in normalized unit coordinate space Top, Left:(0.0, 0.0) - Width, Height(1.0, 1.0).
 Use the `boundingBoxWithImageSize:` method to get the bounding box in absolute image coordinates.
 */
@property (nonatomic, readonly) CGRect boundingBox;

/**
 * The confidence value describes how confident the OCR engine was when detecting the letters and words.
 * Ranges from 0.0 (not confident) to 100.0 (very confident).
 */
@property (nonatomic, readonly) CGFloat confidenceValue;

/** The type of the block. See SBSDKOCRResultBlockType. */
@property (nonatomic, readonly) SBSDKOCRResultBlockType blockType;

/**
 * Designated initializer.
 * @param text The text of the block.
 * @param boundingBox The bounding box of the block in normalized unit coordinates.
 * @param confidenceValue The confidence value of the block.
 * @param blockType The type of the block.
 * @return Initialized instance of SBSDKOCRResultBlock.
 */
- (nonnull instancetype)initWithText:(nonnull NSString *)text
                         boundingBox:(CGRect)boundingBox
                     confidenceValue:(CGFloat)confidenceValue
                           blockType:(SBSDKOCRResultBlockType)blockType;

/**
 * Calculates the bounding box of the receiver in absolute image coordinate system.
 * @param imageSize The size of the image the box is scaled into.
 * @return The bounding box in absolute image coordinate system.
 */
- (CGRect)boundingBoxWithImageSize:(CGSize)imageSize;

@end

NS_ASSUME_NONNULL_END
