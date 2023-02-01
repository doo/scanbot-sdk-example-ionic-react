//
//  SBSDKTIFFImageWriterParameters.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 11/14/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKTIFFImageWriterUserDefinedField.h"
#import "SBSDKImageFilterTypes.h"


NS_ASSUME_NONNULL_BEGIN

/** TIFF Compression algorithms */
typedef NS_ENUM(int, SBSDKTIFFImageWriterCompressionOptions) {
    
    /** For both colored and binarized images */
    COMPRESSION_NONE = 1,
    
    /** Only for binarized images */
    COMPRESSION_CCITTRLE = 2,
    
    /** Only for binarized images */
    COMPRESSION_CCITTFAX3 = 3,
    
    /** Only for binarized images */
    COMPRESSION_CCITT_T4 = 3,
    
    /** Only for binarized images */
    COMPRESSION_CCITTFAX4 = 4,
    
    /** Only for binarized images */
    COMPRESSION_CCITT_T6 = 4,
    
    /** For both colored and binarized images */
    COMPRESSION_LZW = 5,
    
    /** Only for binarized images */
    COMPRESSION_CCITTRLEW = 32771,
    
    /** For both colored and binarized images */
    COMPRESSION_PACKBITS = 32773 ,
    
    /** For both colored and binarized images */
    COMPRESSION_DEFLATE = 32946,
    
    /** For both colored and binarized images */
    COMPRESSION_ADOBE_DEFLATE = 8
};

/**
 * Class used to define parameters for TIFF format writer.
 */
@interface SBSDKTIFFImageWriterParameters : NSObject

/** Defines if target document should be binarized. */
@property (nonatomic) BOOL binarize;

/** Defines target document DPI. */
@property (nonatomic) NSInteger dpi;

/** Defines target document compression algorithm. */
@property (nonatomic) SBSDKTIFFImageWriterCompressionOptions compression;

/** Array that contains user-defined TIFF tags that should be written into result TIFF document. */
@property (nonatomic, copy) NSArray<SBSDKTIFFImageWriterUserDefinedField *> *userDefinedFields;

/**
 * The filter that should be applied for binarization, if the binarize flag is set to YES.
 *
 * Defaults to SBSDKImageFilterTypePureBinarized.
 *
 * Note: Setting this property to a non-binarizing filter will raise an exception!
 * Valid binarizing filters are:
 * - SBSDKImageFilterTypePureBinarized
 * - SBSDKImageFilterTypeBinarized
 * - SBSDKImageFilterTypeOtsuBinarization
 * - SBSDKImageFilterTypeDeepBinarization
 * - SBSDKImageFilterTypeLowLightBinarization
 * - SBSDKImageFilterTypeLowLightBinarization2
 * - SBSDKImageFilterTypeSensitiveBinarization
 */
@property (nonatomic, assign) SBSDKImageFilterType binarizationFilter;

/**
 * Generates default parameters set for colored images.
 * @return generated SBSDKTIFFImageWriterParameters instance.
 */
+ (instancetype)defaultParameters;

/**
 * Generates default parameters set for binarized images.
 * @return generated SBSDKTIFFImageWriterParameters instance.
 */
+ (instancetype)defaultParametersForBinaryImages;

@end

NS_ASSUME_NONNULL_END
