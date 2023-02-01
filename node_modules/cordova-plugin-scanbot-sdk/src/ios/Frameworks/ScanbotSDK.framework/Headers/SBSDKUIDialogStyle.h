//
//  SBSDKUIDialogStyle.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 10.03.21.
//  Copyright © 2021 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** The general style for a dialog in ScanbotSDK. Used to customize certain result dialogs in SBSDKUI components. */
@interface SBSDKUIDialogStyle : NSObject

/** The color of the screen-covering backdrop view. Defaults to a very transparent  black. */
@property(nonatomic, strong) UIColor *screenBackgroundColor;

/** The general background color of the actual dialog view. Defaults to a very light grey with subtle transparency. */
@property(nonatomic, strong) UIColor *dialogBackgroundColor;

/** The visual effect of the dialogs background. Defaults to a system like blur with regular vibrance. */
@property(nonatomic, strong) UIVisualEffect *dialogBackgroundEffect;

/** The corner radius of the dialog. Defaults to 13 points. */
@property(nonatomic, assign) CGFloat cornerRadius;

/** The color of the dialogs title. Defaults to black. */
@property(nonatomic, strong) UIColor *titleColor;

/** The font of the dialogs title. Defaults to System font Bold 17.0. */
@property(nonatomic, strong) UIFont *titleFont;

/** The color of the dialogs message. Defaults to black. */
@property(nonatomic, strong) UIColor *messageColor;

/** The font of the dialogs message. Defaults to System font Regular 13.0. */
@property(nonatomic, strong) UIFont *messageFont;

/** The color of the separators around the dialogs button area. Defaults to a light grey with a small amount of transparency. */
@property(nonatomic, strong) UIColor *separatorColor;

/** The width of the separators in points. Defaults to 0.5 points. */
@property(nonatomic, assign) CGFloat separatorWidth;

/** The default style that mimics an iOS UIdialogController. */
+ (instancetype)defaultStyle;

@end

NS_ASSUME_NONNULL_END
