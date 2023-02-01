//
//  SBSDKMedicalCertificateScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 19.01.22.
//  Copyright © 2022 doo GmbH. All rights reserved.
//

#import "SBSDKBaseScannerViewController.h"
#import "SBSDKMedicalCertificateRecognizer.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKMedicalCertificateScannerViewController;

/**
 * The live recognition state of the medical certificate scanner.
 */
typedef NS_ENUM(NSUInteger, SBSDKMedicalCertificateScannerState) {
    /** The medical certificate scanner searches for medical certificate. */
    SBSDKMedicalCertificateScannerStateSearching,

    /** The medical certificate scanner recognizes medical certificate. */
    SBSDKMedicalCertificateScannerStateRecognizing,
    
    /** The medical certificate scanner captures a high-res photo of a medical certificate. */
    SBSDKMedicalCertificateScannerStateCapturing,

    /** The medical certificate scanner is in energy saving mode. */
    SBSDKMedicalCertificateScannerStateEnergySaving,

    /** The medical certificate scanner paused the detection and recognition. */
    SBSDKMedicalCertificateScannerStatePaused
};

/**
 * The delegation protocol for the `SBSDKMedicalCertificateScannerViewController` class.
 */
@protocol SBSDKMedicalCertificateScannerViewControllerDelegate <NSObject>

/**
 * Informs the delegate, that the medical certificate scanner has successfully
 * detected and recognized a medical certificate.
 * @param controller The medical scanner viewcontroller which recognized the medical certificate.
 * @param result The medical scanner result that have been recognized.
 */
- (void)medicalCertificateScannerViewController:(SBSDKMedicalCertificateScannerViewController *)controller
                 didRecognizeMedicalCertificate:(SBSDKMedicalCertificateRecognizerResult *)result;

@optional

/**
 * Asks the delegate if the medical certificate scanner should scan the next video frame.
 * @param controller The medical scanner viewcontroller that will receive the video frame.
 * @return Return YES to run the recognition on the next video frame, NO otherwise. Can be used to pause the detection.
 */
- (BOOL)medicalCertificateScannerViewControllerShouldRecognize:(SBSDKMedicalCertificateScannerViewController *)controller;

/**
 * Informs the delegate, that the medical certificate scanner has changed its detection/recognition state.
 * @param controller The medical scanner viewcontroller that changed its state.
 * @param state The current state of the medical certificate scanner.
*/
- (void)medicalCertificateScannerViewController:(SBSDKMedicalCertificateScannerViewController *)controller
                                 didChangeState:(SBSDKMedicalCertificateScannerState)state;

@end

/**
 * Classic UI viewcontroller that can be used to detect and recognize medical certificates. Can be configured to
 * recognize on video frames or, for better accuracy, on high-res photos that are automatically captured.
 */
@interface SBSDKMedicalCertificateScannerViewController : SBSDKBaseScannerViewController

/** The current state of the medical certificate scanner. */
@property(nonatomic, readonly) SBSDKMedicalCertificateScannerState state;

/** Whether the information of the patient (name, address) is extracted or not. The default value is YES. */
@property(nonatomic, assign) BOOL extractPatientInfo;

/** Whether eventual barcodes or data matrices on the medical certificates extracted or not. The default value is YES. */
@property(nonatomic, assign) BOOL extractBarcode;

/**
 * If set to YES a high-resolution photo of the medical certificate is captured to run the recognition on.
 * Upon successful recognition the recognition result also contains a high-resolution image of the medical certificate.
 * If set to NO, the video frames will be used for recognition and result image delivery.
 * The default value is YES.
 */
@property(nonatomic, assign) BOOL captureHighResolutionImage;

/** The delegate of the receiver. */
@property(nonatomic, weak) id<SBSDKMedicalCertificateScannerViewControllerDelegate>delegate;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
* Designated initializer. Installs the medical certificate scanner as child view controller onto the parent
* viewcontrollers view hierarchy.
* @param parentViewController The view controller the newly created instance is embedded into.
* If parentViewController conforms to SBSDKMedicalCertificateScannerViewControllerDelegate,
* it is automatically set as delegate.
* @param containerView The view the newly created instance is embedded into. If nil the parent viewcontrollers
* view is used.
* @param device The camera device to be used for scanning. If nil the default camera will be used.
* @param delegate The delegate of the medical certificate scanner.
*/
- (nullable instancetype)initWithParentViewController:(nullable UIViewController *)parentViewController
                                           parentView:(nullable UIView *)containerView
                                               device:(nullable SBSDKCameraDevice *)device
                                             delegate:(id<SBSDKMedicalCertificateScannerViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
