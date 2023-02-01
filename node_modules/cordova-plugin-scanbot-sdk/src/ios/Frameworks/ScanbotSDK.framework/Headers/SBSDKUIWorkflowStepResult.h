//
//  SBSDKUIWorkflowStepResult.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 23.11.18.
//  Copyright © 2018 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIPage.h"
#import "SBSDKDocumentDetectorResult.h"
#import "SBSDKOCRResult.h"
#import "SBSDKMachineReadableZoneRecognizerResult.h"
#import "SBSDKMedicalCertificateRecognizerResult.h"
#import "SBSDKHealthInsuranceCardRecognitionResult.h"
#import "SBSDKCheckRecognizerResult.h"
#import "SBSDKPayFormScanner.h"
#import "SBSDKBarcodeScannerResult.h"

@class SBSDKUIWorkflowStep;

NS_ASSUME_NONNULL_BEGIN

/** This class represents the result of one workflow step */
__deprecated_msg("Will be removed soon.")
@interface SBSDKUIWorkflowStepResult : NSObject

/** The workflow step the receiver belongs to. */
@property(nonnull, nonatomic, readonly) SBSDKUIWorkflowStep *step;

/** If the validation of the workflow step returns an error, it is stored here. Nil if validation was successful. */
@property(nullable, nonatomic, readonly) NSError *validationError;

/** The high-res still image, if the step requested one. */
@property(nullable, nonatomic, strong) SBSDKUIPage* capturedPage;

/** The low-res video frame image, if the step requested one. */
@property(nullable, nonatomic, strong) SBSDKUIPage* videoFramePage;

/** Array of detected machine readable codes, if the step requested them. */
@property(nullable, nonatomic, strong) NSArray<SBSDKBarcodeScannerResult *> *barcodeResults;

/** The machine readable zone recognition result, if requested by the step. */
@property(nullable, nonatomic, strong) SBSDKMachineReadableZoneRecognizerResult *mrzResult;

/** The medical certificate recognition result, if requested by the step. */
@property(nullable, nonatomic, strong) SBSDKMedicalCertificateRecognizerResult *disabilityCertificateResult __attribute__((deprecated("Deprecated.")));;

/** The payform recognition result, if requested by the step. */
@property(nullable, nonatomic, strong) SBSDKPayFormRecognitionResult *payformResult;

/** The health insurance card recognition result, if requested by the step. */
@property(nullable, nonatomic, strong) SBSDKHealthInsuranceCardRecognitionResult *ehicResult;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer.
 * Usually you must not create instances of this class, except when you create custom workflow steps.
 * @param step The workflow step this result belongs to.
 */
- (instancetype)initWithStep:(nonnull SBSDKUIWorkflowStep *)step;

/**
 * A thumbnail of either the high-res still image or the low-res video frame, depending on what was requested.
 * If none of both was requested thumbnail may be nil.
 */
- (nullable UIImage *)thumbnail;

@end

NS_ASSUME_NONNULL_END
