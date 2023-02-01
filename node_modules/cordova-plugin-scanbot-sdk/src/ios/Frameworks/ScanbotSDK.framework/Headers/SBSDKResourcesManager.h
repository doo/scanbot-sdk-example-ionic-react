//
//  SBSDKResourcesManager.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 07.03.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * An enumeration that represents resource type.
 */
typedef NS_ENUM(NSUInteger, SBSDKResourceType) {
    /** The resource type for optical text recognition training data. */
    SBSDKResourceTypeOCR,
    
    /** The resource type for machine readable zone recognition training data. */
    SBSDKResourceTypeMRZ,
    
    /** The resource type for payform recognition training data. */
    SBSDKResourceTypePayform,

    /** The resource type for invoice recognition training data. Not used yet*/
    SBSDKResourceTypeInvoice,
};

/**
 * A class that manages installation and removal of resources, required by some features. It also manages installation
 * of custom resources that extend some features functionality.
 */
@interface SBSDKResourcesManager : NSObject

/**
 * Installs required resource from the application's bundle. If the resource is missing, this method will terminate the
 * app with a descriptive message. This method will be called by a feature that depend on a given resource automatically,
 * thus no need to call it explicitly.
 * @param type The type of required resource to be installed.
 * @param force A boolean flag that forces to override the previously installed resources.
 * @return A boolean value, the success of the operation.
 */
+ (BOOL)installRequiredResourcesOfTypeIfNeeded:(SBSDKResourceType)type forceInstall:(BOOL)force;

/**
 * Removes resources of a given type. For type OCR it will also uninstall custom OCR languages.
 * @param type The type of required resource to be removed.
 */
+ (void)resetResourceOfType:(SBSDKResourceType)type;

/**
 * Checks whether `ScanbotSDKOCRData.bundle` is available in the application's bundle. If yes,
 * calling `installRequiredResourcesOfTypeIfNeeded:forceInstall:` will copy default OCR resources provided in it,
 * as well as required ones.
 * @return A boolean value that indicates the possibility of installing default OCR resources.
 */
+ (BOOL)canInstallDefaultOCRResources;

/**
 * Provides an URL of the folder, where custom OCR languages data can be copied.
 * @return An URL of the folder, where custom OCR languages data can be copied to.
 */
+ (nullable NSURL *)customOCRLanguagesDataURL;

/**
 * Returns a list of all installed two-letter ISO 639-1 language codes.
 * @return NSArray of NSString objects, each being a two-letter ISO 639-1 language code.
 */
+ (nonnull NSArray<NSString *> *)installedLanguages;

@end
