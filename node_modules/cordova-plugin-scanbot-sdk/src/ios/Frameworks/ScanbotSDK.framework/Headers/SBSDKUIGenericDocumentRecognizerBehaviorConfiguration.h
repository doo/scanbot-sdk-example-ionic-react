//
//  SBSDKUIGenericDocumentRecognizerBehaviorConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKGenericDocumentRecognizer.h"
#import "SBSDKUIDocumentType.h"

NS_ASSUME_NONNULL_BEGIN
/**
 * Configuration for the behavior of the generic document recognizer.
 */
@interface SBSDKUIGenericDocumentRecognizerBehaviorConfiguration : NSObject

/** Whether the torch light is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/**
 * The recognizable document type.
 */
@property (nonnull, nonatomic, strong) SBSDKUIDocumentType *documentType;

/**
 * The accepted minimal sharpness score. Images with a score less than that will
 * be rejected with blurry status.
 *
 * 0 - any image will be accepted.
 * 80 - a good compromise; the recommended setting.
 * 100 - only very sharp images will be accepted.
 *
 * The default value is 80.
 */
@property (nonatomic, assign) CGFloat sharpnessAcceptanceFactor;

/**
 * An array of normalized names for the document field types that should not be recognized. If nil all the fields are going to be recognized.
 */
@property (nullable, nonatomic, copy) NSArray<NSString *> *excludedFieldTypes;

@end

NS_ASSUME_NONNULL_END
