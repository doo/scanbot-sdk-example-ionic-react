//
//  SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration.h
//  ScanbotSDK
//
//  Created by Danil Voitenko on 06.08.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SBSDKHealthInsuranceCardRecognizer.h"

/** Configuration for the behavior of Health Insurance Card scanner.*/
@interface SBSDKUIHealthInsuranceCardScannerBehaviorConfiguration : NSObject

/** Whether flash is toggled on or off. */
@property (nonatomic, assign, getter=isFlashEnabled) BOOL flashEnabled;

@end
