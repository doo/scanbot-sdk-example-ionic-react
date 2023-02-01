//
//  SBSDKUIDocumentScannerTextConfiguration.h
//  SBSDK Internal Demo
//
//  Created by Yevgeniy Knizhnik on 3/1/18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"
#import "SBSDKUIDocumentScannerAccessibilityConfiguration.h"

/** Configuration for the textual contents of the document scanning screen. */
@interface SBSDKUIDocumentScannerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the multi-page button. */
@property (nullable, nonatomic, strong) NSString *multiPageButtonTitle;

/** String being displayed on the auto-snapping button. */
@property (nullable, nonatomic, strong) NSString *autoSnappingButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the page-amount button additionally. Use %d as number formatting symbol. */
@property (nullable, nonatomic, strong) NSString *pageCounterButtonTitle;

/** The text being displayed on the user-guidance label, when no document was detected. */
@property (nullable, nonatomic, strong) NSString *textHintNothingDetected;

/** The text being displayed on the user-guidance label, when the scanners energy saver is activated. */
@property (nullable, nonatomic, strong) NSString *textHintEnergySavingActive;

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

/** String being displayed on the label describing that the app is in split mode and needs to go fullscreen to work with camera. */
@property (nonnull, nonatomic, strong) NSString *cameraUnavailableExplanationText;

/** The font size for the user guidance label in points. Defaults to 17. */
@property (nonatomic, assign) CGFloat textHintFontSize;

/** A configuration with accessibility texts settings. */
@property (nonnull, nonatomic, strong) SBSDKUIDocumentScannerAccessibilityConfiguration *accessibilityConfiguration;

@end
