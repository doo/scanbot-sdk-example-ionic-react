#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

#import "SBSDKHealthInsuranceCardRecognitionResult.h"

/**
 * A class to recognize European health insurance cards (EHIC), a.k.a. elektronische Gesundheitskarten (eGK).
 * NOTE: In order to operate, this class requires tesseract languages and trained data to be present
 * in the application bundle.
 */
@interface SBSDKHealthInsuranceCardRecognizer : NSObject

/**
 * Extracts EHIC data fields from a still image.
 * @param image An image of an EHIC.
 * @return Recognizer result. nil if recognition failed or validation is unsuccessful.
 */
- (nullable SBSDKHealthInsuranceCardRecognitionResult *)recognizeFromStillImage:(nonnull UIImage *)image;

/**
 * Extracts EHIC data fields from a video frame image. Call this method on consecutive video frames which have been
 * converted to UIImage.
 * @param image A video frame image of an EHIC.
 * @return Recognizer result. nil if recognition failed or validation is unsuccessful.
 */
- (nullable SBSDKHealthInsuranceCardRecognitionResult *)recognizeFromVideoFrameImage:(nonnull UIImage *)image;

/**
 * Extracts EHIC data fields from a sample buffer reference
 * @param sampleBufferRef The sample buffer reference possibly containing an EHIC.
 * @return Recognizer result. nil if recognition failed or validation is unsuccessful.
 */
- (nullable SBSDKHealthInsuranceCardRecognitionResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                      orientation:(AVCaptureVideoOrientation)videoOrientation;

/**
 * Extracts EHIC data fields from a sample buffer reference
 * @param sampleBufferRef The sample buffer reference possibly containing an EHIC.
 * @param searchInRect Rectangle in video frame, where recognizer will try to recognize the data.
 * @return Recognizer result. nil if recognition failed or validation is unsuccessful.
 */
- (nullable SBSDKHealthInsuranceCardRecognitionResult *)recognizeFromSampleBuffer:(nonnull CMSampleBufferRef)sampleBufferRef
                                                                     searchInRect:(CGRect)searchInRect
                                                                      orientation:(AVCaptureVideoOrientation)videoOrientation;

@end
