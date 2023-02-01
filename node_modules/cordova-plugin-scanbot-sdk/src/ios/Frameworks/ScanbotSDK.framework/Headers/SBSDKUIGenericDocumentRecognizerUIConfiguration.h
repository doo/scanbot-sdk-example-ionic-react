//
//  SBSDKUIGenericDocumentRecognizerUIConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKGenericDocument.h"
#import "SBSDKOrientationLock.h"

NS_ASSUME_NONNULL_BEGIN

/** Configuration for the user interface of the generic document recognizer screens. */
@interface SBSDKUIGenericDocumentRecognizerUIConfiguration : NSObject

/** Foreground color of the top bar buttons on the scanning screen. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsColor;

/** Background color of the top bar. */
@property (nonnull, nonatomic, strong) UIColor *topBarBackgroundColor;

/** Foreground color of the flash button when flash is off. */
@property (nonnull, nonatomic, strong) UIColor *topBarButtonsInactiveColor;

/** Background color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *cameraOverlayColor;

/** Foreground color of the detection overlay. */
@property (nonnull, nonatomic, strong) UIColor *finderLineColor;

/** Width of finder frame border. Default is 2. */
@property (nonatomic) CGFloat finderLineWidth;

/** Whether the flash button is hidden or not. */
@property (nonatomic, assign, getter=isFlashButtonHidden) BOOL flashButtonHidden;

/** Whether the cancel button is hidden or not. */
@property (nonatomic, assign, getter=isCancelButtonHidden) BOOL cancelButtonHidden;

/** Allowed orientations for automatic interface rotations. **/
@property (nonatomic, assign) SBSDKOrientationLock orientationLockMode;

/** Text color of the fields count label. */
@property (nonnull, nonatomic, strong) UIColor *fieldsCountTextColor;

/** Text color in the details list. Also affects image background and separator. */
@property (nonnull, nonatomic, strong) UIColor *detailsPrimaryColor;

/** Foreground color of the top bar buttons on the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsActionColor;

/** Text color for section headers on the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsSectionHeaderTextColor;

/** Background color for section headers on the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsSectionHeaderBackgroundColor;

/** Background color of the details screen. */
@property (nonnull, nonatomic, strong) UIColor *detailsBackgroundColor;

/** Color of confidence value label background in details screen, when the field confidence level is high. */
@property (nonnull, nonatomic, strong) UIColor *fieldConfidenceHighColor;

/** Color of confidence value label background  in details screen, when the field confidence level is moderate. */
@property (nonnull, nonatomic, strong) UIColor *fieldConfidenceModerateColor;

/** Color of confidence value label background  in details screen, when the field confidence level is low. */
@property (nonnull, nonatomic, strong) UIColor *fieldConfidenceLowColor;

/** Color of confidence value label text in details. */
@property (nonnull, nonatomic, strong) UIColor *fieldConfidenceTextColor;

/** Color of tip text on scanning screen. */
@property (nonnull, nonatomic, strong) UIColor *tipTextColor;

/** Color of tip background on scanning screen. */
@property (nonnull, nonatomic, strong) UIColor *tipBackgroundColor;

/**
 * A mutable dictionary of user defined visibility states for generic document field types. Filled with default values.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the state of visibility for the corresponding fields.
 * Use this property to configure the filtering of document fields in the user interface.
 */
@property (nonnull, nonatomic, strong) NSMutableDictionary <NSString *, SBSDKGenericDocumentFieldDisplayState>* fieldTypeVisibilities;

@end

NS_ASSUME_NONNULL_END
