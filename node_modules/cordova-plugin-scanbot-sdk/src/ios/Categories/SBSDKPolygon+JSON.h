//
//  SBSDKPolygon+JSON.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import <ScanbotSDK/ScanbotSDK.h>

@interface SBSDKPolygon (JSON)

- (NSArray *)polygonPoints;
- (NSString *)detectionStatusString;
- (NSString *)detectionStatusStringFromSBSDKStatus:(SBSDKDocumentDetectionStatus)status;

@end
