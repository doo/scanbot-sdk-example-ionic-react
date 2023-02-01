//
//  CDVOCRCompletionAdapter.h
//  ScanbotSDKCordova
//
//  Created by Dmytro Makarenko on 3/20/19.
//  Copyright © 2019 doo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ScanbotSDK/SBSDKScanbotSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface CDVOCRCompletionAdapter : NSObject

typedef void (^CDVOCRCompletionHandler)(NSDictionary *_Nullable resultDict, NSError *_Nullable error);

@property(readonly, nonatomic) NSURL *outputPDFURL;
@property(readonly, nonatomic) NSString *outputFormat;

+ (instancetype)adapterWithOutputFormat:(NSString *)outputFormat;

- (SBSDKCompletionHandler)adaptBlock:(CDVOCRCompletionHandler)completion;

@end

NS_ASSUME_NONNULL_END
