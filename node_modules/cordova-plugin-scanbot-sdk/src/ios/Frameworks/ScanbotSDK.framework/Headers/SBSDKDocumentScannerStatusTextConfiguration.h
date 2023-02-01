//
//  SBSDKDocumentScannerStatusTextConfiguration.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 14.04.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Wraps the texts being displayed as the detection status. */
@interface SBSDKDocumentScannerStatusTextConfiguration : NSObject

/** The text being displayed on the user-guidance label, when the scanners energy saver is activated. */
@property (nullable, nonatomic, strong) NSString *textHintEnergySavingActive;

/** The text being displayed on the user-guidance label, when no document was detected. */
@property (nullable, nonatomic, strong) NSString *textHintNothingDetected;

/** The text being displayed on the user-guidance label, when no document was detected because of image noise. */
@property (nullable, nonatomic, strong) NSString *textHintTooNoisy;

/** The text being displayed on the user-guidance label, when no document was detected because the image is too dark. */
@property (nullable, nonatomic, strong) NSString *textHintTooDark;

/** The text being displayed on the user-guidance label, when a document was detected, but the perspective distortion is too strong. */
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

/** The text being displayed on the user-guidance label, when a document was detected with good conditions. Used with `autoShutterEnabled` set to YES.*/
@property (nullable, nonatomic, strong) NSString *textHintOKAutoShutter;

/** The text being displayed on the user-guidance label, when a document was detected with good conditions. Used with `autoShutterEnabled` set to NO.*/
@property (nullable, nonatomic, strong) NSString *textHintOKManualScan;

@end

NS_ASSUME_NONNULL_END
