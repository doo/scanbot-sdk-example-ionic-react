//
//  SBSDKMedicalCertificateRecognizer.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 14.11.17.
//  Copyright © 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import "SBSDKMedicalCertificateRecognizerResult.h"
#import "SBSDKMedicalCertificateRecognizerDateResult.h"
#import "SBSDKMedicalCertificateRecognizerCheckboxResult.h"
#import "SBSDKMedicalCertificateRecognizerConfigurationOptions.h"

/**
 * A class to recognize medical certificates in a UIImage or CMSampleBufferRef.
 * The result is encapsulated in SBSDKMedicalCertificateRecognizerResult instance.
 */
@interface SBSDKMedicalCertificateRecognizer : NSObject

/**
 * The options to be used with the medical certificates recognizer.
 */
@property (nonnull, nonatomic, strong) SBSDKMedicalCertificateRecognizerConfigurationOptions *recognitionOptions;

/**
 * The designated initializer.
 * @param options The options used to create a new medical certificates recognizer.
 */
- (nonnull instancetype)initWithConfigurationOptions:(SBSDKMedicalCertificateRecognizerConfigurationOptions *_Nonnull)options;

/**
 * Acquires all available information from an UIImage instance.
 * @param image The image with the detected medical certificate.
 * @param detectDocument Pass NO, if the image contains the medical certificate without borders. Pass YES, if there is more content on the image, e.g. a photo of the medical certificate with surroundings.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)recognizeFromImage:(nonnull UIImage *)image detectDocument:(BOOL)detectDocument;

/**
 * Detects the document and acquires all available information from a sample buffer reference.
 * @param sampleBufferRef The sample buffer reference containing the detected medical certificate.
 * @param detectDocument Pass NO, if the image contains the medical certificate without borders. Pass YES, if there is more content on the image, e.g. a photo of the medical certificate with surroundings.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                     orientation:(AVCaptureVideoOrientation)videoOrientation
                                                                  detectDocument:(BOOL)detectDocument;

/**
 * Detects the document and acquires all available information from an UIImage instance.
 * @param image The image with the detected medical certificate.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)detectAndRecognizeFromImage:(nonnull UIImage *)image __attribute__((deprecated("Please use recognizeFromImage:detectDocument:")));

/**
 * Detects the document and acquires all available information from a sample buffer reference.
 * @param sampleBufferRef The sample buffer reference containing the detected medical certificate.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)detectAndRecognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                                 orientation:(AVCaptureVideoOrientation)videoOrientation __attribute__((deprecated("Please use recognizeFromSampleBuffer:orientation:detectDocument:")));

/**
 * Acquires all available information from an UIImage instance.
 * @param image The image with the detected medical certificate.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)recognizeFromImage:(nonnull UIImage *)image __attribute__((deprecated("Please use recognizeFromImage:detectDocument:")));

/**
 * Acquires all available information from a sample buffer reference.
 * @param sampleBufferRef The sample buffer reference containing the detected medical certificate.
 * @return The recognizer result.
 */
- (nullable SBSDKMedicalCertificateRecognizerResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                        orientation:(AVCaptureVideoOrientation)videoOrientation __attribute__((deprecated("Please use recognizeFromSampleBuffer:orientation:detectDocument:")));

@end
