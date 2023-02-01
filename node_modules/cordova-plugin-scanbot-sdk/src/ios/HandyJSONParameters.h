//
//  HandyJSONParameters.h
//  Scanbot SDK Cordova Plugin
//
//  Copyright (c) 2017 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class CDVInvokedUrlCommand;
@interface HandyJSONParameters : NSObject

+ (instancetype)JSONParametersWithCordovaCommand:(CDVInvokedUrlCommand *)command;

- (instancetype)initWithCordovaCommand:(CDVInvokedUrlCommand *)command;

- (id)objectForKeyedSubscript:(id)key;

- (BOOL)validateArrayParameter:(NSString *)parameterName
              withErrorMessage:(NSString *)errorMessage;

- (BOOL)validateParameter:(NSString *)parameterName;

- (CGFloat)floatParameterValueForKey:(NSString *)key
                            minValue:(CGFloat)minValue
                            maxValue:(CGFloat)maxValue
                        defaultValue:(CGFloat)defaultValue;

- (CGFloat)integerParameterValueForKey:(NSString *)key
                              minValue:(NSInteger)minValue
                              maxValue:(NSInteger)maxValue
                          defaultValue:(NSInteger)defaultValue;

- (BOOL)boolParameterValueForKey:(NSString *)key;

- (BOOL)boolParameterValueForKey:(NSString *)key
                    defaultValue:(BOOL)defaultValue;

- (NSString *)stringParameterValueForKey:(NSString *)key
							defaultValue:(NSString *)defaultValue;

- (NSString *)stringParameterValueForKey:(NSString *)key;

#pragma mark - Specific helpers

- (CGFloat)qualityValue;

- (NSInteger)sampleSizeValue;

- (CGFloat)autoSnappingSensitivityValue;

- (NSString *)imageFileUriValue;

- (NSInteger)degreesValue;

@end
