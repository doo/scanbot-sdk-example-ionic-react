//
//  ObjectMapper.m
//  Scanbot SDK Cordova Plugin
//
//  Created by Stefan Dragnev on 01.06.18.
//  Copyright © 2018 doo. All rights reserved.
//
#import "ObjectMapper.h"
#import <objc/runtime.h>
#import "UIColor+JSON.h"
#import "JSONMappings.h"

static NSDictionary<NSString*, NSDictionary<NSString*, NSNumber*>*>* _enumerationMapping;

@implementation ObjectMapper

+ (id)nativeValueFor:(id)value propertyType:(NSString *)propertyType {
    if ([propertyType isEqualToString:@"{CGSize=dd}"]) {
        NSDictionary *sizeDict = (NSDictionary *)value;
        return @(CGSizeFromJson(sizeDict));
    }
    
    if ([propertyType isEqualToString:@"@\"UIColor\""]) {
        return [UIColor colorFromHexString:value];
    }

    if ([propertyType isEqualToString:@"@\"SBSDKAspectRatio\""]) {
        double width = [[value objectForKey:@"width"] doubleValue];
        double height = [[value objectForKey:@"height"] doubleValue];
        return [[SBSDKAspectRatio alloc] initWithWidth:width andHeight:height];
    }
    return nil;
}

+ (void)setEnumerationMapping:(NSDictionary<NSString*, NSDictionary<NSString*, NSNumber*>*>*)enumerationMapping {
    _enumerationMapping = enumerationMapping;
}

+ (void)populateInstance:(id)instance fromDictionary:(NSDictionary *)dictionary class:(Class)cls {
    uint outCount;
    objc_property_t* properties = class_copyPropertyList(cls, &outCount);
    
    for (uint pi = 0; pi < outCount; ++pi) {
        const char *name = property_getName(properties[pi]);
        NSString* key = [NSString stringWithUTF8String:name];
        
        objc_property_attribute_t *propertyType = property_copyAttributeList(properties[pi], NULL);
        NSString *propertyTypeString = [NSString stringWithUTF8String:propertyType->value];
        free(propertyType);
        
        id value = [dictionary objectForKey:key];
        
        // normalize OK and Ok
        if (!value && [key hasSuffix:@"Ok"]) {
            NSString* okKey = [key stringByReplacingOccurrencesOfString:@"Ok" withString:@"OK"];
            value = [dictionary objectForKey:okKey];
        }
        
        if (value) {
            NSDictionary<NSString*, NSNumber*>* valuesDict = [_enumerationMapping objectForKey:key];
            if (valuesDict) {
                value = [valuesDict objectForKey:value];
                if (!value) {
                    @throw [NSException exceptionWithName:@"ArgumentException" reason:[NSString stringWithFormat:@"Invalid enumeration value for parameter %@", key] userInfo:nil];
                }
            } else {
                id native = [self nativeValueFor:value propertyType:propertyTypeString];
                if (native) {
                    value = native;
                }
            }
            
            [instance setValue:value forKey:key];
        }
    }
    
    free(properties);
}

+ (void)populateInstance:(id)instance
          fromDictionary:(NSDictionary*)dictionary {
    Class cls = [instance class];
    
    while (cls != nil && cls != NSObject.class) {
        [ObjectMapper populateInstance:instance fromDictionary:dictionary class:cls];
        cls = [cls superclass];
    }
}

+ (SBSDKDocumentDetectorMode)documentDetectorMode:(NSDictionary*)configuration {
    NSString* mode = [configuration objectForKey:@"documentDetectorMode"];
    if ([mode isEqualToString:@"ML_BASED"]) {
        return SBSDKDocumentDetectorModeMachineLearning;
    }
    return SBSDKDocumentDetectorModeStandard;
}

+ (SBSDKOrientationLock)extractOrientationLockMode:(NSDictionary*)configuration {
    SBSDKOrientationLock orientationLock = SBSDKOrientationLockNone;
    NSString* orientation = [configuration objectForKey:@"interfaceOrientation"];
    if (orientation) {
        if ([orientation isEqualToString:@"ALL"])  orientationLock = SBSDKOrientationLockNone;
        if ([orientation isEqualToString:@"PORTRAIT"])  orientationLock =  SBSDKOrientationLockPortrait;
        if ([orientation isEqualToString:@"LANDSCAPE"]) orientationLock = SBSDKOrientationLockLandscape;
    }
    return orientationLock;
}

+ (NSString *)normalizeJsonString:(NSString *)strValue {
    if (strValue == nil || strValue == (id)[NSNull null]) {
        return nil;
    }
    if ([strValue isEqualToString:@""] || [strValue isEqualToString:@"null"]) {
        return nil;
    }
    return strValue;
}

+ (NSURL *)normalizeJsonFileURL:(NSString *)fileUrl {
    NSString* strValue = [ObjectMapper normalizeJsonString:fileUrl];
    if (!strValue) {
        return nil;
    }
    
    // check if we have a valid file URL
    NSURL* url = [NSURL URLWithString:strValue];
    if (url.isFileURL) {
        return url;
    }
    
    // otherwise convert the path to a file URL ("/some/path" to "file:///some/path")
    return [NSURL fileURLWithPath:strValue];
}

+ (NSString *)normalizeJsonFileURLAsString:(NSString *)fileUrl {
    NSURL* url = [ObjectMapper normalizeJsonFileURL:fileUrl];
    if (!url) {
        return nil;
    }
    return url.absoluteString;
}

@end
