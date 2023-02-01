//
//  SBSDKMachineReadableZoneRecognizer.h
//  ScanbotSDK
//
//  Created by Andrew Petrus on 28.09.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import "SBSDKMachineReadableZoneRecognizerResult.h"

/**
 * A class to recognize machine-readable zones in a UIImage or SampleBufferRef.
 * Result is encapsulated in SBSDKMRZRecognizerResult instance.
 * NOTE: In order to operate, this class requires tesseract languages and trained data to be present
 * in application bundle
 */
@interface SBSDKMachineReadableZoneRecognizer : NSObject

/**
 * The number of frames to be accumulated results when recognizing machine readable zones. 
 * Lower values are more inaccurate but faster, higher values are more accurate but slower. 
 * Values less than or equal 1 effectively turn accumulation off.
 * The default value is 4.
 */
@property (nonatomic, assign) NSUInteger resultAccumulationCount;

/**
 * Acquire all available information from UIImage instance containing machine-readable zone.
 * @param image The image where machine-readable zone is to be detected.
 * @return Recognizer result or nil.
 */
- (nullable SBSDKMachineReadableZoneRecognizerResult *)recognizePersonalIdentityFromImage:(nonnull UIImage *)image;

/**
 * Acquire all available information from previously extracted MRZ text.
 * @param text Text with extracted MRZ data.
 * @return Recognizer result or nil.
 */
- (nullable SBSDKMachineReadableZoneRecognizerResult *)recognizePersonalIdentityFromText:(nonnull NSString *)text;

/**
 * Acquire all available information from sample buffer reference containing machine-readable zone.
 * @param sampleBufferRef The sample buffer reference containing machine-readable zone.
 * @param videoOrientation Video frame orientation.
 * @param machineReadableZoneRect Rectangle in frame containing machine-readable zone. Pass an empty rectangle
 * if no frame is used.
 * @return Recognizer result or nil.
 */
- (nullable SBSDKMachineReadableZoneRecognizerResult *)recognizePersonalIdentityFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                                    orientation:(AVCaptureVideoOrientation)videoOrientation
                                                                        machineReadableZoneRect:(CGRect)machineReadableZoneRect;

@end
