//
//  SBSDKImageMetricsAnalyzer.h
//  
//
//  Created by Sebastian Husche on 03.01.19.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * Class containing the metrics for a single image channel.
 **/
@interface SBSDKImageChannelMetrics: NSObject

/** The minimum value of the image channel (0 - 255). **/
@property(nonatomic, readonly) double min;

/** The maximum value of the image channel (0 - 255). **/
@property(nonatomic, readonly) double max;

/** The average of all values of the image channel (0 - 255). **/
@property(nonatomic, readonly) double mean;

/** The variance of all values of the image channel. **/
@property(nonatomic, readonly) double variance;

/** The standard deviation of all values of the image channel. **/
@property(nonatomic, readonly) double stdDeviation;

/**
 * The sharpness or detail level of the image channel.
 * This is a logarithic measure for the high-frequency proportions of the image channel.
 * Ranges from 0.0 to around 20.0.
 * Values depend on general content of the image channel and are best analyzed in an empirical context.
 * Generally values below 1.0 mean very low detail or very high blurriness, rendering the image unusable.
 */
@property(nonatomic, readonly) double sharpness;

@end



/**
 * Utility class to extract the metrics for each individual channel of an UIImage.
 * Metrics are min, max and mean values of each channel, the variance and standard deviation.
 * Along with the metrics this class also extracts histograms and cumulative histograms for each channel.
**/
@interface SBSDKImageMetricsAnalyzer : NSObject

/** The number of channels of the input image. **/
@property(nonatomic, readonly) NSInteger numberOfChannels;

/** An array of SBSDKImageChannelMetrics objects in the order of the images channels. **/
@property(nonatomic, readonly) NSArray<SBSDKImageChannelMetrics*>* allChannelMetrics;

/**
 * Designated initializer.
 * @param image The image to extract metrics and histograms from.
 * @param convertToHSV If set to YES, the image is converted to the hue-saturation-value system.
 * So instead of R-, G- and B-channels the metrics are created for hue, saturation and value (brightness).
 **/
- (instancetype)init:(UIImage *)image convertToHSV:(BOOL)convertToHSV;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Returns the metrics for the channel with the given index.
 * @param channelIndex The index for the channel. Passing an invalid index will return nil.
 * @return The metrics object for the given channel or nil.
 **/
- (nullable SBSDKImageChannelMetrics *)metricsAtChannel:(NSInteger)channelIndex;

/**
 * Returns the number of pixels for a given histogram bin and channel.
 * @param index The index (0-255) of the histogram bin. Passing an invalid index will lead to crash.
 * @param channelIndex The index for the channel. Passing an invalid index will lead to a crash.
 * @return Number of pixels in the bin.
 **/
- (double)histogramValueAt:(NSInteger)index inChannel:(NSInteger)channelIndex;

/**
 * Returns an array with 256 entries, each containing a NSNumber object with the number of pixels being in the corresponding histogram bin.
 * @param channelIndex The index for the channel. Passing an invalid index will lead to a crash.
 * @return An array of 256 NSNumber objects.
 **/
- (NSArray<NSNumber*>*)histogramValuesInChannel:(NSInteger)channelIndex;

/**
 * Returns the number of pixels for a given cumulative histogram bin and channel.
 * @param index The index (0-255) of the cumulative histogram bin. Passing an invalid index will lead to crash.
 * @param channelIndex The index for the channel. Passing an invalid index will lead to a crash.
 * @return Number of pixels in the bin.
 **/
- (double)cumulativeHistogramValueAt:(NSInteger)index inChannel:(NSInteger)channelIndex;

/**
 * Returns an array with 256 entries, each containing a NSNumber object with the number of pixels being in the corresponding cumulative histogram bin.
 * @param channelIndex The index for the channel. Passing an invalid index will lead to a crash.
 * @return An array of 256 NSNumber objects.
 **/
- (NSArray<NSNumber*>*)cumulativeHistogramValuesInChannel:(NSInteger)channelIndex;

@end

NS_ASSUME_NONNULL_END
