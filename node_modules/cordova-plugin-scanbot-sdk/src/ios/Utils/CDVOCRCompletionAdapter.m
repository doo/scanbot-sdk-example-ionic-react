//
//  CDVOCRCompletionAdapter.m
//  ScanbotSDKCordova
//
//  Created by Dmytro Makarenko on 3/20/19.
//  Copyright © 2019 doo. All rights reserved.
//

#import "CDVOCRCompletionAdapter.h"

#import "ScanbotStorageUtils.h"
#import "SBSDKOCRResult+JSON.h"

@implementation CDVOCRCompletionAdapter

- (instancetype)initWithOutputFormat:(NSString *)outputFormat {
    if (self = [super init]) {
        
        if ([outputFormat isEqualToString:@"PDF_FILE"] || [outputFormat isEqualToString:@"FULL_OCR_RESULT"]) {
            self->_outputPDFURL = [NSURL fileURLWithPath:[ScanbotStorageUtils generatePluginStorageFilePath:@"pdf"]];
        }
        
        self->_outputFormat = outputFormat;
        return self;
    }
    
    return nil;
}

+ (instancetype)adapterWithOutputFormat:(NSString *)outputFormat {
    return [[self alloc] initWithOutputFormat:outputFormat];
}

- (SBSDKCompletionHandler)adaptBlock:(CDVOCRCompletionHandler)completion {
    return ^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
        
        if (!finished || error) {
            completion(nil, error);
            return;
        }
        
        SBSDKOCRResult *result = resultInfo[SBSDKResultInfoOCRResultsKey];
        NSError *resultError;
        NSDictionary *resultDict = [self resultDictWith:result error:&resultError];
        
        if (resultError) {
            completion(nil, resultError);
            return;
        }
        
        completion(resultDict, nil);
    };
}

- (nullable NSDictionary *)resultDictWith:(SBSDKOCRResult *)result error:(NSError **)error {
    
    if ([self.outputFormat isEqualToString:@"PLAIN_TEXT"]) {
        return @{@"plainText": result.recognizedText};
    }
    
    if ([self.outputFormat isEqualToString:@"PDF_FILE"]) {
        return @{@"pdfFileUri": self.outputPDFURL.absoluteString};
    }
    
    if (*error) {
        return nil;
    }
    
    if ([self.outputFormat isEqualToString:@"RESULT_JSON"]) {
        return @{@"jsonData": [result dictionaryRepresentation]};
    }
    
    if ([self.outputFormat isEqualToString:@"FULL_OCR_RESULT"]) {
        return @{@"jsonData": [result dictionaryRepresentation],
                 @"pdfFileUri": self.outputPDFURL.absoluteString};
    }
    
    return nil;
}

- (NSURL *)saveResult:(SBSDKOCRResult *)result error:(NSError **)error {
    NSString *jsonFilePath = [ScanbotStorageUtils generatePluginStorageFilePath:@"json"];
    NSDictionary *json = [result dictionaryRepresentation];
    
    NSData *data = [NSJSONSerialization dataWithJSONObject:json options:kNilOptions error:error];
    [data writeToFile:jsonFilePath atomically:NO];
    
    return [NSURL fileURLWithPath:jsonFilePath];
}

@end
