//
//  SBSDKDocumentDetector.h
//  doo-ios
//
//  Created by Sebastian Husche on 28.11.13.
//  Copyright (c) 2013 doo GmbH. All rights reserved.
//

#import "SBSDKDocumentDetectionStatus.h"
#import <AVFoundation/AVFoundation.h>
#import "SBSDKPolygon.h"
#if TARGET_OS_IPHONE
#import "SBSDKDeviceInformation.h"
#else
#import <Cocoa/Cocoa.h>
#endif

#import "SBSDKGeometryUtilities.h"
#import "SBSDKDocumentDetectorResult.h"
#import "SBSDKAspectRatio.h"

/**
 * The mode of the document detector: standard or machine-learning-based.
 */
typedef NS_ENUM(NSInteger, SBSDKDocumentDetectorMode) {
    /** The standard detection mode. */
    SBSDKDocumentDetectorModeStandard = 0,

    /** The new machine-learning based detection mode. */
    SBSDKDocumentDetectorModeMachineLearning = 1
};

/**
 * A class to detect a document's outline polygon in a UIImage or CMSampleBufferRef.
 */
@interface SBSDKDocumentDetector : NSObject


#if TARGET_OS_IPHONE
/**
 * Executes an edge detection algorithm on the given image and returns
 * a polygon describing the extends of the detected documents box.
 * For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 * @param image The image to analyze.
 * @param visibleRect The unified image rectangle that should be analyzed.
 * (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 * @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 * you should call resetSmoothingData regularly.
 * @param liveDetection Set YES if you want to use faster live detection. Live detection is less reliable than normal detection.
 * @return The detection result containing the status and a polygon.
 */
- (nonnull SBSDKDocumentDetectorResult *)detectDocumentPolygonOnImage:(nonnull UIImage *)image
                                                     visibleImageRect:(CGRect)visibleRect
                                                     smoothingEnabled:(BOOL)smooth
                                           useLiveDetectionParameters:(BOOL)liveDetection;

/**
 * Executes an edge detection algorithm on the given image and returns
 * a polygon describing the extends of the detected photos box.
 * For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 * @param image The image to analyze.
 * @param visibleRect The unified image rectangle that should be analyzed.
 * (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 * @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 * you should call resetSmoothingData regularly.
 * @return The detection result containing the status and a polygon.
 */
- (nonnull SBSDKDocumentDetectorResult* )detectPhotoPolygonOnImage:(nonnull UIImage *)image
                                                  visibleImageRect:(CGRect)visibleRect
                                                  smoothingEnabled:(BOOL)smooth;

/**
 * Executes an edge detection algorithm on the given sample buffer and returns
 * a polygon describing the extends of the detected documents box.
 * For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 * @param sampleBuffer The CMSampleBufferRef to analyze.
 * @param visibleRect The unified image rectangle that should be analyzed.
 * (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 * @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 * you should call resetSmoothingData regularly.
 * @param liveDetection Set YES if you want to use faster live detection. Live detection is less reliable than normal detection.
 * @return The detection result containing the status and a polygon.
 */
- (nonnull SBSDKDocumentDetectorResult *)detectDocumentPolygonOnSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                                            visibleImageRect:(CGRect)visibleRect
                                                            smoothingEnabled:(BOOL)smooth
                                                  useLiveDetectionParameters:(BOOL)liveDetection;


/**
 * Executes an edge detection algorithm on the given sample buffer and returns
 * a polygon describing the extends of the detected photos box.
 * For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 * @param sampleBuffer The CMSampleBufferRef to analyze.
 * @param visibleRect The unified image rectangle that should be analyzed.
 * (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 * @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 * you should call resetSmoothingData regularly.
 * @return The detection result containing the status and a polygon.
 */
- (nonnull SBSDKDocumentDetectorResult *)detectPhotoPolygonOnSampleBuffer:(nonnull CMSampleBufferRef)sampleBuffer
                                                         visibleImageRect:(CGRect)visibleRect
                                                         smoothingEnabled:(BOOL)smooth;

#else
    
