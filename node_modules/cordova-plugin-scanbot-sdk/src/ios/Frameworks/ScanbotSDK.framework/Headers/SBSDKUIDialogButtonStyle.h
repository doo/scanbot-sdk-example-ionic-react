//
//  SBSDKUIDialogButtonStyle.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 10.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** The general style for an action button in a ScanbotSDK alert. Used to customize certain result alerts in SBSDKUI components. */
@interface SBSDKUIDialogButtonStyle : NSObject

/** The font of the button title. Defaults to System font Regular 17.0. */
@property (nonatomic, strong) UIFont *font;

/** The color of the buttons title while not pressed. Defaults to blue. */
@property (nonatomic, strong) UIColor *textColor;

/** The color of the buttons title while pressed. Defaults to blue. */
@property (nonatomic, strong) UIColor *highlightedTextColor;

/** The background color of the button while not pressed. Defaults to clear color, fully transparent. */
@property (nonatomic, strong) UIColor *backgroundColor;

/** The background color of the button while pressed. Defaults to a light grey color. */
@property (nonatomic, strong) UIColor *highlightedBackgroundColor;

/** The default action button style. Use for confirmative actions. */
+ (instancetype)defaultStyle;

/** The cancel action button style. Use for cancel actions. */
+ (instancetype)cancelStyle;

/** The destructive action button style. Use for actions that are not reversible, e.g. deletions. */
+ (instancetype)destructiveStyle;

@end

NS_ASSUME_NONNULL_END
