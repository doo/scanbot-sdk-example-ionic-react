//
//  SBSDKUIGenericDocumentRecognizerTextConfiguration.h
//  ScanbotSDKBeta
//
//  Created by Yevgeniy Knizhnik on 04.06.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKUIEnableCameraTextConfiguration.h"
#import "SBSDKGenericDocument.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration for the textual contents of the generic document recognizer screen.
 */
@interface SBSDKUIGenericDocumentRecognizerTextConfiguration : SBSDKUIEnableCameraTextConfiguration

/** String being displayed on the flash button. */
@property (nullable, nonatomic, strong) NSString *flashButtonTitle;

/** String being displayed on the cancel button. */
@property (nullable, nonatomic, strong) NSString *cancelButtonTitle;

/** String being displayed on the clear button. */
@property (nullable, nonatomic, strong) NSString *clearButtonTitle;

/** String being displayed on the view results button.  */
@property (nullable, nonatomic, strong) NSString *viewResultsButtonTitle;

/** String used for displaying amount of detected fields. Use %li for number formatting symbol. */
@property (nullable, nonatomic, strong) NSString *fieldsCountText;

/** String that shows average confidence value of scanned card. Use %li as number formatting symbol. */
@property (nullable, nonatomic, strong) NSString *confidenceValue;

/** String that asks user to scan back side of a card. */
@property (nullable, nonatomic, strong) NSString *scanBackSideTitle;

/** String that asks user to scan front side of a card. */
@property (nullable, nonatomic, strong) NSString *scanFrontSideTitle;

/** String that asks user to start scanning a card. */
@property (nullable, nonatomic, strong) NSString *startScanningTitle;

/** String that notifies that nothing was scanned yet. */
@property (nullable, nonatomic, strong) NSString *noDataTitle;

/** String that notifies that both sides of card are scanned. */
@property (nullable, nonatomic, strong) NSString *scannedEverythingTitle;

/** String being displayed for empty values. */
@property (nullable, nonatomic, strong) NSString *emptyValueTitle;

/**
 * A mutable dictionary of user defined display strings for generic document types. Filled with default values.
 * Each key is equal to a document types `normalizedName` property.
 * The values contain the user defined display texts for the corresponding document types.
 */
@property (nonnull, nonatomic, strong) NSMutableDictionary <NSString *, NSString *> *documentTypeDisplayTexts;

/**
 * A mutable dictionary of user defined display strings for generic document field types. Filled with default values.
 * Each key is equal to a fields `normalizedName` property.
 * The values contain the user defined display texts for the corresponding fields.
 */
@property (nonnull, nonatomic, strong) NSMutableDictionary <NSString *, NSString *>* fieldTypeDisplayTexts;

@end

NS_ASSUME_NONNULL_END
