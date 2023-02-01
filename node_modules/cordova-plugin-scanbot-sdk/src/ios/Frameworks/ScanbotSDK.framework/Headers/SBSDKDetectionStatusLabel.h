//
//  SBSDKDetectionStatusLabel.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 09.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * A UILabel subclass with rounded corners and content insets to display the status of the current document
 * detection result.
 */
@interface SBSDKDetectionStatusLabel : UILabel

/** The text insets for the receiver. Defaults to 6, 12, 6, 12). */
@property (nonatomic, assign) UIEdgeInsets textInsets;

@end
