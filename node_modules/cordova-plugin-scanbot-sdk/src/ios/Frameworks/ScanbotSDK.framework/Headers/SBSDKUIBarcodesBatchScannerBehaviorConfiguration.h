//
//  SBSDKUIBarcodesBatchScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 12.03.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKBarcodeImageGenerationType.h"
#import "SBSDKBarcodeAdditionalParameters.h"
#import "SBSDKBarcodeScanner.h"
#import "SBSDKZoomRange.h"
#import "SBSDKUIBarcodeFiltering.h"

/**
 * Configuration for the behavior of  barcodes.
 */
@interface SBSDKUIBarcodesBatchScannerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

/** Whether scanner screen should make a sound on successful barcode or MRZ detection. */
@property (nonatomic, assign, getter=isSuccessBeepEnabled) BOOL successBeepEnabled;

/** 
 * The types of codes to be detected. 
 * The default value is nil, all code types are being detected. 
 */
@property (nullable, nonatomic, strong) NSArray<SBSDKBarcodeType *> *acceptedMachineCodeTypes;

/** 
 * The types of documents being extracted from scanned codes. 
 * The default value is nil, all document types are being extracted. 
 */
@property (nullable, nonatomic, strong) NSArray<SBSDKBarcodeDocumentType *> *acceptedDocumentTypes;

/**
 * Additional parameters for tweaking the detection of barcodes.
 */
@property (nonatomic, strong, nonnull) SBSDKBarcodeAdditionalParameters *additionalDetectionParameters;

/**
 * The barcode detectors engine mode.
 * The default value is SBSDKBarcodeEngineModeNextGen.
 */
@property (nonatomic, assign) SBSDKBarcodeEngineMode engineMode;

/**
 * The range of valid camera zoom factors. Default value is (1.0; 3.0).
 */
@property (nonatomic, strong, nonnull) SBSDKZoomRange *cameraZoomRange;

/**
 * The relative zoom level of the camera relative to `zoomRange`.
 * The minimum value is 0.0 (zoomed out), the maximum value is 1.0 (zoomed in).
 * The default value is 0.0, zoomed out.
 *
 * You can use this value to zoom the camera programmatically but also to set an initial zoom factor.
 */
@property (nonatomic, assign) CGFloat cameraZoomFactor;

/**
 * When this property is set to YES, the zoom can be activated by double tapping
 * somewhere in the receivers view.
 * The default value is YES.
 */
@property(nonatomic, assign, getter=isDoubleTapToZoomEnabled) BOOL doubleTapToZoomEnabled;

/**
 * When this property is set to YES, the zoom can be activated by a pinch gesture
 * somewhere in the receivers view.
 * The default value is YES.
 */
@property(nonatomic, assign, getter=isPinchToZoomEnabled) BOOL pinchToZoomEnabled;

/**
 * Defines, if zooming in or out should be animated.
 * The default value is YES;
 */
@property (nonatomic, assign) BOOL shouldAnimateZooming;

/**
 * Additional filter to reject or accept barcode scanner results.
 * The default value is an instance of SBSDKUIBarcodeFilter.
 */
@property (nonatomic, strong, nonnull) SBSDKUIBarcodeFilter* barcodeFilter;

/**
 * Disables auto-focus and locks the lens at the specified focus lock lens position. The default value is NO.
 */
@property (nonatomic, assign, getter=isFocusLockEnabled) BOOL focusLockEnabled;

/**
 * The position of the lens. Values can be between 0.0f (minimum focusing distance) and
 * 1.0f (maximum focusing distance). The value will be clamped to [0.0f, 1.0f]. The default value is 0.0.
 */
@property (nonatomic, assign) CGFloat focusLockPosition;

/** The initial recognition delay in seconds. Defaults to 0.0. */
@property (nonatomic, assign) NSTimeInterval initialScanDelay;

@end

