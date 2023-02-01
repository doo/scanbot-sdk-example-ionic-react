const constants = require('./constants')
const SDK = ScanbotSdk.promisify();

async function initializeSdk(licenseKey, documentDetectorMode = 'ML_BASED') {
    const config = {
        loggingEnabled: true,
        licenseKey: licenseKey,
        documentDetectorMode: documentDetectorMode
    }
    return SDK.initializeSdk(config);
}

async function getLicenseInfo() {
    const licenseInfo = await SDK.getLicenseInfo();
    return licenseInfo;
}

async function validateLicense(config, gracePeriod) {
    // 1. check if license is valid
    var expectedLicenseValid = (await getLicenseInfo()).info.isLicenseValid;
    var actualLicenseValid = config.isLicenseValid;
    expect(expectedLicenseValid)
    .toBe(actualLicenseValid);

    // 2. check license status
    var expectedLicenseStatus = (await getLicenseInfo()).info.licenseStatus
    var actualLicenseStatus = config.licenseStatus
    expect(expectedLicenseStatus)
    .toBe(actualLicenseStatus);

    // // 3. check timestamp   
    // var expectedTimestamp = config.licenseExpirationDate
    // var actualTimestamp = (await getLicenseInfo()).info.licenseExpirationDate
    
    // const timestampDiff = Math.abs(expectedTimestamp - actualTimestamp)
    // // the difference between the expected and actual timestamp should be within the gracePeriod
    // expect(timestampDiff <= gracePeriod)
    // .toBeTruthy();
}

async function saveFile(url) {
    try {
        const saveResult = await SDK.Test.saveFile({url: url, token: constants.github_token});
        return await saveResult;
    }
    catch (error) {
        console.log('error', error);
    }
}

async function saveImagePath(object) {
    const saveImage = await saveFile(object.img);
    var saveImagePath = saveImage.path;
    if (saveImagePath.indexOf(' ') >= 0) {
        saveImagePath = saveImagePath.replace(" ", "%20");
    }
    return saveImagePath;
}

async function detectDocument(object, quality) {
    const imagePath = await saveImagePath(object);
    try {
        const detectionResult = await SDK.detectDocument({
            imageFileUri: imagePath,
            quality: quality
        });
        return await detectionResult;
    }
    catch (error) {
        console.log("error", error);
    }
}

async function createPage(originalImageFileUri) {
    try {
        const page = await SDK.createPage({originalImageFileUri: originalImageFileUri});
        return await page;
    }
    catch (error) {
        console.log('error', error);
    }
}

async function detectDocumentOnPage(object) {
    const imagePath = await saveImagePath(object);
    const createResult = await createPage(imagePath);
    try {
        const detectionResult = await SDK.detectDocumentOnPage({page: createResult.page});
        return await detectionResult.page.detectionResult;
    }
    catch (error) {
        console.log('error', error);
    }
}

async function createPdf(object, pageSize) {
    const savedImage = await saveFile(object.img)
    try {
        const createPdf = await SDK.createPdf({images: [savedImage.path], pageSize: pageSize})
        return await createPdf;
    }
    catch (error) {
        console.log('error', error);
    }
}

async function validatePdfCreated(object, pageSize) {
    var pdfCreated = false
    var createPdfObj = await createPdf(
        object,
        pageSize
        );
    
    if (createPdfObj.pdfFileUri.endsWith(".pdf") == true) {
        pdfCreated = true;
    }

    return pdfCreated;
}

async function writeTiff(object, oneBitEncoded, dpi, compression) {
    const savedImage = await saveFile(object.img)
    try {
        const writeTiff = await SDK.writeTiff({
            images: [savedImage.path],
            oneBitEncoded: oneBitEncoded,
            dpi: dpi,
            compression: compression
        });
        return await writeTiff;
    }
    catch (error) {
        console.log(error);
    }
}

async function validateWriteTiff(object, oneBitEncoded, dpi, compression) {
    var tiffCreated = false
    var createTiffObj = await writeTiff(
        object,
        oneBitEncoded,
        dpi,
        compression
        );
    
    if (createTiffObj.tiffFileUri.endsWith(".tiff") == true) {
        tiffCreated = true;
    }

    return tiffCreated;
}

async function validatePolygons(object, quality, algorithm) {    
    const imagePath = await saveImagePath(object);
    const detectionResult = await detectDocument(object, quality);

    var expectedPolygon = object.polygon;
    if (algorithm == "ML_BASED") {
        expectedPolygon = object.polygon_ml;
    }

    const actualPolygon = detectionResult.polygon;
    var valid = true;

    for (var i = 0; i < actualPolygon.length; i++) {
        for (var key in actualPolygon) {
            // defines a valid threshold of within +/- 0.02
            if ((actualPolygon[key] > expectedPolygon[key] + 0.02) || (actualPolygon[key] < expectedPolygon[key] - 0.02)) {
                valid = false;
            }
        }
    }
    return valid;
}

module.exports = {
    initializeSdk,
    getLicenseInfo,
    validateLicense,
    saveFile,
    saveImagePath,
    detectDocument,
    detectDocumentOnPage,
    createPdf,
    validatePdfCreated,
    writeTiff,
    validateWriteTiff,
    validatePolygons
}