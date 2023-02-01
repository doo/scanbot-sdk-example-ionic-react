//
//  SBSDKUICheckRecognizerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Seifeddine Bouzid on 12.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKCheckRecognizer.h"
#import "SBSDKAspectRatio.h"

/**
 * Configuration for the behavior of the check scanner.
 */
@interface SBSDKUICheckRecognizerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. The default value is NO. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/**
 * If set to YES a high-resolution photo of the check is captured to run the recognition on.
 * Upon successful recognition the recognition result also contains a high-resolution image of the check.
 * If set to NO, the video frames will be used for recognition and result image delivery.
 * The default value is YES.
 */
@property (nonatomic, assign) BOOL captureHighResolutionImage;

/** An array of accepted check types. By default all check types are allowed. */
@property (nonnull, nonatomic, copy) NSArray<SBSDKCheckDocumentRootType *>* acceptedCheckStandards;

/** The aspect ratio of the view finder. Set to nil, if no finder should be used. The default value is 8.5 x 4.5. */
@property (nullable, nonatomic, strong) SBSDKAspectRatio *finderAspectRatio;

@end
