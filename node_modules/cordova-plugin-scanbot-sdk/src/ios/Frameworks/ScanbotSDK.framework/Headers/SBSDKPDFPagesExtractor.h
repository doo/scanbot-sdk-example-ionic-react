//
//  SBSDKPDFPagesExtractor.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 28.07.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIDocument.h"
#import "SBSDKStorageCrypting.h"
#import "SBSDKProgress.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Class used to extract pages from a PDF file and returns them in various ways.
 * The synchronous functions of this class are running in the same thread that they are called from, so it is up to you to control the concurrency.
 * The asynchronous functions run in a shared queue to prevent memory pressure when running multiple extractions at the same time.
 * It is recommended to use background queues in most cases.
 * Currently the flattening of the PDF document is user's responsibility. So if the document will have unflattened annotations (except signs), they will not be exported.
 */
@interface SBSDKPDFPagesExtractor : NSObject

/**
 * Extracts pages from a PDF, converts them to JPEGs and writes them to a specified URL. Runs in the same thread that it is called from.
 * No encryption is used here. The compression is set to 0.9. Media box scale value is 2
 * @param pdfURL The URL of the PDF file.
 * @param outputURL The output folder where images will be stored. Must be an existing folder.
 * @return An array of URLs with extracted pages as JPEG files. The array will be empty if something is wrong.
 */
- (NSArray<NSURL *> *)imageURLsFromPDF:(NSURL *)pdfURL outputDirectory:(NSURL *)outputURL;

/**
 * Extracts pages from a PDF, converts them to JPEGs and writes them to a specified URL. Runs in the same thread that it is called from.
 * No encryption is used here. Media box scale value is 2
 * @param pdfURL The URL of the PDF file.
 * @param compression Compression of the output image file. The range is from 0 to 1, where 1 - lossless conversion, 0 - maximum compression is used.
 * @param outputURL The output folder where images will be stored. Must be an existing folder.
 * @return An array of URLs with extracted pages as JPEG files. The array will be empty if something is wrong.
 */
- (NSArray<NSURL *> *)imageURLsFromPDF:(NSURL *)pdfURL compression:(float)compression outputDirectory:(NSURL *)outputURL;

/**
 * Extracts pages from a PDF, converts them to JPEGs and writes them to a specified URL. Runs in the same thread that it is called from.
 * @param pdfURL The URL of the PDF file.
 * @param scaling Scaling applied to the PDF media box frame while extracting. Affects the output image quality. In most cases the recommended value is 2 and higher.
 * @param compression Compression of the output image file. The range is from 0 to 1, where 1 - lossless conversion, 0 - maximum compression is used.
 * @param encrypter The encrypter used to encrypt output image files. If nil, no encryption is used.
 * @param outputURL The output folder where images will be stored. Must be an existing folder.
 * @return An array of URLs with extracted pages as JPEG files. The array will be empty if something is wrong.
 */
- (NSArray<NSURL *> *)imageURLsFromPDF:(NSURL *)pdfURL
                               scaling:(CGFloat)scaling
                           compression:(float)compression
                             encrypter:(nullable id<SBSDKStorageCrypting>)encrypter
                       outputDirectory:(NSURL *)outputURL;

/**
 * Extracts pages from PDF and converts them to an array of UIImages. Nothing is written to disk during this operation. Runs in the same thread, as it is called from.
 * The scaling of the media box is set to 2.
 * @param pdfURL The URL of the PDF file.
 * @return An array of UIImages with extracted pages. The array will be empty if something is wrong.
 */
- (NSArray<UIImage *> *)imagesFromPDF:(NSURL *)pdfURL;

/**
 * Extracts pages from PDF and converts them to an array of UIImages. Nothing is written to disk during this operation. Runs in the same thread, as it is called from.
 * @param pdfURL The URL of the PDF file.
 * @param scaling Scaling applied to the PDF media box frame while extracting. Affects the output image quality. In most cases the recommended value is 2 and higher.
 * @return An array of UIImages with extracted pages. The array will be empty if something is wrong.
 */
- (NSArray<UIImage *> *)imagesFromPDF:(NSURL *)pdfURL scaling:(CGFloat)scaling;

/**
 * Extracts pages from PDF and returns them as `SBSDKUIDocument`. Each page of the PDF will be a separate `SBSDKUIPage`.
 * Runs in the same thread, as it is called from.
 * @param pdfURL The URL of the PDF file.
 * @return An array of UIImages with extracted pages. The array will be empty if something is wrong.
 */
- (SBSDKUIDocument *)documentFromPDF:(NSURL *)pdfURL;

/**
 * Asynchronously extracts pages from a PDF, converts them to JPEGs and writes them to a specified URL. 
 * The array of URLs is passed within the completion handler. 
 * @param pdfURL The URL of the PDF file.
 * @param scaling Scaling applied to the PDF media box frame while extracting. Affects the output image quality. In most cases the recommended value is 2 and higher.
 * @param compression Compression of the output image file. The range is from 0 to 1, where 1 - lossless conversion, 0 - maximum compression is used.
 * @param encrypter The encrypter used to encrypt output image files. If nil, no encryption is used.
 * @param outputURL The output folder where images will be stored. Must be an existing folder.
 * @param completion The completion handler that delivers the created array of image file URLs.
 * @return A progress object that can be used for cancellation and progress observing. If nil, an error occured.
 */
- (nullable SBSDKProgress *)imageURLsFromPDF:(NSURL *)pdfURL 
                                     scaling:(CGFloat)scaling
                                 compression:(float)compression
                                   encrypter:(nullable id<SBSDKStorageCrypting>)encrypter
                             outputDirectory:(NSURL *)outputURL 
                                  completion:(void (^)(NSArray<NSURL *> *))completion;

/**
 * Asynchronously extracts pages from PDF and returns them as `SBSDKUIDocument` in the completion handler. 
 * Each page of the PDF will be a separate `SBSDKUIPage`.
 * Runs in the same thread, as it is called from.
 * @param pdfURL The URL of the PDF file.
 * @param completion The completion handler that delivers the created `SBSDKUIDocument`.
 * @return A progress object that can be used for cancellation and progress observing. If nil, an error occured.
 */
- (nullable SBSDKProgress *)documentFromPDF:(NSURL *)pdfURL completion:(void (^)(SBSDKUIDocument *))completion;

@end

NS_ASSUME_NONNULL_END
