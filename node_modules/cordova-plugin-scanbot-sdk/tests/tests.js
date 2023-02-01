const constants = require('./constants')
const helpers = require('./helpers')

exports.defineAutoTests = function () {
    beforeAll(function() {
        jasmine.DEFAULT_TIMEOUT_INTERVAL = 65000;
    });

    describe('Initialize SDK Scenarios', function () { 
        it ('SDK Initialized with Trial License, verify license info is Trial', async () => {
            await helpers.initializeSdk(constants.trialLicense);
            await helpers.validateLicense(constants.config.license.trial, 1000);
        });

        it ('SDK Initialized with Trial License, verify Trial license expires after 60 seconds', async () => {

            function sleep(milliseconds) {
                return new Promise(resolve => setTimeout(resolve, milliseconds))
            }

            // start app with trial license and validate trial license info is correct
            await helpers.initializeSdk(constants.trialLicense);
            await helpers.validateLicense(constants.config.license.trial, 1000);
            
            // wait 61 seconds so that trial license is expired
            await sleep(61000)

            // validate that license is not set
            await helpers.validateLicense(constants.config.license.notSet, 15000);
        });

        it ('SDK Initialized with Expired License', async () => {
            await helpers.initializeSdk(constants.expiredLicense);
            await helpers.validateLicense(constants.config.license.expired, 15000);
        });

        if (device.platform == "Android") {
            it ('SDK Initialized with Android only license for Android device', async () => {
                await helpers.initializeSdk(constants.androidLicense);
                await helpers.validateLicense(constants.config.license.correctOs, 15000);
            });
            it ('SDK Initialization with iOS only license on Android device fails', async () => {
                await helpers.initializeSdk(constants.iosLicense);
                await helpers.validateLicense(constants.config.license.wrongOs, 15000);
            });
        }
        
        if (device.platform == "iOS") {
            it ('SDK Initialized with iOS only license for iOS device', async () => {
                await helpers.initializeSdk(constants.iosLicense);
                await helpers.validateLicense(constants.config.license.correctOs, 15000);
            });
            it ('SDK Initialization with Android only license on iOS device fails', async () => {
                await helpers.initializeSdk(constants.androidLicense);
                await helpers.validateLicense(constants.config.license.wrongOs, 15000);
            });
        }

        it ('SDK Initialization with a license that has an App ID that does not match the App fails', async () => {
            await helpers.initializeSdk(constants.appIdMismatchLicense);
            await helpers.validateLicense(constants.config.license.appIdMismatch, 15000);
        });

        it ('SDK Initialization with a corrupted license fails', async () => {
            await helpers.initializeSdk(constants.corruptedLicense);
            await helpers.validateLicense(constants.config.license.corrupted, 15000);
        });
        
        it ('SDK Initialized with Valid License', async () => {
            await helpers.initializeSdk(constants.validLicense);
            await helpers.validateLicense(constants.config.license.okay, 0);
        });
    });

    describe('Document Detection Scenarios:', function () {
        beforeAll(async function() {
            await helpers.initializeSdk(constants.validLicense);
        });

        // TODO: add OK_BARCODE, OK_OFF_CENTER, ERROR_NOTHING_DETECTED, ERROR_TOO_NOISY scenarios
        it ('detection result OK, but bad aspect ratio', async () => {
            expect((await helpers.detectDocument(constants.images.image.aspect_ratio, 1000)).detectionResult)
            .toBe(constants.images.image.aspect_ratio.result);
        });

        it ('detection result OK, but bad angles', async () => {
            expect((await helpers.detectDocument(constants.images.image.bad_angles, 1000)).detectionResult)
            .toBe(constants.images.image.bad_angles.result);
        });

        // it ('detection result Error, too dark', async () => {
        //     expect((await helpers.detectDocument(constants.images.image.dark, 1000)).detectionResult)
        //     .toBe(constants.images.image.dark.result);
        // });

        // it ('detection result Error, too dark, ML_BASED', async () => {
        //     expect((await helpers.detectDocument(constants.images.image.dark, 1000, "ML_BASED")).detectionResult)
        //     .toBe(constants.images.image.dark.result);
        // });

        // it ('detection result OK', async () => {
        //     expect((await helpers.detectDocument(constants.images.image.ok, 1000)).detectionResult)
        //     .toBe(constants.images.image.ok.result);
        // });

        it ('detection result OK, but too small', async () => {
            expect((await helpers.detectDocument(constants.images.image.small, 1000)).detectionResult)
            .toBe(constants.images.image.small.result);
        });
    });

    describe('Document Detection On Page Scenarios:', function () {
        beforeAll(async function() {
            await helpers.initializeSdk(constants.validLicense);
        });

        // TODO: add OK_BARCODE, OK_OFF_CENTER, ERROR_NOTHING_DETECTED, ERROR_TOO_NOISY scenarios
        it ('detection result OK, but bad aspect ratio', async () => {
            expect(await helpers.detectDocumentOnPage(constants.images.image.aspect_ratio))
            .toBe(constants.images.image.aspect_ratio.result);
        });

        it ('detection result OK, but bad angles', async () => {
            expect(await helpers.detectDocumentOnPage(constants.images.image.bad_angles))
            .toBe(constants.images.image.bad_angles.result);
        });

        // it ('detection result Error, too dark', async () => {
        //     expect(await helpers.detectDocumentOnPage(constants.images.image.dark))
        //     .toBe(constants.images.image.dark.result);
        // });

        // it ('detection result OK', async () => {
        //     expect(await helpers.detectDocumentOnPage(constants.images.image.ok))
        //     .toBe(constants.images.image.ok.result);
        // });

        it ('detection result OK, but too small', async () => {
            expect(await helpers.detectDocumentOnPage(constants.images.image.small))
            .toBe(constants.images.image.small.result);
        });
    });

    describe('Save PDF Scenarios:', function () {
        beforeAll(async function() {
            await helpers.initializeSdk(constants.validLicense);
        });

        it ('file saved as PDF using FROM_IMAGE size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'FROM_IMAGE'))
            .toBe(true);
        });

        it ('file saved as PDF using A4 size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'A4'))
            .toBe(true);
        });

        it ('file saved as PDF using FIXED_A4 size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'FIXED_A4'))
            .toBe(true);
        });

        it ('file saved as PDF using US_LETTER size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'US_LETTER'))
            .toBe(true);
        });

        it ('file saved as PDF using AUTO_LOCALE size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'AUTO_LOCALE'))
            .toBe(true);
        });

        it ('file saved as PDF using AUTO size', async () => {
            expect(await helpers.validatePdfCreated(
                constants.images.image.ok,
                'AUTO'))
            .toBe(true);
        }); 
    });

    describe('TIFF Scenarios:', function () {
        beforeAll(async function() {
            await helpers.initializeSdk(constants.validLicense);
        });

        it ('file written as TIFF using NONE compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'NONE'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITTRLE compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITTRLE'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITTFAX3 compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITTFAX3'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITT_T4 compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITT_T4'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITTFAX4 compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITTFAX4'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITT_T6 compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITT_T6'))
            .toBe(true);
        }); 

        it ('file written as TIFF using CCITTRLEW compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'CCITTRLEW'))
            .toBe(true);
        }); 

        it ('file written as TIFF using LZW compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'LZW'))
            .toBe(true);
        }); 

        it ('file written as TIFF using PACKBITS compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'PACKBITS'))
            .toBe(true);
        }); 

        it ('file written as TIFF using DEFLATE compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'DEFLATE'))
            .toBe(true);
        }); 

        it ('file written as TIFF using ADOBE_DEFLATE compression, encoded, dpi=300', async () => {
            expect(await helpers.validateWriteTiff(
                constants.images.image.ok,
                true,
                300,
                'ADOBE_DEFLATE'))
            .toBe(true);
        }); 
    });

    describe('Polygon Detection Scenarios:', function () {
        beforeAll(async function() {
            await helpers.initializeSdk(constants.validLicense);
        });

        it ('Polygon values are valid, OK scenario, ML_BASED', async () => {
            expect(await helpers.validatePolygons(
                constants.images.image.ok_ml,
                1000,
                "ML_BASED"
            ))
            .toBe(true);
        }); 

        it ('Polygon values are valid, OK scenario', async () => {
            expect(await helpers.validatePolygons(
                constants.images.image.ok,
                1000
            ))
            .toBe(true);
        }); 

        it ('Polygon values are valid, OK_BUT_BAD_ANGLES scenario, ML_BASED', async () => {
            expect(await helpers.validatePolygons(
                constants.images.image.bad_angles,
                1000,
                "ML_BASED"
            ))
            .toBe(true);
        }); 

        it ('Polygon values are valid, OK_BUT_BAD_ANGLES scenario', async () => {
            expect(await helpers.validatePolygons(
                constants.images.image.bad_angles,
                1000
            ))
            .toBe(true);
        });
    });
};