- (nonnull SBSDKDocumentDetectorResult *)detectDocumentPolygonOnImage:(nonnull NSImage *)image
                                                     visibleImageRect:(CGRect)visibleRect
                                                     smoothingEnabled:(BOOL)smooth
                                           useLiveDetectionParameters:(BOOL)liveDetection;
    
- (nonnull SBSDKDocumentDetectorResult* )detectPhotoPolygonOnImage:(nonnull NSImage *)image
                                                  visibleImageRect:(CGRect)visibleRect
                                                  smoothingEnabled:(BOOL)smooth;
#endif

/**
 * The current mode of the detector: standard or machine-learning-based.
 * Defaults to ML mode.
 */
@property (nonatomic, readonly) SBSDKDocumentDetectorMode detectorMode;

/** Default `detectorMode` parameter value. Unless the new instance of detector is initialized with
 * `- (nonnull instancetype)initWithMode:(SBSDKDocumentDetectorMode)mode;` initializer,
 * this new instance will have this mode set.
 */
+ (SBSDKDocumentDetectorMode)defaultDetectorMode;

/** Set default detector mode. Unless the new instance of detector is initialized with
 * `- (nonnull instancetype)initWithMode:(SBSDKDocumentDetectorMode)mode;` initializer,
 *  this new instance will have this mode set.
 */
+ (void)setDefaultDetectorMode:(SBSDKDocumentDetectorMode)newDefaultDetectorMode;

/**
 * Designated initialiizer.
 * @param mode The detection mode of the receiver.
*/
- (nonnull instancetype)initWithMode:(SBSDKDocumentDetectorMode)mode;

/**
 * Resets the smootingData. If smoothing is enabled the polygon detector smoothes the result with results from
 * previous detections. You should call this method once per second or if the device has been moved.
 */
- (void)resetSmoothingData;

/**
 * The minimum size in percent (0 - 100) of the screen size to accept a detected document.
 * It is sufficient that height or width match the score. Default is 80.0.
 * Warning: Lower values result in low resolution document images.
 */
@property(nonatomic, assign) double acceptedSizeScore;

/**
 * The minimum score in percent (0 - 100) of the perspective distortion to accept a detected document.
 * Default is 75.0. Set lower values to accept more perspective distortion.
 * Warning: Lower values result in more blurred document images.
 */
@property(nonatomic, assign) double acceptedAngleScore;

/** The total score of the latest detected polygon (0 - 100). */
@property(readonly) double currentTotalScore;

/** The size score of the latest detected polygon (0 - 100). Part of the total score. */
@property(readonly) double currentSizeScore;

/** The width score of the latest detected polygon (0 - 100). Part of the size score. */
@property(readonly) double currentWidthScore;

/** The height score of the latest detected polygon (0 - 100). Part of the size score. */
@property(readonly) double currentHeightScore;

/** The angles score of the latest detected polygon (0 - 100). Part of the total score. */
@property(readonly) double currentAngleScore;

/** The distance-from-center score of the latest detected polygon (0 - 100). Part of the total score. */
@property(readonly) double currentDistanceScore;

/** The metrics of the last detection or nil. **/
@property(readonly, nullable) SBSDKDocumentDetectionMetrics *detectionMetrics;

/** Preferred aspect ratios for detector.
 * If nil or empty, aspect ratio will not take part in defining best document polygon.
 * If set, polygons with set aspect ratio will be more preferrable.
 * Default is nil.
 */
@property(nonatomic, strong, nullable) NSArray<SBSDKAspectRatio *> *preferredAspectRatios;

/** Required aspect ratios for detector.
 * If not nil or empty, only polygons resulting in crops with one of the required aspect ratios will be detected.
 * Default is nil.
 */
@property(nonatomic, strong, nullable) NSArray<SBSDKAspectRatio *> *requiredAspectRatios;

/** Array of all detected horizontal edges during last detection. Can be used for manual magnetic cropping. */
@property(nonatomic, strong, readonly, nullable) NSArray<SBSDKPolygonEdge *> *detectedHorizontalEdges;

/** Array of all detected vertical edges during last detection. Can be used for manual magnetic cropping. */
@property(nonatomic, strong, readonly, nullable) NSArray<SBSDKPolygonEdge *> *detectedVerticalEdges;

@end
