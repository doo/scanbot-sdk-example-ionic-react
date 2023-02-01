//
//  SBSDKPDFMetadataProcessor.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 10.02.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Enables reading and writing of PDF metadata attributes like author, creator, title, keywords etc. to PDF files.
 * Caution: If you want to use this feature your app must import the PDFKit module.
 */
@interface SBSDKPDFMetadataProcessor: NSObject

/**
 * Reads the PDF metadata from a PDF at the given URL.
 * @param url The file URL of the PDF to read the metadata from.
 * @return Returns a dictionary containing the PDF metadata or nil if the metadata could not be extracted from the file.
 * The dictionaries keys are taken from Apple's PDFKit.framework and can be found here: https://developer.apple.com/documentation/pdfkit/pdfdocumentattribute?language=objc .
 */
+ (NSDictionary*)readMetadataFrom:(NSURL *)url;

/**
 * Extracts the contents of a PDF file and writes a new PDF file along with the given PDF metadata to the specified URL.
 * @param metadata The PDF metadata dictionary to be written to the output PDF file.
 * The dictionaries keys are taken from Apple's PDFKit.framework and can be found here: https://developer.apple.com/documentation/pdfkit/pdfdocumentattribute?language=objc .
 * @param withPDFFrom The file URL of the source PDF file.
 * @param toURL The file URL of the destination PDF file.
 * @param removeCurrentMeta If set to YES, the source PDF metadata is ignored. Otherwise both metadata structures will be merged.
 * @return YES, if the metadata has been successfully saved. NO otherwise.
 */
+ (BOOL) writeMetadata:(NSDictionary*)metadata withPDFFrom:(NSURL*)pdfUrl toURL:(NSURL*)pdfOutput removeCurrentMeta:(BOOL)removeMetadata;

@end
