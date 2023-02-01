//
//  SBSDKCheckRecognizerResult.h
//  ScanbotSDK
//
//  Created by Dmitry Zaytsev on 12/04/16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKCheckDocumentModel.h"

NS_ASSUME_NONNULL_BEGIN

/** An enum describing the status of a check recognition. */
typedef NS_ENUM(NSUInteger, SBSDKCheckRecognitionResultStatus) {
    /** A check has been recognized and validated successfully. */
    SBSDKCheckRecognitionResultStatusSuccess,

    /** A check has been recognized but the validation of its content has been failed. */
    SBSDKCheckRecognitionResultStatusValidationFailed,
};

/**
 * The result object of a check recognition.
 */
@interface SBSDKCheckRecognizerResult : NSObject

/** The status of the check recognition result. */
@property(nonatomic, assign) SBSDKCheckRecognitionResultStatus status;

/** The generic document for the found check. Nil, if the recognition was not successfull. */
@property(nonatomic, strong, nullable) SBSDKGenericDocument *document;

/** The image the check was recognized on. */
@property(nonatomic, strong, nullable) UIImage* checkImage;

/** A string representation of the receiver. */
@property(nonatomic, readonly) NSString *stringRepresentation;

@end

NS_ASSUME_NONNULL_END
