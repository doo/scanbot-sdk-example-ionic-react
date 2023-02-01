//
//  SBSDKGenericTextLineRecognizerResult.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 30.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SBSDKBoxedObject.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A class describing a recognized word, its bounding box and its text recognition confidence.
 */
@interface SBSDKGenericTextLineRecognizerResultWordBox : NSObject <SBSDKBoxedObject>

/** The recognized word. */
@property (nonatomic, strong) NSString* word;

/** The recognized words bounding rect. */
@property (nonatomic, assign) CGRect boundingRect;

/** The recognized words confidence value. */
@property (nonatomic, assign) double confidenceValue;

@end

/**
 * A class describing the result of the generic text line recognizer.
 */
@interface SBSDKGenericTextLineRecognizerResult : NSObject

/** YES, if the validation was successful. NO otherwise */
@property (nonatomic, assign) BOOL validationSuccessful;

/** The recognized text. */
@property (nonatomic, strong) NSString *text;

/** The recognition confidence value. */
@property (nonatomic, assign) double confidenceValue;

/** An array of the recognized word boxes. */
@property (nonatomic, strong) NSArray<SBSDKGenericTextLineRecognizerResultWordBox *> *wordBoxes;

@end

NS_ASSUME_NONNULL_END
