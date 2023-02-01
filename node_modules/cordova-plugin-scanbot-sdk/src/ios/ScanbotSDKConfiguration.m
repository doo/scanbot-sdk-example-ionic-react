#import "ScanbotSDKConfiguration.h"

@implementation ScanbotSDKConfiguration
- (instancetype)init {
    self = [super init];
    self.storageImageFormat = SBSDKImageFileFormatJPEG;
    self.storageImageQuality = 80;
    self.storageBaseDirectory = nil;
    self.fileEncryptionPassword = nil;
    self.fileEncryptionMode = SBSDKAESEncrypterModeAES256;
    return self;
}
@end
