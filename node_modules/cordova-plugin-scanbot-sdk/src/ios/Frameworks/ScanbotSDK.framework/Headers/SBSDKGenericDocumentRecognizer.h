//
//  SBSDKGenericDocumentRecognizer.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 15.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import "SBSDKGenericDocumentRecognitionResult.h"
#import "SBSDKGenericDocument.h"
#import "SBSDKGenericDocumentCommonFieldType.h"
#import "SBSDKGenericDocumentsModel.h"
#import "SBSDKGenericDocumentExtensions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class to recognize and detect the data fields from specific documents,
 * e.g. German passports, ID cards and driver's licenses in a UIImage or CMSampleBufferRef.
 * In case of success, returns an instance of SBSDKGenericDocumentRecognitionResult holding
 * the generic document with all recognized fields, including their names, values and image excerpts, along with their OCR confidence values.
 */
@interface SBSDKGenericDocumentRecognizer : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;


/**
 * Designated initializer.
 * Creates an instance of the recognizer which recognizes any of the given accepted document types.
 * @param acceptedDocumentTypes An array of document types that should be recognized. Must not be nil or empty.
 */
- (instancetype)initWithAcceptedDocumentTypes:(nonnull NSArray<SBSDKGenericDocumentRootType*>*)acceptedDocumentTypes;

/**
 * Convenient initializer.
 * Creates an instance of the recognizer which recognizes any of the given accepted document types excluding certain fields.
 * @param acceptedDocumentTypes An array of document types that should be recognized. Must not be nil or empty.
 * @param excludedFieldTypes An array of normalized names for the document field types that should not be recognized. If nil all the fields are going to be recognized.
 */
- (instancetype)initWithAcceptedDocumentTypes:(nonnull NSArray<SBSDKGenericDocumentRootType*>*)acceptedDocumentTypes
                           excludedFieldTypes:(nullable NSArray<NSString *>*)excludedFieldTypes;
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
 * Set to NO, if recognition should happen on a single image.
 * Set to YES, if consecutive frames should be used to refine the recognized documents.
 * If set to YES, you need to call `resetAccumulation` before trying to recognize a different document.
 * Default value is NO.
 */
@property (nonatomic, assign) BOOL accumulatesDocuments;

/**
 * An array of recognizable document types. Please specify at least one document type you want to scan for.
 */
@property (nonnull, nonatomic, copy) NSArray<SBSDKGenericDocumentRootType *>* acceptedDocumentTypes;

/**
 * An array of normalized names for the document field types that should not be recognized. If nil all the fields are going to be recognized.
 */
@property (nullable, nonatomic, copy) NSArray<NSString *> *excludedFieldTypes;

/**
 * Recognizes a document on a video frame and extracts the documents fields.
 * @param sampleBufferRef The CMSampleBuffer instance to recognize a document on.
 * @param videoOrientation The orientation of the sample buffer.
 * @return The recognition result or nil if no document has been recognized.
 */
- (nullable SBSDKGenericDocumentRecognitionResult *)recognizeDocumentOnBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                  orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Recognizes a document on an UIImage instance and extracts the documents fields.
 * @param image The UIImage instance to recognize a document on.
 * @return The recognition result or nil if no document has been recognized.
 */
- (nullable SBSDKGenericDocumentRecognitionResult *)recognizeDocumentOnImage:(nonnull UIImage *)image;

/**
 * Resets the recognized-documents-accumulator.
 */
- (void)resetDocumentAccumulation;

@end

NS_ASSUME_NONNULL_END
