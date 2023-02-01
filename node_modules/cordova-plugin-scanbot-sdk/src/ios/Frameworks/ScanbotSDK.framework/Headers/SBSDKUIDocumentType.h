//
//  SBSDKUIDocumentType.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKGenericDocumentRecognizer.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The type of the document that should be recognized with `SBSDKUIGenericDocumentRecognizerViewController`.
 * It is a composition of generic document types.
 */
@interface SBSDKUIDocumentType : NSObject

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/** A compound document type consisting of one or multiple generic document root types. */
- (nonnull instancetype)initWithGenericTypes:(NSArray<SBSDKGenericDocumentRootType *>*)genericTypes;

/** The document type for a German passport. Front side only. */
+ (SBSDKUIDocumentType *)passportDE;

/** The document type for a German driver's license. Front and back side . */
+ (SBSDKUIDocumentType *)driverLicenseFrontBackDE;

/** The document type for a German id card. Front and back side. */
+ (SBSDKUIDocumentType *)idCardFrontBackDE;

/** The array of generic document types the receiver is composited from. */
@property (nonatomic, readonly) NSArray<SBSDKGenericDocumentRootType *> *genericTypes;

@end

NS_ASSUME_NONNULL_END
