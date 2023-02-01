//
//  SBSDKPolygon+JSON.m
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import "SBSDKPolygon+JSON.h"

@implementation SBSDKPolygon (JSON)

- (NSArray *)polygonPoints {
    NSMutableArray *points = [NSMutableArray array];
    for (NSInteger index = 0; index < 4; index++) {
        CGPoint point = [self normalizedPointWithIndex:index];
        [points addObject:@{@"x":@(point.x),
                            @"y":@(point.y)}];
    }
    return [NSArray arrayWithArray:points];
}

- (NSString *)detectionStatusString {
    return [self detectionStatusStringFromSBSDKStatus:self.detectionStatus];
}

- (NSString *)detectionStatusStringFromSBSDKStatus:(SBSDKDocumentDetectionStatus)status {
    switch (status) {
        case SBSDKDocumentDetectionStatusOK:
            return @"OK";
        case SBSDKDocumentDetectionStatusOK_SmallSize:
            return @"OK_BUT_TOO_SMALL";
        case SBSDKDocumentDetectionStatusOK_BadAngles:
            return @"OK_BUT_BAD_ANGLES";
        case SBSDKDocumentDetectionStatusOK_BadAspectRatio:
            return @"OK_BUT_BAD_ASPECT_RATIO";
        case SBSDKDocumentDetectionStatusError_NothingDetected:
            return @"ERROR_NOTHING_DETECTED";
        case SBSDKDocumentDetectionStatusError_Brightness:
            return @"ERROR_TOO_DARK";
        case SBSDKDocumentDetectionStatusError_Noise:
            return @"ERROR_TOO_NOISY";
        default:
            return @"";
    }
}

@end
