//
//  SBSDKShutterButton.h
//  SnapIos
//
//  Created by Sebastian Husche on 09.07.13.
//  Copyright (c) 2014 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKScanbotSDKConstants.h"

/**
 * @class SBSDKShutterButton
 * The button class used in the camera view controller to take a snapshot.
 * Animates itself depending on its status.
 */
@interface SBSDKShutterButton : UIButton

/** 
 * Indicates, whether a still image is currently being taken or not.
 * If YES a UIActivityIndicator is shown in the center.
 */
@property(nonatomic, assign) BOOL takingPhoto;

/**
 * The current status of the receiver. See SBSDKScannerStatus.
 */
@property(nonatomic, assign) SBSDKScannerStatus scannerStatus;

/**
 * The main color of shutter button while scannerStatus is `SBSDKScannerStatusScanning`. Can be nil. Default is white.
 */
@property(nonatomic, strong) UIColor *buttonSearchingColor UI_APPEARANCE_SELECTOR;

/**
 * The main color of shutter button while scannerStatus is `SBSDKScannerStatusDetected`. Can be nil. Default is white.
 */
@property(nonatomic, strong) UIColor *buttonDetectedColor UI_APPEARANCE_SELECTOR;

/**
 * The background color of shutter button while scannerStatus is `SBSDKScannerStatusScanning`.
 * Can be nil. Default is clear color.
 */
@property(nonatomic, strong) UIColor *buttonSearchingBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * The background color of shutter button while scannerStatus is `SBSDKScannerStatusDetected`.
 * Can be nil. Default is clear color.
 */
@property(nonatomic, strong) UIColor *buttonDetectedBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * The color of indicator shown, when `takingPhoto` is set to YES.
 */
@property(nonatomic, strong) UIColor *indicatorColor UI_APPEARANCE_SELECTOR;

@end

