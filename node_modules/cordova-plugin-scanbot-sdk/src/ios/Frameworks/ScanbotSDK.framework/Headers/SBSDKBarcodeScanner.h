//
//  SBSDKBarcodeScanner.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 17.01.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SBSDKBarcodeScannerResult.h"
#import "SBSDKBarcodeAdditionalParameters.h"


/** The engine mode of the barcode recognizer. */
typedef NS_ENUM(NSUInteger, SBSDKBarcodeEngineMode) {
    /** Legacy mode. */
    SBSDKBarcodeEngineModeLegacy = 0,
    
    /** Next generation engine mode based on machine learning. */
    SBSDKBarcodeEngineModeNextGen = 1
};

/**
 * A class to search and decode multiple types of barcodes in a UIImage or SampleBufferRef.
 * Result is incapsulated in an array of SBSDKBarcodeScannerResult instances.
 */
@interface SBSDKBarcodeScanner : NSObject

/**
 * Creates an SBSDKBarcodeScanner with no frame accumulator for detecting all supported barcode types
 */
- (nonnull instancetype)init;

/**
 * Creates an SBSDKBarcodeScanner with no frame accumulator for detecting only the given barcode types
 * @param barCodeTypes Bar code types to limit detection results to.
 */
- (nonnull instancetype)initWithTypes:(nonnull NSArray<SBSDKBarcodeType *> *)barCodeTypes;

/**
 * Creates an SBSDKBarcodeScanner that accumulates multiple frames before returning a detection result.
 * The barcode scanner's detect* methods will return empty results until they've been called the
 * given number of times. Then, they will perform detection on the frame with the least
 * amount of blur. Intended for using with live detection.
 * @param barCodeTypes Bar code types to limit detection results to.
 * @param useLiveMode Whether you want to recognize in live mode or not.
 */
- (nonnull instancetype)initWithTypes:(nonnull NSArray<SBSDKBarcodeType *> *)barCodeTypes
                             liveMode:(BOOL)useLiveMode;

/**
 * Search and decode specified types of bar codes on given image.
 * Strong recommendation is to use this method with static image barcode detection and not live detection.
 * The reason is that video stream returns rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This method does not handle this orientation difference.
 * For live detection using `detectBarCodesOnImage:orientation:inRect:` or `detectBarCodesOnSampleBuffer:orientation:inRect:` is more preferable.
 * @param image The image where search is to be done.
 * @return List of found barcodes.
 */
- (nullable NSArray<SBSDKBarcodeScannerResult *> *)detectBarCodesOnImage:(nonnull UIImage *)image;

/**
 * Search and decode specified types of bar codes on given image.
 * Strong recommendation is to use this method with static image barcode detection and not live detection.
 * The reason is that video stream returns rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This method does not handle this orientation difference.
 * For live detection using `detectBarCodesOnImage:orientation:inRect:` or `detectBarCodesOnSampleBuffer:orientation:inRect:` is more preferable.
 * @param image The image where search is to be done.
 * @param rect Rectangle in image coordinates in which to perform the search. Must be inside the image.
 * @return List of found barcodes.
 */
- (nullable NSArray<SBSDKBarcodeScannerResult *> *)detectBarCodesOnImage:(nonnull UIImage *)image
                                                                  inRect:(CGRect)rect;

/**
 * Search and decode specified types of bar codes on given image.
 * This function is intended to be used use with live detection.
 * Video stream from device returns a rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This function handles these orientation differences, so you shouldn't fix or rotate the input image.
 * @param image The image where search is to be done.
 * @param videoOrientation Video frame orientation. Should be the orientation that the device currently has, not actual image orientation.
 * @param rect Rectangle in image coordinates in which to perform the search. Must be within the image frame.
 * @return List of found barcodes.
 */
- (nullable NSArray<SBSDKBarcodeScannerResult *> *)detectBarCodesOnImage:(nonnull UIImage *)image
                                                             orientation:(AVCaptureVideoOrientation)videoOrientation
                                                                  inRect:(CGRect)rect;

/**
 * Search and decode specified types of bar codes from sample buffer reference.
 * This function is intended to be used with live detection.
 * Video stream from device returns a rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This function handles these orientation differences, so you shouldn't fix or rotate the input buffer.
 * Keep in mind, that the buffer received from the video stream is handled by the system. So in some cases it might be cleaned or changed by the system
 * before recognition occurs. You may convert the buffer to UIImage upon receiving it and use `detectBarCodesOnImage:orientation:inRect:` function, if that is an issue.
 * @param sampleBuffer The sample buffer reference.
 * @param videoOrientation Video frame orientation. Should be the orientation that the device currently has, not actual image orientation.
 * @return List of found barcodes.
 */
- (nullable NSArray<SBSDKBarcodeScannerResult *> *)detectBarCodesOnSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                                                    orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Search and decode specified types of bar codes from sample buffer reference.
 * This function is intended to be used with live detection.
 * Video stream from device returns a rotated image, so for example for portrait device orientation, every frame returned will be in landscape left orientation.
 * This function handles these orientation differences, so you shouldn't fix or rotate the input buffer.
 * Keep in mind, that the buffer received from the video stream is handled by the system. So in some cases it might be cleaned or changed by the system
 * before recognition occurs. You may convert the buffer to UIImage upon receiving it and use `detectBarCodesOnImage:orientation:inRect:` function, if that is an issue.
 * @param sampleBuffer The sample buffer reference.
 * @param videoOrientation Video frame orientation. Should be the orientation that the device currently has, not actual image orientation.
 * @param rect Rectangle in image coordinates in which to perform the search. Must be inside the image.
 * @return List of found barcodes.
 */
- (nullable NSArray<SBSDKBarcodeScannerResult *> *)detectBarCodesOnSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                                                    orientation:(AVCaptureVideoOrientation)videoOrientation
                                                                         inRect:(CGRect)rect;

/**
 * Bar code types to limit detection results to. When nil or empty - all codes can be returned.
 * Default is nil.
 */
@property (nonatomic, strong, nullable) NSArray<SBSDKBarcodeType *> *acceptedBarcodeTypes;

/**
 * Bar code document types to limit detection results to. When nil or empty - all document can be returned.
 * Default is nil.
 */
@property (nonatomic, strong, nullable) NSArray<SBSDKBarcodeDocumentType *> *acceptedDocumentTypes;

/**
 * Additional parameters for tweaking the detection of barcodes.
 */
@property (nonatomic, strong, nonnull) SBSDKBarcodeAdditionalParameters *additionalParameters;

/**
 * The barcode detectors engine mode.
 * The default value is SBSDKBarcodeEngineModeNextGen.
 */
@property (nonatomic, assign) SBSDKBarcodeEngineMode engineMode;

/**
 * Set to YES, if you want to recognize barcodes on consecutive video frames.
 * Otherwise, if you want to recognize on a single image, set to NO.
 * The default value is NO.
 */
@property (nonatomic, assign) BOOL useLiveMode;

@end
