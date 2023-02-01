//
//  SBSDKUIWorkflowScannerTextConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 21.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/** Text configuration object for a 'SBSDKUIWorkflowScannerViewController'. */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** The text being displayed on the user-guidance label, when no document was detected. */
@property (nullable, nonatomic, strong) NSString *textHintNothingDetected;

/** The text being displayed on the user-guidance label, when no document was detected because of image noise. */
@property (nullable, nonatomic, strong) NSString *textHintTooNoisy;

/** The text being displayed on the user-guidance label, when no document was detected because the image is too dark. */
@property (nullable, nonatomic, strong) NSString *textHintTooDark;

/**
 * The text being displayed on the user-guidance label, when a document was detected,
 * but the perspective distortion is too strong.
 */
@property (nullable, nonatomic, strong) NSString *textHintBadAngles;

/**
 * The text being displayed on the user-guidance label, when a document was detected,
 * but the aspect ratio of the document is inverse to the cameras aspect ratio.
 */
@property (nullable, nonatomic, strong) NSString *textHintBadAspectRatio;

/**
 * The text being displayed on the user-guidance label, when a document was detected,
 * but the documents area is too small compared to the image area.
 */
@property (nullable, nonatomic, strong) NSString *textHintTooSmall;

/**
 * The text being displayed on the user-guidance label, when a document was detected,
 * but its center is too far away from the image center.
 */
@property (nullable, nonatomic, strong) NSString *textHintOffCenter;

/** The text being displayed on the user-guidance label, when a document was detected with good conditions. */
@property (nullable, nonatomic, strong) NSString *textHintOK;

@end

NS_ASSUME_NONNULL_END
