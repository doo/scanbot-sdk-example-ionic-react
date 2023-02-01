/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova;

import android.Manifest;
import android.app.Application;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.PointF;
import android.net.Uri;
import android.preference.PreferenceManager;
import android.util.Base64;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.LOG;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.Set;
import java.util.HashSet;
import java.util.List;

import io.scanbot.sap.SapManager;
import io.scanbot.sap.SdkLicenseInfo;
import io.scanbot.sdk.ScanbotSDK;
import io.scanbot.sdk.ScanbotSDKInitializer;
import io.scanbot.sdk.barcode.BarcodeFilter;
import io.scanbot.sdk.barcode.ScanbotBarcodeDetector;
import io.scanbot.sdk.barcode.entity.BarcodeFormat;
import io.scanbot.sdk.barcode.entity.BarcodeItem;
import io.scanbot.sdk.barcode.entity.BarcodeScanningResult;
import io.scanbot.sdk.core.contourdetector.ContourDetector;
import io.scanbot.sdk.core.contourdetector.DetectionResult;
import io.scanbot.sdk.core.contourdetector.DetectionStatus;
import io.scanbot.sdk.ocr.OpticalCharacterRecognizer;
import io.scanbot.sdk.ocr.process.OcrResult;
import io.scanbot.sdk.persistence.DocumentStoreStrategy;
import io.scanbot.sdk.persistence.Page;
import io.scanbot.sdk.persistence.PageFileStorage;
import io.scanbot.sdk.persistence.PageStorageSettings;
import io.scanbot.sdk.plugin.cordova.dto.JsonPage;
import io.scanbot.sdk.plugin.cordova.helpers.ScanbotBarcodeDetectorConfigBuilder;
import io.scanbot.sdk.plugin.cordova.utils.Conversion;
import io.scanbot.sdk.plugin.cordova.utils.SDKError;
import io.scanbot.sdk.plugin.cordova.utils.StorageUtils;
import io.scanbot.sdk.plugin.cordova.utils.ImageUtils;
import io.scanbot.sdk.plugin.cordova.utils.JsonArgs;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import io.scanbot.sdk.plugin.cordova.utils.LogUtils;
import io.scanbot.sdk.plugin.cordova.utils.ObjectMapper;
import io.scanbot.sdk.process.ImageFilterType;
import io.scanbot.sdk.process.ImageProcessor;
import io.scanbot.sdk.process.PDFPageSize;
import io.scanbot.sdk.tiff.model.TIFFImageWriterCompressionOptions;
import kotlin.Unit;
import kotlin.jvm.functions.Function1;
/**
 * Scanbot SDK Cordova Plugin
 */
public class ScanbotSdkPlugin extends ScanbotCordovaPluginBase {

    private static final String LOG_TAG = ScanbotSdkPlugin.class.getSimpleName();

    // A set of TIFF compression types, which are compatible only with binarized images (1-bit encoded).
    private static final Set<TIFFImageWriterCompressionOptions> binarizedOnlyCompressionTypes =
            new HashSet<>();

