//
//  SBSDKLicenseStatus.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 27.09.19.
//  Copyright © 2019 doo GmbH. All rights reserved.
//

#ifndef SBSDK_LICENSE_STATUS_H
#define SBSDK_LICENSE_STATUS_H

/**
 * The status of the license.
 */
typedef enum : int32_t {

    /** License is valid and accepted. */
    LicenseStatusOkay = 0,

    /** No license set yet. The SDK is in trial mode. */
    LicenseStatusTrial = 1,

    /** No license set yet. The SDKs trial mode is over. */
    LicenseStatusFailureNotSet = 10,

    /** No license active. The set license was unreadable or has an invalid format. */
    LicenseStatusFailureCorrupted = 11,

    /** No license active. The set license does not cover the current operating system. */
    LicenseStatusFailureWrongOS = 12,

    /** No license active. The set licenses does not cover the current apps bundle identifier. */
    LicenseStatusFailureAppIDMismatch = 13,

    /** No license active.  The set license is valid but it has expired. */
    LicenseStatusFailureExpired = 14

} dooLicenseStatus;
#endif
