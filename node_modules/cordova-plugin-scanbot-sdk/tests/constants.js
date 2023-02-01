const validLicense = "<VALID_LICENSE>";
const trialLicense = '';
const expiredLicense = "<EXPIRED_LICENSE>";
const iosLicense = "<IOS_LICENSE>";
const androidLicense = "<ANDROID_LICENSE>"
const appIdMismatchLicense = "<APP_ID_MISMATCH_LICENSE>";
const corruptedLicense = 'foo bar';
const trialPeriod = Date.now() + 60000;
const github_token = '<GITHUB_TOKEN>';
const assets_url = 'https://raw.githubusercontent.com/doo/scanbot-test-assets/master/images/docdetector';

const config = {
    license: {
        okay: {
            message: "Scanbot SDK initialized.", 
            isLicenseValid: true,
            licenseStatus: "Okay",
            licenseExpirationDate: 1654127999000
        },
        trial: { 
            message: "Scanbot SDK initialized. Trial mode activated. You can now test all features for 60 seconds.", 
            isLicenseValid: true,
            licenseStatus: "Trial",
            licenseExpirationDate: trialPeriod
        },
        expired: {
            isLicenseValid: false,
            licenseStatus: "Expired",
            licenseExpirationDate: trialPeriod
        },
        correctOs: {
            isLicenseValid: true,
            licenseStatus: "Okay",
            licenseExpirationDate: Date.now()
        },
        wrongOs: {
            isLicenseValid: false,
            licenseStatus: "WrongOS",
            licenseExpirationDate: Date.now()
        },
        corrupted: {
            isLicenseValid: false,
            licenseStatus: "Corrupted",
            licenseExpirationDate: Date.now()
        },
        appIdMismatch: {
            isLicenseValid: false,
            licenseStatus: "AppIDMismatch",
            licenseExpirationDate: Date.now()
        },
        notSet: {
            isLicenseValid: false,
            licenseStatus: "NotSet",
            licenseExpirationDate: trialPeriod
        },
        // unknown: {
        //     isLicenseValid: false,
        //     licenseStatus: "Unknown",
        //     licenseExpirationDate: 0
        // }
    }
}

const images = {
    image: {
        aspect_ratio: {
            img: `${assets_url}/aspect_ratio.jpg`,
            result: "OK_BUT_BAD_ASPECT_RATIO"
        },
        bad_angles: {
            img: `${assets_url}/bad_angles.jpg`,
            result: "OK_BUT_BAD_ANGLES",
            polygon: [
                {
                    x: 0.22345594,
                    y: 0.039661016
                },
                {
                    x: 0.8102012,
                    y: 0.049830507
                },
                {
                    x: 0.9944483,
                    y: 0.96474576
                },
                {
                    x: 0.011797363,
                    y: 0.9481356
                }
            ],
            polygon_ml: [
                {
                    x: 0.22102706,
                    y: 0.041694917
                },
                {
                    x: 0.8140181,
                    y: 0.043050848
                },
                {
                    x: 0.98820263,
                    y: 0.96949154
                },
                {
                    x: 0.017349062,
                    y: 0.94881356
                }
            ], 
        },
        // dark: {
        //     img: `${assets_url}/dark.jpg`,
        //     result: "ERROR_TOO_DARK"
        // },
        // dark_ml: {
        //     img: `${assets_url}/dark_ml.jpg`,
        //     result: "ERROR_TOO_DARK"
        // },
        ok: {
            img: `${assets_url}/ok.jpg`,
            result: "OK",
            polygon: [
                {
                    x: 0.094, 
                    y: 0.04996481
                },
                {
                    x: 0.952,
                    y: 0.039408866
                },
                {
                    x: 0.963,
                    y: 0.96481353
                },
                {
                    x: 0.075,
                    y: 0.9444054
                }
            ]
        },
        ok_ml: {
            img: `${assets_url}/ok_ml.jpg`,
            result: "OK",
            polygon_ml: [
                {
                    x: 0.09398186,
                    y: 0.04874835
                },
                {
                    x: 0.84831,
                    y: 0.026350461
                },
                {
                    x: 0.92168176,
                    y: 0.9216074
                },
                {
                    x: 0.08408903,
                    y: 0.93379444
                }
            ]
        },
        small: {
            img: `${assets_url}/small.jpg`,
            result: "OK_BUT_TOO_SMALL"
        }
    }
}

module.exports = {
    validLicense,
    trialLicense,
    expiredLicense,
    iosLicense,
    androidLicense,
    appIdMismatchLicense,
    corruptedLicense,
    github_token,
    assets_url,
    config,
    images
}