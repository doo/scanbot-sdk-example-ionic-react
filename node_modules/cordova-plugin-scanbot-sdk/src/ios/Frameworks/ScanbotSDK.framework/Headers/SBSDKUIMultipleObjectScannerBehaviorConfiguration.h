//
//  SBSDKUIMultipleObjectScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 03.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKVideoContentMode.h"
#import "SBSDKImageFilterTypes.h"
#import "SBSDKAspectRatioRange.h"

/** Configuration for the behavior of the document scanning screen. */
@interface SBSDKUIMultipleObjectScannerBehaviorConfiguration : NSObject

/** Whether multi-page snapping is enabled or not. Default is NO. */
@property (nonatomic, assign, getter=isBatchModeEnabled) BOOL batchModeEnabled;

/** Whether flash is toggled on or off. Default is NO. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** The video layers content mode. Default is `SBSDKVideoContentModeFillIn` */
@property (nonatomic) SBSDKVideoContentMode cameraPreviewMode;

/** Maximum number of pages to scan. Ignored when set to nil, or when `batchModeEnabled` is NO. Default is nil. */
@property (nullable, nonatomic, strong) NSNumber *maxNumberOfPages;

/**
 * Defines aspect ratio range. Only objects that are within this range will be detected. The default range is `1:2 - 2:1`.;
 */
@property (nonatomic, strong, nonnull) SBSDKAspectRatioRange *aspectRatioRange;

@end