    static {
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITTRLE);
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITTFAX3);
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITT_T4);
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITTFAX4);
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITT_T6);
        binarizedOnlyCompressionTypes.add(TIFFImageWriterCompressionOptions.COMPRESSION_CCITTRLEW);
    }

    private static ScanbotSdkConfiguration config = null;
    private static boolean encrypt = false;

    @Override
    protected String getLogTag() {
        return LOG_TAG;
    }

    private byte[] stringToBytes(String stringified) {
        char[] go = stringified.toCharArray();
        byte[] bytes = new byte[go.length];
        for (int i = 0; i < go.length; i++) {
            bytes[i] = (byte) go[i];
        }
        return bytes;
    }

    private static final int ID_REQUEST_CAMERA_PERMISSION = 1337;
    private CallbackContext permissionsCallback;

    @Override
    public void onRequestPermissionResult(int requestCode, String[] permissions, int[] grantResults) throws JSONException {
        if (permissionsCallback == null) {
            return;
        }

        if (permissions != null && permissions.length > 0) {
            for (int grantResult : grantResults) {
                if (grantResult == android.content.pm.PackageManager.PERMISSION_DENIED) {
                    JsonArgs json = new JsonArgs()
                            .put("status", "ERROR")
                            .put("message", "Camera permission not granted");
                    successCallback(permissionsCallback, false, json);
                    return;
                }
            }
            JsonArgs json = new JsonArgs().put("status", "OK");
            successCallback(permissionsCallback, false, json);
        } else {
            errorCallback(permissionsCallback, "No permissions to request");
        }
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {

        if (action.equals("requestCameraPermission")) {
            String permission = Manifest.permission.CAMERA;
            permissionsCallback = callbackContext;
            if (cordova.hasPermission(permission)) {
                JsonArgs json = new JsonArgs().put("status", "OK");
                successCallback(permissionsCallback, false, json);
                return true;
            }
            cordova.requestPermission(this, ID_REQUEST_CAMERA_PERMISSION, permission);
            return true;
        }

        if (action.equals("detectBarcodesFromBytes")) {
            cordova.getThreadPool().execute(() -> {
                try {
                    ScanbotBarcodeDetector detector = sdkWrapper.barcodeDetector();

                    int width = args.getInt(0);
                    int height = args.getInt(1);
                    String stringified = args.getString(2);
                    String formatString = args.getString(3);

                    byte[] bytes = stringToBytes(stringified);
                    List<BarcodeItem> items = new ArrayList<>();

                    List<BarcodeFormat> formats = JsonUtils.formatsFromString(formatString);
                    detector.modifyConfig(builder -> {
                        builder.setBarcodeFormats(formats);
                        return null;
                    });
                    BarcodeScanningResult result = detector.detectFromRgba(bytes, width, height, 0);
                    if (result != null) {
                        items = result.getBarcodeItems();
                    }


                    JSONArray barcodes = JsonUtils.jsonFromBarcodeItems(items);
                    JsonArgs json = new JsonArgs().put("status", "OK").put("barcodes", barcodes);
                    successCallback(callbackContext, false, json);
                } catch (final Exception e) {
                    String message = "Could not perform barcode detection stream";
                    errorCallback(callbackContext, message, e);
                }
            });

            return true;
        }

        LOG.d(LOG_TAG, "execute: action=" + action + "; callbackId=" + callbackContext.getCallbackId());
        final JSONObject jsonArgs = (args.length() > 0 ? args.getJSONObject(0) : new JSONObject());
        debugLog("JSON args: " + jsonArgs.toString());

        if (action.equals("initializeSdk")) {
            initializeSdk(jsonArgs, callbackContext);
            return true;
        }

        if (!isSdkInitialized()) {
            errorCallback(callbackContext, "Scanbot SDK is not initialized. Please use 'initializeSdk(...)' to initialize the Scanbot SDK.");
            return true;
        }

        if (action.equals("isLicenseValid")) {
            try {
                isLicenseValid(callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not perform license validation.", e);
            }
            return true;
        }

        if (action.equals("detectDocument")) {
            try {
                detectDocument(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not perform document detection.", e);
            }
            return true;
        }

        if (action.equals("performOcr")) {
            try {
                performOcr(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not perform OCR.", e);
            }
            return true;
        }

        if (action.equals("getOcrConfigs")) {
            try {
                getOcrConfigs(callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not get OCR configs.", e);
            }
            return true;
        }

        if (action.equals("applyImageFilter")) {
            try {
                applyImageFilter(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not apply image filter on image.", e);
            }
            return true;
        }

        if (action.equals("applyImageFilterOnPage")) {
            try {
                applyImageFilterOnPage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not apply image filter on page.", e);
            }
            return true;
        }

        if (action.equals("getFilteredDocumentPreviewUri")) {
            try {
                getFilteredDocumentPreviewUri(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not get filtered document preview image URI.", e);
            }
            return true;
        }

        if (action.equals("rotateImage")) {
            try {
                rotateImage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not apply rotation on image.", e);
            }
            return true;
        }

        if (action.equals("rotatePage")) {
            try {
                rotatePage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not apply rotation on page.", e);
            }
            return true;
        }

        if (action.equals("createPdf")) {
            try {
                createPdf(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not create PDF.", e);
            }
            return true;
        }

        if (action.equals("writeTiff")) {
            try {
                writeTiff(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not create TIFF.", e);
            }
            return true;
        }

        if (action.equals("cleanup")) {
            try {
                cleanup(callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not cleanup the temporary directory of Scanbot SDK Plugin.", e);
            }
            return true;
        }

        if (action.equals("createPage")) {
            try {
                createPage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not create pages.", e);
            }
            return true;
        }

        if (action.equals("detectDocumentOnPage")) {
            try {
                detectDocumentOnPage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error while detecting document on page.", e);
            }
            return true;
        }

        if (action.equals("setDocumentImage")) {
            try {
                setDocumentImage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not set document image.", e);
            }
            return true;
        }

        if (action.equals("removePage")) {
            try {
                removePage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not remove page.", e);
            }
            return true;
        }

        if (action.equals("detectBarcodesOnImage")) {
            try {
                detectBarcodesOnImage(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not detect barcodes on the given image.", e);
            }
            return true;
        }

        if (action.equals("detectBarcodesOnImages")) {
            try {
                detectBarcodesOnImages(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not detect barcodes on the given images");
            }
            return true;
        }

        if (action.equals("getLicenseInfo")) {
            try {
                getLicenseInfo(callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not get license info.", e);
            }
            return true;
        }

        if (action.equals("setLicenseFailureHandler")) {
            try {
                setLicenseFailureHandler(callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not set license failure handler.", e);
            }
            return true;
        }

        if (action.equals("estimateBlur")) {
            try {
                estimateBlur(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not estimate blurriness on image.", e);
            }
            return true;
        }

        if (action.equals("refreshImageUris")) {
            try {
                refreshImageUris(jsonArgs, callbackContext);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not refresh image URIs of the page.", e);
            }
            return true;
        }
        if (action.equals("getImageData")) {
            cordova.getThreadPool().execute(() -> {
                try {
                    getImageData(jsonArgs, callbackContext);
                } catch (final Exception e) {
                    errorCallback(callbackContext, "Could not get base64 data of encrypted images", e);
                }
            });

            return true;
        }
        return false;
    }

    private void getImageData(JSONObject args, CallbackContext context) {
        try {
            final String imageFileUri = getImageFileUriArg(args);
            final File file = new File(Uri.parse(imageFileUri).getPath());
            if (!file.exists()) {
                errorCallback(context, String.format("File not found: %s", imageFileUri));
                return;
            }
            // In case image file encryption is enabled, the corresponding FileIOProcessor
            // implementation will decrypt image data under the hood:
            byte[] data = sdkWrapper.fileProcessor().read(file);
            JsonArgs json = JsonArgs.kvp("base64ImageData", Base64.encodeToString(data, Base64.DEFAULT));
            successCallback(context, false, json);
        } catch (Exception e) {
            errorCallback(context, "Failed to load image data", e);
        }
    }

    private void refreshImageUris(JSONObject args, CallbackContext callbackContext) throws JSONException {
        // This method is actually not required on Android. We just provide a dummy implementation
        // to stay consistent with the Cordova API and iOS. See the comments of the iOS implementation.
        final JSONArray jsonPages = getPagesJsonArg(args, true);
        try {
            // simply pass back the JSON pages
            successCallback(callbackContext, false, new JsonArgs()
                    .put("pages", jsonPages)
            );
        } catch (final Exception e) {
            final String message = "Could not refresh image URIs";
            errorCallback(callbackContext, message, e);
        }
    }

    private void estimateBlur(JSONObject args, CallbackContext callbackContext) throws JSONException {
        final String imageFileUri = getImageFileUriArg(args);
        execute(() -> {
            Bitmap bitmap;
            try {
                bitmap = loadImage(imageFileUri);
            } catch (Exception e) {
                bitmap = null;
            }
            try {
                if (bitmap == null) {
                    // might be an encrypted image, try to decrypt (done under the hood via current fileIOProcessor):
                    bitmap = sdkWrapper.sdk().fileIOProcessor().readImage(Uri.parse(imageFileUri), null);
                }
                float result = sdkWrapper.sdk().createBlurEstimator().estimateInBitmap(bitmap, 0);
                successCallback(callbackContext, false, new JsonArgs().put("blur", result));
            } catch (Exception e) {
                String message = "Could not perform blur estimation on image: " + imageFileUri;
                errorCallback(callbackContext, message, e);
            }
        });
    }

    private void execute(Runnable runnable) {
        cordova.getThreadPool().execute(runnable);
    }

    private void detectBarcodesOnImage(JSONObject args, CallbackContext callbackContext) throws JSONException {
        cordova.getThreadPool().execute(() -> {
            String imageFileUri = "";
            try {
                imageFileUri = getImageFileUriArg(args);
                // Instantiates and configures the detector
                ScanbotBarcodeDetector detector = createBarcodeDetector(args);
                JsonArgs jsonResult = detectBarcodesWithExtensionFilter(detector, args, imageFileUri);
                // null result case handled in above function with same response
                successCallback(callbackContext, false, jsonResult);
            } catch (final Exception e) {
                String message = "Could not perform barcode detection on image: " + imageFileUri;
                errorCallback(callbackContext, message, e);
            }
        });
    }

    private void detectBarcodesOnImages(JSONObject args, CallbackContext callbackContext) throws JSONException {
        final JSONArray imageFilesUris = JsonUtils.getJsonArray(args, "imageFilesUris", null);
        if (imageFilesUris == null || imageFilesUris.length() == 0) {
            String message = "Could not perform barcode detection on images";
            errorCallback(callbackContext, message, null);
            return;
        }
        debugLog("Performing document detection on the images");
        cordova.getThreadPool().execute(() -> {
            try {
                // Instantiates and configures the detector
                ScanbotBarcodeDetector detector = createBarcodeDetector(args);
                // Detect the barcodes and produces the JSON output
                JSONArray barcodeResultsJSON = new JSONArray();
                for (int i = 0; i < imageFilesUris.length(); ++i) {
                    String imageFileUri = imageFilesUris.getString(i);
                    JsonArgs resultJson = detectBarcodesWithExtensionFilter(detector, args, imageFileUri);
                    barcodeResultsJSON.put(resultJson.jsonObj());
                }

                JsonArgs outputResultJSON = new JsonArgs();
                outputResultJSON.put("results", barcodeResultsJSON);
                outputResultJSON.put("status", "OK");
                successCallback(callbackContext, false, outputResultJSON);

            } catch (final Exception e) {
                String message = "Could not perform barcode detection on the images";
                errorCallback(callbackContext, message, e);
            }
        });
    }

    /**
     * Common function for detecting barcodes from single image.
     *
     * @param detector
     * @param args
     * @param imageFileUri: Image path
     * @return Json Object with final result Json.
     */
    private JsonArgs detectBarcodesWithExtensionFilter(ScanbotBarcodeDetector detector, JSONObject args, String imageFileUri) {
        JsonArgs jsonResult = null;
        try {
            final boolean shouldFilterBarcodes = args.has("barcodeFilter");
            // Detect the barcodes and produces the JSON output
            Bitmap sourceImage = loadImage(imageFileUri);
            BarcodeScanningResult result = detector.detectFromBitmap(sourceImage, 0);
            String keyName = args.has("imageFilesUris") ? "barcodeResults" : "barcodes";
            if (shouldFilterBarcodes) {
                final BarcodeFilter barcodeFilter = JsonUtils.extractBarcodeFilter(args);
                if (barcodeFilter == null) {
                    throw new IllegalArgumentException("Invalid Barcode Filter specified in JSON configuration: " + args.getString("barcodeFilter"));
                }
                final List<BarcodeItem> barcodeItems = JsonUtils.getBarcodeItemsFromResultWithFilter(result, barcodeFilter);
                jsonResult = jsonResultFromBarcodeScannerResult(barcodeItems, keyName);
            } else {
                jsonResult = jsonResultFromBarcodeScannerResult(result, keyName);
            }
            jsonResult.put("imageFileUri", imageFileUri);
        } catch (Exception ex) {
            debugLog(ex.getMessage());
            jsonResult.put("imageFileUri", imageFileUri);
            jsonResult.put("error", String.format("Cannot detect barcodes on the given image: %s", ex.getLocalizedMessage()));
        }
        return jsonResult;
    }

    private void getLicenseInfo(CallbackContext callbackContext) {

        SdkLicenseInfo info = sdkWrapper.getLicenseInfo();

        try {
            successCallback(callbackContext, false, "info", new JSONObject()
                    .put("isLicenseValid", info.isValid())
                    .put("licenseStatus", Conversion.statusToString(info.getStatus()))
                    .put("licenseExpirationDate", getMilliseconds(info.getExpirationDate())));
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error getting license info.", e);
        }
    }

    private long getMilliseconds(Date date) {
        long milliseconds = -1;
        if (date != null) {
            milliseconds = date.getTime();
        }
        return milliseconds;
    }

    private void setLicenseFailureHandler(CallbackContext callbackContext) {
        new SapManager().setLicenceErrorHandler((status, sdkFeature, errorMessage) -> {
            try {
                successCallback(callbackContext, false, new JsonArgs()
                        .put("licenseStatus", status)
                        .put("licenseFeature", sdkFeature)
                        .put("licenseErrorMessage", errorMessage));
            } catch (Exception e) {
                errorCallback(callbackContext, "Error setting license error handler.", e);
            }
        });
    }

    private static synchronized void setSdkInitialized(ScanbotSdkConfiguration config) {
        ScanbotSdkPlugin.config = config;
    }

    public static synchronized boolean isSdkInitialized() {
        return ScanbotSdkPlugin.config != null;
    }


    /**
     * Initializes Scanbot SDK.
     *
     * @param args Optional JSON Args:
     *             loggingEnabled: true,
     *             licenseKey: 'xyz..'
     *             storageImageQuality: 1-100
     *             storageImageFormat: "JPEG" or "PNG"
     */
    private void initializeSdk(final JSONObject args, final CallbackContext callbackContext) {
        debugLog("Initializing Scanbot SDK ...");
        cordova.getThreadPool().execute(() -> {
            try {
                final ScanbotSdkConfiguration configuration = new ScanbotSdkConfiguration();
                ObjectMapper.map(args, configuration);

                final Application app = cordova.getActivity().getApplication();
                final String callbackMessage;

                LogUtils.setLoggingEnabled(configuration.isLoggingEnabled());
                final ScanbotSDKInitializer initializer = new ScanbotSDKInitializer();
                initializer.withLogging(LogUtils.isLoggingEnabled(), configuration.getEnableNativeLogging());

                if ("EDGE_BASED".equals(configuration.getDocumentDetectorMode())) {
                    initializer.contourDetectorType(ContourDetector.Type.EDGE_BASED);
                }

                initializer.allowGpuAcceleration(configuration.getAllowGpuAcceleration());
                initializer.allowXnnpackAcceleration(configuration.getAllowXnnpackAcceleration());
                initializer.useCameraXRtuUi(configuration.getUseCameraX());

                if (configuration.getStorageBaseDirectory() != null && !"".equals(configuration.getStorageBaseDirectory())) {
                    final Uri uri = Uri.parse(configuration.getStorageBaseDirectory());
                    final File customStorageBaseDirectory = new File(uri.getPath());
                    customStorageBaseDirectory.mkdirs();
                    if (!customStorageBaseDirectory.isDirectory()) {
                        throw new IOException("Specified storageBaseDirectory is not valid: " + uri);
                    }
                    initializer.sdkFilesDirectory(app, customStorageBaseDirectory);
                    StorageUtils.setCustomStorageBaseDirectory(customStorageBaseDirectory);
                    debugLog("Using custom storage base directory: " + customStorageBaseDirectory.getAbsolutePath());
                }

                final String licenseKey = configuration.getLicenseKey();
                if (licenseKey != null && !"".equals(licenseKey.trim()) && !"null".equals(licenseKey.toLowerCase())) {
                    initializer.license(app, licenseKey);
                    callbackMessage = "Scanbot SDK initialized.";
                } else {
                    callbackMessage = "Scanbot SDK initialized. Trial mode activated. You can now test all features for 60 seconds.";
                }

                initializer.usePageStorageSettings(new PageStorageSettings.Builder()
                        .imageQuality(configuration.getStorageImageQuality())
                        .imageFormat(configuration.getStorageImageFormat())
                        .previewTargetMax(1500) // max size for the preview images
                        .build());

                initializer.prepareOCRLanguagesBlobs(true);
                initializer.prepareMRZBlobs(true);
                initializer.imageProcessorType(ImageProcessor.Type.ML_BASED);

                if (configuration.encryptImages()) {
                    ScanbotSdkPlugin.encrypt = true;
                    initializer.useFileEncryption(true, configuration.encryptionProcessor());
                }

                initializer.initialize(app);

                setSdkInitialized(configuration);
                debugLog(callbackMessage);
                successCallback(callbackContext, false, callbackMessage);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error initializing Scanbot SDK.", e);
            }
        });
    }

    private void isLicenseValid(final CallbackContext callbackContext) {
        debugLog("Checking Scanbot SDK license...");
        final ScanbotSDK scanbotSDK = new ScanbotSDK(cordova.getActivity());
        cordova.getThreadPool().execute(() -> {
            try {
                successCallback(callbackContext, false,
                        JsonArgs.kvp("isLicenseValid", scanbotSDK.isLicenseValid()));
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error checking Scanbot SDK license.", e);
            }
        });
    }


    private void detectDocument(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final String imageFileUri = getImageFileUriArg(args);
        final int quality = getImageQualityArg(args);
        debugLog("Performing document detection on image: " + imageFileUri);
        debugLog("quality: " + quality);

        cordova.getThreadPool().execute(() -> {
            try {
                final Bitmap sourceImage = loadImage(imageFileUri);
                final ScanbotSdkWrapper.DocumentDetectionResult result = sdkWrapper.documentDetection(sourceImage);

                if (result == null) {
                    errorCallback(callbackContext, "Could not perform document detection on image: " + imageFileUri);
                    return;
                }

                debugLog("Document detection result: " + result.sdkDetectionResult.getStatus());
                debugLog("Document detection polygon: " + result.polygon);

                final Uri resultImgUri;
                if (result.documentImage != null) {
                    resultImgUri = sdkWrapper.storeImage(result.documentImage, quality);
                    debugLog("Stored document image: " + resultImgUri.toString());
                } else {
                    resultImgUri = null;
                }

                successCallback(callbackContext, false, new JsonArgs()
                        .put("detectionResult", JsonUtils.sdkDetectionResultToJsString(result.sdkDetectionResult.getStatus()))
                        .put("documentImageFileUri", (resultImgUri != null ? resultImgUri.toString() : null))
                        .put("polygon", JsonUtils.sdkPolygonToJson(result.polygon))
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not perform document detection on image: " + imageFileUri, e);
            }
        });
    }


    private void applyImageFilter(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final String imageFileUri = getImageFileUriArg(args);
        final String imageFilter = getImageFilterArg(args);
        final int quality = getImageQualityArg(args);

        debugLog("Applying image filter (" + imageFilter + ") on image: " + imageFileUri);
        debugLog("quality: " + quality);

        cordova.getThreadPool().execute(() -> {
            try {
                final Bitmap bitmap = loadImage(imageFileUri);
                final Bitmap result = sdkWrapper.applyImageFilter(bitmap, JsonUtils.jsImageFilterToSdkFilter(imageFilter));
                final Uri resultImgUri = sdkWrapper.storeImage(result, quality);
                debugLog("Stored filtered image: " + resultImgUri.toString());

                successCallback(callbackContext, false, new JsonArgs()
                        .put("imageFileUri", resultImgUri.toString())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error applying filter on image: " + imageFileUri, e);
            }
        });
    }


    private void getFilteredDocumentPreviewUri(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final Page page = JsonPage.fromJson(getPageJsonArg(args, true)).asSdkPage();
        final String imageFilter = getImageFilterArg(args);

        cordova.getThreadPool().execute(() -> {
            try {
                final ImageFilterType filterType = JsonUtils.jsImageFilterToSdkFilter(imageFilter);
                final Uri filteredPreviewUri = sdkWrapper.getFilteredDocumentPreviewUri(page, filterType);

                successCallback(callbackContext, false, new JsonArgs()
                        .put("imageFileUri", StorageUtils.uriWithHash(filteredPreviewUri.toString()))
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error getting filtered preview image URI of page: " + page.getPageId(), e);
            }
        });
    }


    private void applyImageFilterOnPage(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final Page page = JsonPage.fromJson(getPageJsonArg(args, true)).asSdkPage();
        final String imageFilter = getImageFilterArg(args);

        cordova.getThreadPool().execute(() -> {
            try {
                final Page updatedPage = sdkWrapper.applyImageFilterOnPage(page, JsonUtils.jsImageFilterToSdkFilter(imageFilter));

                successCallback(callbackContext, false, new JsonArgs()
                        .put("page", JsonPage.fromSdkPage(updatedPage, sdkWrapper.pageFileStorage()).asJsonObj())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error applying filter on page: " + page.getPageId(), e);
            }
        });
    }


    private void rotateImage(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final String imageFileUri = getImageFileUriArg(args);
        final int degrees = getDegreesArg(args);
        final int quality = getImageQualityArg(args);
        debugLog("Applying image rotation with " + degrees + " degrees on image: " + imageFileUri);
        debugLog("quality: " + quality);

        cordova.getThreadPool().execute(() -> {
            try {
                final Bitmap bitmap = loadImage(imageFileUri);
                final Uri resultImgUri = sdkWrapper.storeImage(ImageUtils.rotateBitmap(bitmap, -degrees), quality);
                debugLog("Stored rotated image: " + resultImgUri.toString());

                successCallback(callbackContext, false, new JsonArgs()
                        .put("imageFileUri", resultImgUri.toString())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error applying rotation on image: " + imageFileUri, e);
            }
        });
    }


    private void rotatePage(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final Page page = JsonPage.fromJson(getPageJsonArg(args, true)).asSdkPage();
        final int times = getTimesArg(args);
        debugLog("Rotating page " + page.getPageId() + " " + times + " times...");

        cordova.getThreadPool().execute(() -> {
            try {
                final Page updatedPage = sdkWrapper.rotatePage(page, times);

                successCallback(callbackContext, false, new JsonArgs()
                        .put("page", JsonPage.fromSdkPage(updatedPage, sdkWrapper.pageFileStorage()).asJsonObj())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error applying filter on page.", e);
            }
        });
    }


    private void createPdf(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final List<Uri> images = getImagesArg(args);
        if (images.size() == 0) {
            errorCallback(callbackContext, "At least one image must be present.");
            return;
        }

        final PDFPageSize pageSize = getPDFPageSizeArg(args);

        debugLog("Creating PDF of " + images.size() + " images ...");

        cordova.getThreadPool().execute(() -> {
            final ScanbotSdkWrapper.PdfSdk pdfSdk = new ScanbotSdkWrapper.PdfSdk(cordova.getActivity());
            File tempPdfFile = null;
            try {
                tempPdfFile = sdkWrapper.createPdf(images, pageSize, pdfSdk, ScanbotSdkPlugin.encrypt);
                debugLog("Got temp PDF file from SDK: " + tempPdfFile);

                File file = StorageUtils.generateRandomPluginStorageFile("pdf", cordova.getActivity());
                final Uri pdfOutputUri = Uri.fromFile(file);
                debugLog("Copying SDK temp file to plugin storage dir: " + pdfOutputUri);
                StorageUtils.copyFile(tempPdfFile, new File(pdfOutputUri.getPath()));

                successCallback(callbackContext, false, JsonArgs.kvp("pdfFileUri", pdfOutputUri));
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error creating PDF file.", e);
            } finally {
                if (tempPdfFile != null && tempPdfFile.exists()) {
                    boolean result = tempPdfFile.delete();
                    if (result) {
                        debugLog("Deleted temp file: " + tempPdfFile);
                    } else {
                        debugLog("Failed to delete temp file: " + tempPdfFile);
                    }
                }
            }
        });
    }

    private void writeTiff(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final List<Uri> images = getImagesArg(args);
        if (images.size() == 0) {
            errorCallback(callbackContext, "At least one image must be present.");
            return;
        }

        debugLog("Creating TIFF of " + images.size() + " images ...");

        cordova.getThreadPool().execute(() -> {
            try {
                final boolean binarized = getOneBitEncodedArg(args);
                final int dpi = getDpiArg(args, 200);
                final TIFFImageWriterCompressionOptions defaultCompression = (binarized ?
                        TIFFImageWriterCompressionOptions.COMPRESSION_CCITT_T6 :
                        TIFFImageWriterCompressionOptions.COMPRESSION_ADOBE_DEFLATE);
                final TIFFImageWriterCompressionOptions compression = getTiffCompressionArg(args, defaultCompression);

                if (!binarized && binarizedOnlyCompressionTypes.contains(compression)) {
                    errorCallback(callbackContext, SDKError.incompatibleCompression(compression.name()));
                    return;
                }

                final File tiffFile = sdkWrapper.writeTiff(images, binarized, dpi, compression, config.encryptImages());

                successCallback(callbackContext, false, new JsonArgs()
                        .put("tiffFileUri", Uri.fromFile(tiffFile).toString())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Error creating TIFF file.", e);
            }
        });
    }

    private void performOcr(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final List<Uri> images = getImagesArg(args);
        final List<String> languages = getLanguagesArg(args);
        final String outputFormat = JsonUtils.getJsonArg(args, "outputFormat", "PDF_FILE");

        if (images.size() == 0) {
            errorCallback(callbackContext, "At least one image must be present.");
            return;
        }

        debugLog("Performing OCR on " + images.size() + " images ...");

        cordova.getThreadPool().execute(() -> {
            final ScanbotSdkWrapper.PdfSdk pdfSdk = new ScanbotSdkWrapper.PdfSdk(cordova.getActivity());
            final SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(cordova.getActivity());
            final DocumentStoreStrategy documentStoreStrategy = new DocumentStoreStrategy(cordova.getActivity(), preferences);
            final OpticalCharacterRecognizer ocrRecognizer = pdfSdk.scanbotSDK.createOcrRecognizer();

            File tempPdfFile = null;
            try {
                // first check if requested languages are installed:
                final List<String> check = new ArrayList<>(languages);
                check.removeAll(sdkWrapper.getInstalledOcrLanguages(pdfSdk));
                if (!check.isEmpty()) {
                    errorCallback(callbackContext, "Missing OCR language files for languages: " + check.toString());
                    return;
                }

                final OcrResult result = sdkWrapper.performOcr(languages, ocrRecognizer, images, outputFormat, ScanbotSdkPlugin.encrypt);
                debugLog("Got OCR result from SDK: " + result);

                final JsonArgs jsonArgs = new JsonArgs();
                if (outputFormat.equals("PLAIN_TEXT")) {
                    jsonArgs.put("plainText", result.getRecognizedText());

                } else if (outputFormat.equals("RESULT_JSON")) {
                    jsonArgs.put("jsonData", JsonUtils.resultToJson(result));

                } else if (outputFormat.equals("PDF_FILE") || outputFormat.equals("FULL_OCR_RESULT")) {
                    tempPdfFile = documentStoreStrategy.getDocumentFile(
                            result.sandwichedPdfDocument.id, result.sandwichedPdfDocument.id + ".pdf");
                    debugLog("Got temp PDF file from SDK: " + tempPdfFile);

                    final Uri pdfOutputUri = Uri.fromFile(
                            StorageUtils.generateRandomPluginStorageFile("pdf", cordova.getActivity()));
                    debugLog("Copying SDK temp file to plugin storage dir: " + pdfOutputUri);
                    StorageUtils.copyFile(tempPdfFile, new File(pdfOutputUri.getPath()));

                    jsonArgs.put("pdfFileUri", pdfOutputUri.toString());

                    if (outputFormat.equals("FULL_OCR_RESULT")) {
                        jsonArgs.put("jsonData", JsonUtils.resultToJson(result));
                    }

                } else {
                    jsonArgs.put("plainText", result.getRecognizedText());
                }

                successCallback(callbackContext, false, jsonArgs);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not perform OCR on images: " + images.toString(), e);
            } finally {
                if (tempPdfFile != null && tempPdfFile.exists()) {
                    boolean result = tempPdfFile.delete();
                    if (result) {
                        debugLog("Deleted temp file: " + tempPdfFile);
                    } else {
                        debugLog("Failed to delete temp file: " + tempPdfFile);
                    }
                }
            }
        });

    }

    private void getOcrConfigs(final CallbackContext callbackContext) {
        cordova.getThreadPool().execute(() -> {
            try {
                final ScanbotSdkWrapper.PdfSdk pdfSdk = new ScanbotSdkWrapper.PdfSdk(cordova.getActivity());
                final List<String> languages = sdkWrapper.getInstalledOcrLanguages(pdfSdk);
                final File ocrBlobsDir = pdfSdk.blobManager.getOcrBlobsDirectory();
                final JsonArgs jsonResult = new JsonArgs();
                jsonResult.put("languageDataPath", Uri.fromFile(ocrBlobsDir).toString());
                jsonResult.put("installedLanguages", new JSONArray(languages));

                successCallback(callbackContext, false, jsonResult);
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not get OCR configs.", e);
            }
        });
    }

    private void createPage(final JSONObject args, final CallbackContext callbackContext) {
        cordova.getThreadPool().execute(() -> {
            try {
                final String imageFileUri = getImageFileUriArg(args, "original");
                final PageFileStorage pageFileStorage = sdkWrapper.pageFileStorage();
                final List<PointF> emptyPolygon = Collections.emptyList();

                final Bitmap bitmap = ImageUtils.prepareImageForImport(Uri.parse(imageFileUri), cordova.getActivity());
                final String pageId = pageFileStorage.add(bitmap);
                final Page page = new Page(pageId, emptyPolygon, DetectionStatus.OK, ImageFilterType.NONE);

                successCallback(callbackContext, false, new JsonArgs()
                        .put("page", JsonPage.fromSdkPage(page, pageFileStorage).asJsonObj())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not create page.", e);
            }
        });
    }

    private void detectDocumentOnPage(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final Page page = JsonPage.fromJson(getPageJsonArg(args, true)).asSdkPage();

        cordova.getThreadPool().execute(() -> {
            try {
                final Page updatedPage = sdkWrapper.detectDocumentOnPage(page);

                successCallback(callbackContext, false, new JsonArgs()
                        .put("page", JsonPage.fromSdkPage(updatedPage, sdkWrapper.pageFileStorage()).asJsonObj())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not detect document on page.", e);
            }
        });
    }

    private void setDocumentImage(final JSONObject args, final CallbackContext callbackContext) {
        cordova.getThreadPool().execute(() -> {
            try {
                final JsonPage page = JsonPage.fromJson(getPageJsonArg(args, true));
                final Uri imageFileUri = Uri.parse(getImageFileUriArg(args, "document"));
                final PageFileStorage pageFileStorage = sdkWrapper.pageFileStorage();
                Bitmap image = ImageUtils.loadImage(imageFileUri, cordova.getActivity());
                pageFileStorage.setImageForId(image, page.pageId, PageFileStorage.PageFileType.DOCUMENT);

                successCallback(callbackContext, false, new JsonArgs()
                        .put("page", JsonPage.fromSdkPage(page.asSdkPage(), pageFileStorage).asJsonObj())
                );
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not set document image on page.", e);
            }
        });
    }

    private void removePage(final JSONObject args, final CallbackContext callbackContext) throws JSONException {
        final JsonPage jsonPage = JsonPage.fromJson(getPageJsonArg(args, true));
        cordova.getThreadPool().execute(() -> {
            try {
                final PageFileStorage pageFileStorage = sdkWrapper.pageFileStorage();

                if (pageFileStorage.remove(jsonPage.pageId)) {
                    successCallback(callbackContext, false, "Page removed.");
                } else {
                    errorCallback(callbackContext, "Could not remove page.");
                }
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not remove page.", e);
            }
        });
    }

    private void cleanup(final CallbackContext callbackContext) {
        debugLog("Cleaning storage directories of the Scanbot SDK and Plugin ...");
        cordova.getThreadPool().execute(() -> {
            try {
                StorageUtils.cleanupPluginStorageDirectory(cordova.getActivity());
                sdkWrapper.pageFileStorage().removeAll();

                debugLog("Cleaning Barcode SDK storage folder ...");
                sdkWrapper.barcodeFileStorage().cleanupBarcodeImagesDirectory();

                successCallback(callbackContext, false, "Cleanup successfully done.");
            } catch (final Exception e) {
                errorCallback(callbackContext, "Could not cleanup all or some of the storage directories.", e);
            }
        });
    }

    // Utility Method to create a Barcode Detector with the given JSON configuration
    private ScanbotBarcodeDetector createBarcodeDetector(final JSONObject jsonConfig) {
        final ScanbotBarcodeDetector detector = sdkWrapper.barcodeDetector();
        detector.modifyConfig(new ScanbotBarcodeDetectorConfigBuilder(jsonConfig));
        return detector;
    }

    /**
     * @param barcodeItems
     * @param keyName      - KeyName is changed as per the model class property for Single image or Multiple images
     * @return
     * @throws JSONException
     */
    private static JsonArgs jsonResultFromBarcodeScannerResult(List<BarcodeItem> barcodeItems, String keyName) throws JSONException {
        final JSONArray barcodes = new JSONArray();
        for (BarcodeItem barcodeItem : barcodeItems) {
            final JSONObject barcode = new JSONObject();
            barcode.put("type", barcodeItem.getBarcodeFormat().name());
            barcode.put("text", barcodeItem.getText());
            barcode.put("textWithExtension", barcodeItem.getTextWithExtension());
            barcode.put("rawBytes", jsonFromRawBytes(barcodeItem.getRawBytes()));
            barcodes.put(barcode);
        }
        final JsonArgs result = new JsonArgs();
        result.put("status", "OK");
        result.put(keyName, barcodes);
        return result;
    }

    static JSONArray jsonFromRawBytes(byte[] rawBytes) {
        JSONArray jsonArray = new JSONArray();
        if (rawBytes.length > 0) {
            try {
                final JSONArray bytesArray = new JSONArray(rawBytes);
                jsonArray = bytesArray;
            } catch (JSONException e) {
            }
        }
        return jsonArray;
    }

    private static JsonArgs jsonResultFromBarcodeScannerResult(BarcodeScanningResult barcodeResult, String keyName) throws JSONException {
        if (barcodeResult != null) {
            return jsonResultFromBarcodeScannerResult(barcodeResult.getBarcodeItems(), keyName);
        } else {
            return jsonResultFromBarcodeScannerResult(new ArrayList<>(), keyName);
        }
    }
}
