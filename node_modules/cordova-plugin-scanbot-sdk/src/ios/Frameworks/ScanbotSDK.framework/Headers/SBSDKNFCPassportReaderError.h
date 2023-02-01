//
//  SBSDKNFCPassportReaderError.h
//  ScanbotSDK
//
//  Created by Yevgeniy Knizhnik on 31.07.20.
//  Copyright © 2020 doo GmbH. All rights reserved.
//

/** Types of passport reader errors. */
typedef NS_ENUM(NSUInteger, SBSDKNFCPassportReaderError) {
    /** Error occurred during authentication. */
    SBSDKNFCPassportReaderErrorAuthentication,
    
    /** Error occurred during data downloading. */
    SBSDKNFCPassportReaderErrorDownloading,
};

