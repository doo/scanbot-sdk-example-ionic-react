#import <Foundation/Foundation.h>


@import ScanbotSDK;

@interface CDVScanbotSDKConfiguration : NSObject
@property(nonatomic) BOOL loggingEnabled;
@property(nonatomic) NSString* licenseKey;
@property(nonatomic) int storageImageQuality;
@property(nonatomic) SBSDKImageFileFormat storageImageFormat;
@property(nonatomic) NSString* storageBaseDirectory;

@property(nonatomic) NSString* fileEncryptionPassword;
@property(nonatomic) SBSDKAESEncrypterMode fileEncryptionMode;

- (instancetype)init;
@end
