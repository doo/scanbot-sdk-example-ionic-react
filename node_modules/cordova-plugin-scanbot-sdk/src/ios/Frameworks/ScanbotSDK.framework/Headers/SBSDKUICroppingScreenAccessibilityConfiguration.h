//
//  SBSDKUICroppingScreenAccessibilityConfiguration.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 17.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Configuration for the accessibility labels and hints. */
@interface SBSDKUICroppingScreenAccessibilityConfiguration : NSObject

/** Text, that is used as an accessibility label for the cancel button. The default value is "Cancel". */
@property (nullable, nonatomic, strong) NSString *cancelButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the cancel button. The default value is "Discards changes and dismisses the screen". */
@property (nullable, nonatomic, strong) NSString *cancelButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the done button. The default value is "Done". */
@property (nullable, nonatomic, strong) NSString *doneButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the done button. The default value is "Saves and dismisses the screen". */
@property (nullable, nonatomic, strong) NSString *doneButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the detect button. The default value is "Detect". */
@property (nullable, nonatomic, strong) NSString *detectButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the detect button. The default value is "Detects document's edges". */
@property (nullable, nonatomic, strong) NSString *detectButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the reset button. The default value is "Reset". */
@property (nullable, nonatomic, strong) NSString *resetButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the reset button. The default value is "Resets document's edges". */
@property (nullable, nonatomic, strong) NSString *resetButtonAccessibilityHint;

/** Text, that is used as an accessibility label for the rotate button. The default value is "Rotate". */
@property (nullable, nonatomic, strong) NSString *rotateButtonAccessibilityLabel;

/** Text, that is used as an accessibility hint for the rotate button. The default value is "Rotate image". */
@property (nullable, nonatomic, strong) NSString *rotateButtonAccessibilityHint;
@end
