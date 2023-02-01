//
//  SBSDKUIDocumentScannerAccessibilityConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 16.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Configuration for the accessibility labels and hints. */
@interface SBSDKUIDocumentScannerAccessibilityConfiguration : NSObject

/** Text, that is used as an accessibility label for the flash button. The default value is "Flash". */
@property (nullable, nonatomic, strong) NSString *flashButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the flash button. The default value is "Turns the flashlight on or off". */
@property (nullable, nonatomic, strong) NSString *flashButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the multi-page button. The default value is "Multi page scanning". */
@property (nullable, nonatomic, strong) NSString *multiPageButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the multi-page button. The default value is "Turns multi page scanning on or off". */
@property (nullable, nonatomic, strong) NSString *multiPageButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the auto-snapping button. The default value is "Auto scan". */
@property (nullable, nonatomic, strong) NSString *autoSnappingButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the auto-snapping button. The default value is "Turns auto scanning on or off". */
@property (nullable, nonatomic, strong) NSString *autoSnappingButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the cancel button. The default value is "Cancel". */
@property (nullable, nonatomic, strong) NSString *cancelButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the cancel button. The default value is "Dismisses the screen". */
@property (nullable, nonatomic, strong) NSString *cancelButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the page-amount button. The default value is "%d photos", to voice the amount of scans taken. */
@property (nullable, nonatomic, strong) NSString *pageCounterButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the page-amount button. The default value is "Dismisses the screen and shows the result". */
@property (nullable, nonatomic, strong) NSString *pageCounterButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the shutter button. The default value is "Shutter release". */
@property (nullable, nonatomic, strong) NSString *shutterButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the shutter button. The default value is "Makes a scan". */
@property (nullable, nonatomic, strong) NSString *shutterButtonAccessibilityHint;

@end
