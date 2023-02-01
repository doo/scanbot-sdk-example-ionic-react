//
//  SBSDKMachineReadableZoneRecognizerTextLine.h
//  ScanbotSDKBeta
//
//  Created by Andrew Petrus on 13.12.17.
//  Copyright © 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * A class encapsulating machine-readable-zones text line.
 */
@interface SBSDKMachineReadableZoneRecognizerTextLine : NSObject

/** The text recognized in the line. */
@property (nonatomic, strong) NSString *recognizedText;

/** The confidence value of the recognized text. */
@property (nonatomic) double confidenceValue;

@end
