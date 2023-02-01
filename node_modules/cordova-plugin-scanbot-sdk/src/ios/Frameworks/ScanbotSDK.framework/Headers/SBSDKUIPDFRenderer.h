//
//  SBSDKUIPDFRenderer.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 21.06.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIDocument.h"
#import "SBSDKPDFRenderer.h"

/**
 *  A class to render a `SBSDKUIDocument` into a PDF.
 */
@interface SBSDKUIPDFRenderer : NSObject

/**
 * Renders the document into a PDF at the specified file url.
 * @param document The document to be rendered as a PDF document.
 * @param pageSize The size of the pages in the PDF document.
 * @param pdfOutputURL The file URL where the PDF document is saved at.
 * @return An NSError if the operation failed, nil otherwise.
 */
+ (nullable NSError *)renderDocument:(nonnull SBSDKUIDocument *)document
                        withPageSize:(SBSDKPDFRendererPageSize)pageSize
                              output:(nonnull NSURL *)pdfOutputURL;


/**
 * Performs optical text recognition and renders the document into a searchable PDF at the specified file url.
 * @param document The document to be rendered as a PDF document.
 * @param languages Array of language strings to be used by optical text recognition.
 * If empty or nil, english language is used. Specify languages using ISO two-letter-language-codes, e.g. "en", "de".
 * @param pdfOutputURL The file URL where the PDF document is saved at.
 * @return An NSError if the operation failed, nil otherwise.
 */
+ (nullable NSError *)renderDocument:(nonnull SBSDKUIDocument *)document
                    withOCRLanguages:(nullable NSArray<NSString*>*) languages
                              output:(nonnull NSURL *)pdfOutputURL;
@end
