//
//  HandyJSONParameters.m
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import "HandyJSONParameters.h"

#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

#import "LoggingUtils.h"

@interface HandyJSONParameters ()

@property (nonatomic, strong) CDVInvokedUrlCommand *command;

@end

@implementation HandyJSONParameters

+ (instancetype)JSONParametersWithCordovaCommand:(CDVInvokedUrlCommand *)command {
    return [[HandyJSONParameters alloc] initWithCordovaCommand:command];
}

- (instancetype)initWithCordovaCommand:(CDVInvokedUrlCommand *)command {
    self = [super init];
    if (self) {
        self.command = command;
    }
    return self;
}

- (id)objectForKeyedSubscript:(id)key {
    if (self.command) {
        for (NSDictionary *dict in self.command.arguments) {
            if ([dict.allKeys containsObject:key]) {
                return dict[key];
            }
        }
    }
    return nil;
}

- (BOOL)validateArrayParameter:(NSString *)parameterName
              withErrorMessage:(NSString *)errorMessage {
    if (!self[parameterName] ||
        ![self[parameterName] isKindOfClass:[NSArray class]] ||
        [self[parameterName] count] == 0) {
        if (errorMessage) {
            SBSDKLog(errorMessage);
        }
        return NO;
    }
    return YES;
}

- (BOOL)validateParameter:(NSString *)parameterName {
    if (!self[parameterName]) {
        return NO;
    }
    return YES;
}

- (CGFloat)floatParameterValueForKey:(NSString *)key
                            minValue:(CGFloat)minValue
                            maxValue:(CGFloat)maxValue
                        defaultValue:(CGFloat)defaultValue {
    if (self[key]) {
        if ([self[key] isKindOfClass:[NSNumber class]] ||
            [self[key] isKindOfClass:[NSString class]]) {
            CGFloat value = [self[key] floatValue];
            if (value < minValue || value > maxValue) {
                return defaultValue;
            }
            return value;
        }
    }
    return defaultValue;
}

- (CGFloat)integerParameterValueForKey:(NSString *)key
                              minValue:(NSInteger)minValue
                              maxValue:(NSInteger)maxValue
                          defaultValue:(NSInteger)defaultValue {
    if (self[key]) {
        if ([self[key] isKindOfClass:[NSNumber class]] ||
            [self[key] isKindOfClass:[NSString class]]) {
            NSInteger value = [self[key] integerValue];
            if (value < minValue || value > maxValue) {
                return defaultValue;
            }
            return value;
        }
    }
    return defaultValue;
}

- (BOOL)boolParameterValueForKey:(NSString *)key
                    defaultValue:(BOOL)defaultValue {
    if (self[key]) {
        if ([self[key] isKindOfClass:[NSNumber class]]) {
            BOOL value = [self[key] boolValue];
            return value;
        }
        if ([self[key] isKindOfClass:[NSString class]]) {
            NSString *value = self[key];
            if ([[value uppercaseString] isEqualToString:@"TRUE"]) {
                return YES;
            }
            return NO;
        }
    }
    return defaultValue;
}

- (NSString *)stringParameterValueForKey:(NSString *)key
							defaultValue:(NSString *)defaultValue {
	if (self[key]) {
		if ([self[key] isKindOfClass:[NSString class]]) {
			return self[key];
		}
	}
	return defaultValue;
}

- (NSString *)stringParameterValueForKey:(NSString *)key {
	return [self stringParameterValueForKey:key defaultValue:@""];
}

- (BOOL)boolParameterValueForKey:(NSString *)key {
    return [self boolParameterValueForKey:key defaultValue:NO];
}

- (CGFloat)qualityValue {
    return [self floatParameterValueForKey:@"quality" minValue:1 maxValue:100 defaultValue:80] / 100.0;
}

- (NSInteger)sampleSizeValue {
    return [self integerParameterValueForKey:@"sampleSize" minValue:1 maxValue:100 defaultValue:1];
}

- (CGFloat)autoSnappingSensitivityValue {
    return [self floatParameterValueForKey:@"autoSnappingSensitivity" minValue:0.0f maxValue:1.0f defaultValue:0.66f];
}

- (NSString *)imageFileUriValue {
	return [self stringParameterValueForKey:@"imageFileUri"];
}

- (NSInteger)degreesValue {
	return [self integerParameterValueForKey:@"degrees" minValue:-360 maxValue:360 defaultValue:0];
}

@end
