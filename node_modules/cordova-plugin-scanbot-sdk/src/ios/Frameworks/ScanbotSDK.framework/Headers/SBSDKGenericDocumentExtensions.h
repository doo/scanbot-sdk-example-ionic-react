//
//  SBSDKGenericDocumentUtilities.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 19.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKGenericDocumentCommonFieldType.h"
#import "SBSDKGenericDocumentsModel.h"
#import "SBSDKCheckDocumentModel.h"

NS_ASSUME_NONNULL_BEGIN

/** Helper functions to get a convenience wrapper on a generic document. */
@interface SBSDKGenericDocument (Wrapping)

- (nullable SBSDKGenericDocumentWrapper *)wrap;

@end

/** Helper functions to get a flat view on a generic document, suited for table views etc. */
@interface SBSDKGenericDocument (Flattening)

/**
 * Generates a flat array of the document and its child documents recursively.
 * Can be used for displaying the documents fields in a table view.
 * @param includeEmptyChildren If set to YES, child documents without fields are included, otherwise NO.
 * @param includeEmptyFields If set to YES, fields with no values are included, otherwise NO.
 * @return An array of the child documents with the main document in the first position.
 */
- (nullable NSArray <SBSDKGenericDocument*> *)flatDocumentIncludingEmptyChildren:(BOOL)includeEmptyChildren
                                                            includingEmptyFields:(BOOL)includeEmptyFields;

/**
 * Generates a flat array of the document fields and its child documents fields recursively.
 * Can be used for displaying the documents fields in a table view.
 * @param includeEmptyFields If set to YES, fields with no values are included, otherwise NO.
 * @return An array of all the fields in the document.
 */
- (nullable NSArray <SBSDKGenericDocumentField*> *)allFieldsIncludingEmptyFields:(BOOL)includeEmptyFields;

@end



/** Root document type collection extensions */
@interface SBSDKGenericDocumentRootType (Collections)

/** Array of all available document front side root types. */
+ (nonnull NSArray<SBSDKGenericDocumentRootType*>*)frontSideDocumentTypes;

/** Array of all available document back side root types. */
+ (nonnull NSArray<SBSDKGenericDocumentRootType*>*)backSideDocumentTypes;

@end


NS_ASSUME_NONNULL_END
