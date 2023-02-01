//
//  SBSDKGenericDocumentRecognizerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 16.04.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKGenericDocumentRecognizer.h"
#import "SBSDKBaseScannerViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class SBSDKGenericDocumentRecognizerViewController;

/** The delegate protocol for the SBSDKGenericDocumentRecognizerViewController. */
@protocol SBSDKGenericDocumentRecognizerViewControllerDelegate <NSObject>

/**
 * Informs the delegate that a document has been recognized successfully.
 * @param controller The SBSDKGenericDocumentRecognizerViewController instance that recognized the document.
 * @param result The recognition result.
 * @param image The original image where the document has been recognized on.
 */
- (void)documentRecognizerViewController:(SBSDKGenericDocumentRecognizerViewController *)controller
                      didRecognizeResult:(SBSDKGenericDocumentRecognitionResult *)result
                                 onImage:(UIImage *)image;

@end


/**
 * A UIViewController subclass to recognize  documents, e.g. German passports, ID cards and driver's licenses on video frames.
 */
@interface SBSDKGenericDocumentRecognizerViewController : SBSDKBaseScannerViewController

/** The receivers delegate. */
@property (nonatomic, readonly, weak) id<SBSDKGenericDocumentRecognizerViewControllerDelegate> delegate;

/**
 * The accepted minimal sharpness score. Images with a score less than that will
 * be rejected with blurry status.
 *
 * 0 - any image will be accepted.
 * 80 - a good compromise; the recommended setting.
 * 100 - only very sharp images will be accepted.
 *
 * The default value is 80.
 */
@property (nonatomic, assign) CGFloat sharpnessAcceptanceFactor;

/**
 * The array of recognizable document types. Readonly.
 */
@property (nonnull, nonatomic, readonly) NSArray<SBSDKGenericDocumentRootType *>* acceptedDocumentTypes;

/**
 * An array of normalized names for the document field types that should not be recognized. If nil all the fields are going to be recognized.
 */
@property (nullable, nonatomic, readonly) NSArray<NSString *> *excludedFieldTypes;

/** Not available. */
- (nonnull instancetype)init NS_UNAVAILABLE;

/** Not available. */
+ (nonnull instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * If parentViewController conforms to SBSDKGenericDocumentRecognizerViewControllerDelegate, it is automatically set as delegate.
 * @param parentView The view the newly created instance is embedded into.
 * If nil the parentViewControllers view is used.
 * @param acceptedDocumentTypes Array of document types to be recognized.
 * @param delegate The delegate of the receiver.
*/
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)parentView
                                acceptedDocumentTypes:(nonnull NSArray<SBSDKGenericDocumentRootType*> *)acceptedDocumentTypes
                                             delegate:(id<SBSDKGenericDocumentRecognizerViewControllerDelegate>)delegate;

/**
 * Convenient initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into.
 * If parentViewController conforms to SBSDKGenericDocumentRecognizerViewControllerDelegate, it is automatically set as delegate.
 * @param parentView The view the newly created instance is embedded into.
 * If nil the parentViewControllers view is used.
 * @param acceptedDocumentTypes Array of document types to be recognized.
 * @param excludedFieldTypes An array of normalized names for the document field types that should not be recognized.
 * @param delegate The delegate of the receiver.
*/
- (nullable instancetype)initWithParentViewController:(nonnull UIViewController *)parentViewController
                                           parentView:(nullable UIView *)parentView
                                acceptedDocumentTypes:(nonnull NSArray<SBSDKGenericDocumentRootType*> *)acceptedDocumentTypes
                                   excludedFieldTypes:(nullable NSArray<NSString *> *)excludedFieldTypes
                                             delegate:(id<SBSDKGenericDocumentRecognizerViewControllerDelegate>)delegate;

/**
 * Resets the recognized-documents-accumulator.
 */
- (void)resetDocumentAccumulation;

@end

NS_ASSUME_NONNULL_END
