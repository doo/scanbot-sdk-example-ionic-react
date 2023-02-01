//
//  SBSDKOCRResult+JSON.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import <ScanbotSDK/ScanbotSDK.h>

@interface SBSDKOCRResult (JSON)

- (NSDictionary *)dictionaryRepresentation;

@end

@interface SBSDKOCRPage (JSON)

- (NSDictionary *)dictionaryRepresentation;

@end

@interface SBSDKOCRResultBlock (JSON)

- (NSDictionary *)dictionaryRepresentation;

@end
