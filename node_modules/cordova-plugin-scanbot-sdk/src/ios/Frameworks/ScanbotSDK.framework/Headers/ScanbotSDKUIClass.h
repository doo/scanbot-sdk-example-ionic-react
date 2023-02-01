//
//  ScanbotSDKUIClass.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 05.11.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKStorageCrypting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Helper class to configure properties of the ScanbotSDKUI (SBSDKUI) components.
 */
@interface ScanbotSDKUI : NSObject

/**
 * Sets the SBSDKUI-component-wide encrypter for storing image data to disk. Defaults to nil.
 * If set to nil no encryption is used at all.
 * You can use the built-in encrypter `SBSDKAESEncrypter` to encrypt your sensitive image data
 * using AES128 or AES256 before storing it to disk.
 *
 * When using encryption you still can access the unencrypted images in the image storage.
 * Of course, encrypted storages cannot be read without the proper encrypter being set here.
 * You are responsible for migrating image storages.
 *
 * Important: If you wish to use the SBSDKUI-wide encryption setup your encrypter before using any of the SBSDKUI-API.
 * A good place to configure it, is your AppDelegates entry point, right where the license is set.
 * Once SBSDKUI-API is used the storages are created and any change to the default encrypter is of no effect.
 *
 * For standard components, prefixed with SBSDK (without UI) the default encrypter has no effect, since there is
 * no image storage by default. You can, of course, create instances of `SBSDKKeyedImageStorage`
 * and `SBSDKIndexedImageStorage` and initialize them with an encrypter of your choice.
 */
+ (void)setDefaultImageStoreEncrypter:(nullable id<SBSDKStorageCrypting>)encrypter;

/**
 * The encrypter used in all SBSDKUI components for encrypting images before storing to disk.
 * Defaults to nil: no encryption is used.
 * @return The default image storage encrypter if set, nil otherwise.
 */
+ (nullable id<SBSDKStorageCrypting>)defaultImageStoreEncrypter;


/**
 * Sets the SBSDKUI-component-wide encrypter for storing PDF files to disk. Defaults to nil.
 * If set to nil no encryption is used at all.
 * You can use the built-in encrypter `SBSDKAESEncrypter` to encrypt your sensitive pdf files
 * using AES128 or AES256 before storing it to disk.
 *
 * Important: If you wish to use the SBSDKUI-wide encryption setup your encrypter before using any of the SBSDKUI-API.
 * A good place to configure it, is your AppDelegates entry point, right where the license is set.
 *
 * For standard components, prefixed with SBSDK (without UI) the default pdf encrypter has no effect.
 * Here you have to set it up for the PDF renderer individually.
 */
+ (void)setDefaultPDFEncrypter:(nullable id<SBSDKStorageCrypting>)encrypter;

/**
 * The encrypter used in all SBSDKUI components for encrypting generated PDF files before storing to disk.
 * Defaults to nil: no encryption is used.
 * @return The default pdf encrypter if set, nil otherwise.
 */
+ (nullable id<SBSDKStorageCrypting>)defaultPDFEncrypter;

/**
 * Scanning viewcontrollers in SBSDKUI components can show or hide the status bar.
 * This is the default value for all scanning viewcontrollers upon their initialization.
 * @return YES, if the status bar in scanning viewcontrollers is shown by default, NO otherwise.
 *
 * The default value is NO.
 */
+ (BOOL)shouldShowStatusBarOnScanningScreens;

/**
 * Scanning viewcontrollers in SBSDKUI components can show or hide the status bar.
 * This sets the default value for all scanning viewcontrollers upon their initialization.
 * @param shouldShow Set to YES, if the status bar in scanning viewcontrollers should be shown by default, NO otherwise.
 * The default value is NO.
 *
 * You still can individually set the status bar visibility for each instance of any scanning viewcontroller using
 * its shouldShowStatusBar property.
 */
+ (void)setShouldShowStatusBarOnScanningScreens:(BOOL)shouldShow;

/**
 * The default status bar style of all SBSDKUI components upon their initialization. Defaults to UIStatusBarStyleLightContent.
 * @return The default status bar style of all SBSDKUI components.
 */
+ (UIStatusBarStyle)defaultStatusBarStyle;

/**
 * Sets the default status bar style of all SBSDKUI components.
 * @param style The default status bar style of all SBSDKUI components.
 *
 * You still can individually set the status bar style for each instance of any SBSDKUI viewcontroller using
 * its statusBarStyle property.
 */
+ (void)setDefaultStatusBarStyle:(UIStatusBarStyle)style;


@end

NS_ASSUME_NONNULL_END
