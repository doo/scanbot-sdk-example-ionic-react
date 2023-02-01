//
//  SBSDKOpticalTextRecognizer.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKScanbotSDKConstants.h"
#import "SBSDKImageStoring.h"
#import "SBSDKProgress.h"
#import "SBSDKOCRResult.h"
#import "SBSDKPageAnalyzerResult.h"
#import "SBSDKStorageCrypting.h"

@class SBSDKOpticalTextRecognizer;

/** Delegate protocol for `SBSDKOpticalTextRecognizer`. */
@protocol SBSDKOpticalTextRecognizerDelegate <NSObject>

/**
 Asks the delegate if the text recognition should be cancelled.
 @return YES, if the text recognition should cancel, NO otherwise.
 **/
- (BOOL)shouldCancelTextRecognition;

@end

/**
 * A factory class to enqueue and execute optical character recognition operations: the heart of the Scanbot SDK OCR module.
 * It performs OCR operations on either a single image or a collection of images, see SBSDKImageStoring.
 * Additionally it can perform a standalone page analysis on a single image.
 * All of the operations are dispatched to a single serial queue to ensure low memory footprint and optimum CPU load.
 *
 * Any text recognition operation will fail with an error if all of the specified languages are missing as language files.
 * If the specified languages are partially available a warning will be logged, but the operation executes
 * without using the missing languages. Please see the section "Optical Character Recognition" of the main SDK documentation
 * for more details about the OCR language files.
 *
 * The number of languages passed to OCR operations have a significant impact on the performance: the more languages,
 * the slower the recognition process.
 */
@interface SBSDKOpticalTextRecognizer : NSObject

/**
 * Returns a list of all available two-letter ISO 639-1 language codes.
 * Note: This is not a list of installed languages but of all languages with training data available.
 * @return NSArray of NSString objects, each being a two-letter ISO 639-1 language code.
 */
+ (nonnull NSArray<NSString *> *)availableLanguages __attribute__((deprecated("Please use corresponding method of SBSDKResourcesManager instead.")));

/**
 * Returns a list of the two-letter ISO 639-1 language codes that are retrieved from the current NSLocale and the
 * users preferred languages.
 * Note: This is not a list of installed languages but of languages with training data available.
 * @return NSArray of NSString objects, each being a two-letter ISO 639-1 language code.
 */
+ (nonnull NSArray<NSString *> *)userPreferredLanguages;

/**
 * Returns a list of all installed two-letter ISO 639-1 language codes.
 * @return NSArray of NSString objects, each being a two-letter ISO 639-1 language code.
 */
+ (nonnull NSArray<NSString *> *)installedLanguages;

/**
 * Asynchronously recognizes text on a set of images with the specified 
 * languages and calls the completion handler upon completion.
 * If pdfOutputURL is a valid file URL a searchable PDF is created and written to the specified URL.
 * A searchable PDF contains selectable and searchable text.
 * @param storage The image storage containing the images to be recognized. Must not be nil, & contains at least 1 image
 * @param copyStorage Whether the receiver should make a physical copy of the image storage for the operation or not.
 * If set to NO, you must make sure that the image storage is not mutated while the operation is running.
 * Setting YES makes a physical copy of the files in the storage, using up disk memory, but protecting it against mutation.
 * @param indices An NSIndexSet specifying the indices of the images in the image storage that you want to recognize.
 * Pass nil if you want to select all images. Invalid indices are ignored.
 * @param languageString A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param pdfOutputURL If not nil and a valid file URL a searchable PDF is rendered and saved to this URL.
 * @param completionHandler The completionHandler that is being called upon completion of the operation.
 * Called on main thread.
 * The result info dictionary contains values for the following keys:
 * - SBSDKResultInfoImageStorageKey: the image storage as SBSDKImageStoring
 * - SBSDKResultInfoOCRResultsKey: the OCR  results as SBSDKOCRResult
 * - SBSDKResultInfoDestinationFileURLKey: the file URL of the output PDF
 
 * @return An SBSDKProgress object that can be used to observe the operations progress and to cancel the operation.
 */
+ (nullable SBSDKProgress *)recognizeText:(nonnull id<SBSDKImageStoring>)storage
                         copyImageStorage:(BOOL)copyStorage
                                 indexSet:(nullable NSIndexSet *)indices
                           languageString:(nullable NSString *)languageString
                             pdfOutputURL:(nullable NSURL *)pdfOutputURL
                               completion:(nullable SBSDKCompletionHandler)completionHandler;

/**
 * Asynchronously recognizes text on a set of images with the specified
 * languages and calls the completion handler upon completion.
 * If pdfOutputURL is a valid file URL a searchable PDF is created and written to the specified URL.
 * A searchable PDF contains selectable and searchable text.
 * @param storage The image storage containing the images to be recognized. Must not be nil, & contains at least 1 image
 * @param copyStorage Whether the receiver should make a physical copy of the image storage for the operation or not.
 * If set to NO, you must make sure that the image storage is not mutated while the operation is running.
 * Setting YES makes a physical copy of the files in the storage, using up disk memory, but protecting it against mutation.
 * @param indices An NSIndexSet specifying the indices of the images in the image storage that you want to recognize.
 * Pass nil if you want to select all images. Invalid indices are ignored.
 * @param languageString A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param encrypter The encrypter used to encrypt the PDF file. If nil, no encryption is used.
 * @param pdfOutputURL If not nil and a valid file URL a searchable PDF is rendered and saved to this URL.
 * @param completionHandler The completionHandler that is being called upon completion of the operation.
 * Called on main thread.
 * The result info dictionary contains values for the following keys:
 * - SBSDKResultInfoImageStorageKey: the image storage as SBSDKImageStoring
 * - SBSDKResultInfoOCRResultsKey: the OCR  results as SBSDKOCRResult
 * - SBSDKResultInfoDestinationFileURLKey: the file URL of the output PDF
 
 * @return An SBSDKProgress object that can be used to observe the operations progress and to cancel the operation.
 */
