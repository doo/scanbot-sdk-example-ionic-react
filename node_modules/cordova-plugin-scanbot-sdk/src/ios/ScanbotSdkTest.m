#import "ScanbotSdkTest.h"

#import <Foundation/Foundation.h>

#ifdef _CORDOVA_TEST_TARGET
#import "CDVPlugin.h"
#import "CDVInvokedUrlCommand.h"
#else
#import <Cordova/CDVPlugin.h>
#endif

@implementation ScanbotSdkTest

- (void)saveFile:(CDVInvokedUrlCommand*)command {
    @try {
        NSString *url = [command.arguments[0] objectForKey:@"url"];
        NSString *token = [command.arguments[0] objectForKey:@"token"];
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *fileDirectory = [paths objectAtIndex:0];
        fileDirectory = [@"file:///" stringByAppendingString:fileDirectory];
        NSString *fileName = [url lastPathComponent];
        NSString *localFilePath = [fileDirectory stringByAppendingPathComponent:fileName];
        
        if ([[NSFileManager defaultManager] fileExistsAtPath:localFilePath]) {
            NSLog(@"File already exists...");
        }
        else {
            NSURL *requestUrl = [NSURL URLWithString:url];
            NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:requestUrl];
            [request setValue:[NSString stringWithFormat:@"token %@", token] forHTTPHeaderField:@"Authorization"];
            
            NSURLSession *session = [NSURLSession sharedSession];
            dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
            NSURLSessionDownloadTask *task = [session downloadTaskWithRequest:request completionHandler:^(NSURL * _Nullable location, NSURLResponse * _Nullable response, NSError * _Nullable error) {
                    [[NSFileManager defaultManager] moveItemAtURL:location toURL:[NSURL URLWithString:localFilePath] error:nil];
                    dispatch_semaphore_signal(semaphore);
                }
            ];
            
            while (dispatch_semaphore_wait(semaphore, DISPATCH_TIME_NOW)){
                [task resume];
                [[NSData dataWithContentsOfURL:requestUrl] writeToFile:localFilePath atomically:YES];
            }
            
            NSDictionary *result = @{@"path": localFilePath};
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:result];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            
        }
    }

    @catch (NSException *exception) {
        NSLog(@"Exception caught with reason >%@", exception);
        nil;
    }
}

@end
