//
//  SBSDKGenericDocumentRecognitionResult.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 06.07.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKGenericDocument.h"

NS_ASSUME_NONNULL_BEGIN

/** The status of the generic document recognition. */
typedef NS_ENUM(NSUInteger, SBSDKGenericDocumentRecognitionStatus) {
    
    /** A document was found, cropped and it's fields have been recognized. */
    SBSDKGenericDocumentRecognitionStatusSuccess,
    
    /** A document was found and can be processed further. */
    SBSDKGenericDocumentRecognitionStatusSuccessFound,
    
    /** No document recognized. */
    SBSDKGenericDocumentRecognitionStatusErrorNothingFound,
    
    /** The document image could not be cropped correctly. */
    SBSDKGenericDocumentRecognitionStatusErrorBadCrop,
    
    /** No document recognized. The image was too blurry. */
    SBSDKGenericDocumentRecognitionStatusErrorTooBlurry
};

/** The recognition result of the SBSDKGenericDocumentRecognizer. */
@interface SBSDKGenericDocumentRecognitionResult : NSObject

/** The status of the recognition. */
@property(nonatomic, readonly) SBSDKGenericDocumentRecognitionStatus status;

/** The recognized generic document, if recognized. Nil otherwise. */
@property(nullable, nonatomic, readonly) SBSDKGenericDocument *document;

/** The image of the document, if recognized. Nil otherwise. */
@property(nullable, nonatomic, readonly) UIImage *croppedImage;

@end

NS_ASSUME_NONNULL_END