+ (nullable SBSDKProgress *)recognizeText:(nonnull id<SBSDKImageStoring>)storage
                         copyImageStorage:(BOOL)copyStorage
                                 indexSet:(nullable NSIndexSet *)indices
                           languageString:(nullable NSString *)languageString
                                encrypter:(nullable id<SBSDKStorageCrypting>)encrypter
                             pdfOutputURL:(nullable NSURL *)pdfOutputURL
                               completion:(nullable SBSDKCompletionHandler)completionHandler;



/**
 * Synchronously recognizes text on a set of images with the specified
 * languages and calls the completion handler upon completion.
 * If pdfOutputURL is a valid file URL a searchable PDF is created and written to the specified URL.
 * A searchable PDF contains selectable and searchable text.
 * @param storage The image storage containing the images to be recognized. Must not be nil, & contains at least 1 image
 * @param indices An NSIndexSet specifying the indices of the images in the image storage that you want to recognize.
 * Pass nil if you want to select all images. Invalid indices are ignored.
 * @param languageString A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param pdfOutputURL If not nil and a valid file URL a searchable PDF is rendered and saved to this URL.
 * @param outError A pointer to an NSError object.
 
 * @return An SBSDKOCRResult containing the result of the text recognition. Nil if an error occurred.
 */
+ (nullable SBSDKOCRResult *)recognizeText:(nonnull id<SBSDKImageStoring>)storage
                                  indexSet:(nullable NSIndexSet *)indices
                            languageString:(nullable NSString *)languageString
                              pdfOutputURL:(nullable NSURL *)pdfOutputURL
                                     error:(NSError *_Nullable*_Nullable)outError;

/**
 * Synchronously recognizes text on a set of images with the specified
 * languages and calls the completion handler upon completion.
 * If pdfOutputURL is a valid file URL a searchable PDF is created and written to the specified URL.
 * A searchable PDF contains selectable and searchable text.
 * @param storage The image storage containing the images to be recognized. Must not be nil, & contains at least 1 image
 * @param indices An NSIndexSet specifying the indices of the images in the image storage that you want to recognize.
 * Pass nil if you want to select all images. Invalid indices are ignored.
 * @param languageString A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param encrypter The encrypter used to encrypt the PDF file. If nil, no encryption is used.
 * @param pdfOutputURL If not nil and a valid file URL a searchable PDF is rendered and saved to this URL.
 * @param outError A pointer to an NSError object.
 
 * @return An SBSDKOCRResult containing the result of the text recognition. Nil if an error occurred.
 */
+ (nullable SBSDKOCRResult *)recognizeText:(nonnull id<SBSDKImageStoring>)storage
                                  indexSet:(nullable NSIndexSet *)indices
                            languageString:(nullable NSString *)languageString
                                 encrypter:(nullable id<SBSDKStorageCrypting>)encrypter
                              pdfOutputURL:(nullable NSURL *)pdfOutputURL
                                     error:(NSError *_Nullable*_Nullable)outError;

/**
 * Recognizes text within a specified area on a single image with the specified languages and
 * calls the completion handler upon completion.
 * @param imageURL The file URL at which the image is located. Must not be nil.
 * @param rectangle A rectangle defining the boundaries of where to recognize text.
 * Pass CGRectZero to recognize the whole image.
 * @param languageString A string of two-letter ISO 639-1 language codes, separated by '+',
 * the OCR engine should use for recognition. E.g. "de+en" (german and english) "ar+he+ja" (arabic, hebrew and japanese).
 * If the string is invalid or nil the user preferred languages are used.
 * Ignores white spaces, invalid languages and invalid characters.
 * @param completionHandler The completionHandler that is being called upon completion of the operation.
 * Called on main thread.
 * The result info dictionary contains values for the following keys:
 * - SBSDKResultInfoSourceFileURLKey: the file URL of the input image as NSURL
 * - SBSDKResultInfoOCRResultsKey: the OCR  results as SBSDKOCRResult
 
 * @return An SBSDKProgress object that can be used to observe the operations progress and to cancel the operation.
 */
+ (nullable SBSDKProgress *)recognizeText:(nonnull NSURL *)imageURL
                                rectangle:(CGRect)rectangle
                           languageString:(nullable NSString *)languageString
                               completion:(nullable SBSDKCompletionHandler)completionHandler;


/**
 * Runs a basic page layout analysis asynchronously on the given image and calls the completion handler upon completion.
 * The result contains information about general text orientation, writing direction, textline order and an angle to
 * deskew the image.
 *
 * @param imageURL The file URL at which the image is located. Must not be nil.
 * @param completionHandler The completionHandler that is being called upon completion of the operation.
 * Called on main thread.
 * The result info dictionary contains values for the following keys:
 * - SBSDKResultInfoSourceFileURLKey: the file URL of the input image as NSURL
 * - SBSDKResultInfoPageAnalyzerResultsKey: the page analysis result as SBSDKPageAnalyzerResult.
 *
 * @return An SBSDKProgress object that can be used to observe the operations progress and to cancel the operation.
 */
+ (nullable SBSDKProgress *)analyseImagePageLayout:(nonnull NSURL *)imageURL
                                        completion:(nullable SBSDKCompletionHandler)completionHandler;


@end
