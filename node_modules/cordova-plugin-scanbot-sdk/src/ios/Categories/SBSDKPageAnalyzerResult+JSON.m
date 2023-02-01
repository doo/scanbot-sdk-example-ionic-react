//
//  SBSDKPageAnalyzerResult+JSON.m
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import "SBSDKPageAnalyzerResult+JSON.h"

@implementation SBSDKPageAnalyzerResult (JSON)

- (NSString *)orientationString {
    switch (self.orientation) {
        case SBSDKPageOrientationUp:
            return @"UP";
        case SBSDKPageOrientationDown:
            return @"DOWN";
        case SBSDKPageOrientationLeft:
            return @"LEFT";
        case SBSDKPageOrientationRight:
            return @"RIGHT";
    }
    return @"";
}

- (NSString *)writingDirectionString {
    switch (self.writingDirection) {
        case SBSDKWritingDirectionLeftToRight:
            return @"LEFT_TO_RIGHT";
        case SBSDKWritingDirectionRightToLeft:
            return @"RIGHT_TO_LEFT";
        case SBSDKWritingDirectionTopToBottom:
            return @"TOP_TO_BOTTOM";
    }
    return @"";
}

- (NSString *)textLineOrderString {
    switch (self.textlineOrder) {
        case SBSDKTextlineOrderLeftToRight:
            return @"LEFT_TO_RIGHT";
        case SBSDKTextlineOrderRightToLeft:
            return @"RIGHT_TO_LEFT";
        case SBSDKTextlineOrderTopToBottom:
            return @"TOP_TO_BOTTOM";
    }
    return @"";
}

- (NSDictionary *)dictionaryRepresentation {
    return @{@"orientation":self.orientationString,
             @"writingDirection":self.writingDirectionString,
             @"textlineOrder":self.textLineOrderString,
             @"deskewAngle":@(self.deskewAngle)
             };
}

@end
