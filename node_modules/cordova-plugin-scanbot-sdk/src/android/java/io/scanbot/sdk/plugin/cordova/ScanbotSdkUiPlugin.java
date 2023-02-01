/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Parcelable;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.LOG;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import io.scanbot.check.entity.Check;
import io.scanbot.check.entity.USACheck;
import io.scanbot.check.model.CheckRecognizerStatus;
import io.scanbot.genericdocument.entity.DeDriverLicenseBack;
import io.scanbot.genericdocument.entity.DeDriverLicenseFront;
import io.scanbot.genericdocument.entity.DeIdCardBack;
import io.scanbot.genericdocument.entity.DeIdCardFront;
import io.scanbot.genericdocument.entity.DePassport;
import io.scanbot.genericdocument.entity.Field;
import io.scanbot.genericdocument.entity.GenericDocument;
import io.scanbot.genericdocument.entity.GenericDocumentLibrary;
import io.scanbot.genericdocument.entity.GenericDocumentWrapper;
import io.scanbot.genericdocument.entity.MRZ;
import io.scanbot.genericdocument.entity.OcrResult;
import io.scanbot.genericdocument.entity.RootDocumentType;
import io.scanbot.genericdocument.entity.TextFieldWrapper;
import io.scanbot.genericdocument.entity.ValidatedTextFieldWrapper;
import io.scanbot.hicscanner.model.HealthInsuranceCardField;
import io.scanbot.hicscanner.model.HealthInsuranceCardRecognitionResult;
import io.scanbot.mrzscanner.model.MRZField;
import io.scanbot.mrzscanner.model.MRZRecognitionResult;
import io.scanbot.sdk.barcode.BarcodeFilter;
import io.scanbot.sdk.barcode.entity.BarcodeDensity;
import io.scanbot.sdk.barcode.entity.BarcodeDocumentFormat;
import io.scanbot.sdk.barcode.entity.BarcodeFormat;
import io.scanbot.sdk.barcode.entity.BarcodeItem;
import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfig;
import io.scanbot.sdk.barcode.entity.BarcodeScanningResult;
import io.scanbot.sdk.barcode.entity.EngineMode;
import io.scanbot.sdk.barcode.entity.MSIPlesseyChecksumAlgorithm;
import io.scanbot.sdk.camera.CameraPreviewMode;
import io.scanbot.sdk.check.entity.CheckRecognizerResult;
import io.scanbot.sdk.generictext.TextFilterStrategy;
import io.scanbot.sdk.licenseplate.LicensePlateScanStrategy;
import io.scanbot.sdk.persistence.Page;
import io.scanbot.sdk.persistence.PageFileStorage;
import io.scanbot.sdk.plugin.cordova.dto.JsonPage;
import io.scanbot.sdk.plugin.cordova.utils.ImageUtils;
import io.scanbot.sdk.plugin.cordova.utils.JsonArgs;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import io.scanbot.sdk.plugin.cordova.utils.ObjectMapper;
import io.scanbot.sdk.ui.camera.FinderAspectRatio;
import io.scanbot.sdk.ui.result.ResultRepository;
import io.scanbot.sdk.ui.result.ResultWrapper;
import io.scanbot.sdk.ui.view.barcode.BarcodeScannerActivity;
import io.scanbot.sdk.ui.view.barcode.batch.BatchBarcodeScannerActivity;
import io.scanbot.sdk.ui.view.barcode.batch.configuration.BatchBarcodeScannerConfiguration;
import io.scanbot.sdk.ui.view.barcode.configuration.BarcodeScannerAdditionalConfiguration;
import io.scanbot.sdk.ui.view.barcode.configuration.BarcodeScannerConfiguration;
import io.scanbot.sdk.ui.view.base.configuration.CameraOrientationMode;
import io.scanbot.sdk.ui.view.base.configuration.OrientationMode;
import io.scanbot.sdk.ui.view.camera.DocumentScannerActivity;
import io.scanbot.sdk.ui.view.camera.configuration.DocumentScannerAccessibilityConfiguration;
import io.scanbot.sdk.ui.view.camera.configuration.DocumentScannerConfiguration;
import io.scanbot.sdk.ui.view.check.CheckRecognizerActivity;
import io.scanbot.sdk.ui.view.check.configuration.CheckRecognizerConfiguration;
import io.scanbot.sdk.ui.view.edit.CroppingActivity;
import io.scanbot.sdk.ui.view.edit.configuration.CroppingAccessibilityConfiguration;
import io.scanbot.sdk.ui.view.edit.configuration.CroppingConfiguration;
import io.scanbot.sdk.ui.view.genericdocument.GenericDocumentRecognizerActivity;
import io.scanbot.sdk.ui.view.genericdocument.configuration.GenericDocumentRecognizerConfiguration;
import io.scanbot.sdk.ui.view.generictext.TextDataScannerActivity;
import io.scanbot.sdk.ui.view.generictext.configuration.TextDataScannerConfiguration;
import io.scanbot.sdk.ui.view.generictext.entity.TextDataScannerStep;
import io.scanbot.sdk.ui.view.generictext.entity.TextDataScannerStepResult;
import io.scanbot.sdk.ui.view.hic.HealthInsuranceCardScannerActivity;
import io.scanbot.sdk.ui.view.licenseplate.LicensePlateScannerActivity;
import io.scanbot.sdk.ui.view.licenseplate.configuration.LicensePlateScannerConfiguration;
import io.scanbot.sdk.ui.view.licenseplate.entity.LicensePlateScannerResult;
import io.scanbot.sdk.ui.view.mrz.MRZScannerActivity;
import io.scanbot.sdk.ui.view.mrz.configuration.MRZScannerConfiguration;
import io.scanbot.sdk.ui.view.hic.configuration.HealthInsuranceCardScannerConfiguration;
import io.scanbot.genericdocument.entity.DocumentProperties;
import io.scanbot.genericdocument.entity.FieldProperties;

import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_BARCODE_SCANNER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_CHECK_RECOGNIZER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_CROPPING;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_DATA_SCANNER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_GENERIC_DOCUMENT_RECOGNIZER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_LP_SCANNER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_DOCUMENT_SCANNER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_MRZ_SCANNER;
import static io.scanbot.sdk.plugin.cordova.ScanbotConstants.REQUEST_SB_EHIC_SCANNER;

/**
 * Scanbot SDK UI Cordova Plugin
 */
public class ScanbotSdkUiPlugin extends ScanbotCordovaPluginBase {

    private static final String LOG_TAG = ScanbotSdkUiPlugin.class.getSimpleName();

    private static final String EXTRAS_JSON_ARGS = "EXTRAS_JSON_ARGS";


    private CallbackContext callbackContext;
    private JSONObject jsonArgs;

    @Override
    protected String getLogTag() {
        return LOG_TAG;
    }


    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        LOG.d(LOG_TAG, "execute: action=" + action + "; callbackId=" + callbackContext.getCallbackId());

        this.jsonArgs = (args.length() > 0 ? args.getJSONObject(0) : new JSONObject());
        debugLog("JSON args: " + jsonArgs.toString());

        // First check if SDK is initialized:
        if (!ScanbotSdkPlugin.isSdkInitialized()) {
            final String errorMsg = "Scanbot SDK is not initialized. Please call the ScanbotSdk.initializeSdk() function first.";
            errorLog(errorMsg);
            callbackContext.error(errorMsg);
            return true;
        }

        this.callbackContext = callbackContext;

        switch (action) {
            case "startDocumentScanner":
                startDocumentScannerActivity();
                break;
            case "startCroppingScreen":
                startCroppingActivity();
                break;
            case "startBarcodeScanner":
                startBarcodeScannerActivity();
                break;
            case "startBatchBarcodeScanner":
                startBatchBarcodeScannerActivity();
                break;
            case "startMrzScanner":
                startMrzScannerActivity();
                break;
            case "startEHICScanner":
                startEHICScannerActivity();
                break;
            case "startLicensePlateScanner":
                startLicensePlateScannerActivity();
                break;
            case "startDataScanner":
                startDataScannerActivity();
                break;
            case "startGenericDocumentRecognizer":
                startGenericDocumentRecognizerActivity();
                break;
            case "startCheckRecognizer":
                startCheckRecognizerActivity();
                break;
            default:
                return false;
        }

        return true;
    }


    /**
     * Called when the Activity is being destroyed (e.g. if a plugin calls out to an
     * external Activity and the OS kills the CordovaActivity in the background).
     * The plugin should save its state in this method only if it is awaiting the
     * result of an external Activity and needs to preserve some information so as
     * to handle that result; onRestoreStateForActivityResult() will only be called
     * if the plugin is the recipient of an Activity result
     *
     * @return Bundle containing the state of the plugin or null if state does not
     * need to be saved
     */
    @Override
    public Bundle onSaveInstanceState() {
        final Bundle state = super.onSaveInstanceState();
        if (this.jsonArgs != null) {
            state.putString(EXTRAS_JSON_ARGS, this.jsonArgs.toString());
        }
        return state;
    }


    /**
     * Called when a plugin is the recipient of an Activity result after the
     * CordovaActivity has been destroyed. The Bundle will be the same as the one
     * the plugin returned in onSaveInstanceState()
     *
     * @param state           Bundle containing the state of the plugin
     * @param callbackContext Replacement Context to return the plugin result to
     */
    @Override
    public void onRestoreStateForActivityResult(final Bundle state, final CallbackContext callbackContext) {
        super.onRestoreStateForActivityResult(state, callbackContext);

        this.callbackContext = callbackContext;

        if (state.containsKey(EXTRAS_JSON_ARGS)) {
            try {
                this.jsonArgs = new JSONObject(state.getString(EXTRAS_JSON_ARGS));
            } catch (final JSONException e) {
                errorLog("Could not restore JSON args", e);
            }
        }
    }


    /**
     * Called when an activity you launched exits, giving you the requestCode you started it with,
     * the resultCode it returned, and any additional data from it.
     *
     * @param requestCode The request code originally supplied to startActivityForResult(),
     *                    allowing you to identify who this result came from.
     * @param resultCode  The integer result code returned by the child activity through its setResult().
     * @param intent      An Intent, which can return result data to the caller (various data can be
     *                    attached to Intent "extras").
     */
    @Override
    public void onActivityResult(final int requestCode, final int resultCode, final Intent intent) {
        debugLog("onActivityResult: requestCode=" + requestCode + ", resultCode=" + resultCode + ", intent=" + intent);

        switch (requestCode) {
            case REQUEST_SB_DOCUMENT_SCANNER:
                this.handleDocumentScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_CROPPING:
                this.handleCroppingResult(intent, resultCode);
                return;
            case REQUEST_SB_BARCODE_SCANNER:
                this.handleBarcodeScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_MRZ_SCANNER:
                this.handleMrzScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_EHIC_SCANNER:
                this.handleEHICScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_LP_SCANNER:
                this.handleLicensePlateScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_DATA_SCANNER:
                this.handleDataScannerResult(intent, resultCode);
                return;
            case REQUEST_SB_GENERIC_DOCUMENT_RECOGNIZER:
                this.handleGenericDocumentRecognizerResult(intent, resultCode);
                return;
            case REQUEST_SB_CHECK_RECOGNIZER:
                this.handleCheckRecognizerResult(intent, resultCode);
                return;
            default:

                break;
        }
    }

    private JSONObject getUiConfigs() throws JSONException {
        // "uiConfigs" is an optional JSON object. If not provided, return an empty JSON object (means use default ui configs)
        return JsonUtils.getJsonObject(jsonArgs, "uiConfigs", new JSONObject());
    }


    /**
     * Starts Scanbot DocumentScanner UI.
     */
    private void startDocumentScannerActivity() {
        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                try {
                    final DocumentScannerConfiguration configuration = new DocumentScannerConfiguration();
                    final JSONObject uiConfigs = getUiConfigs();

                    JSONObject accessibilityJson = null;
                    if (uiConfigs.has("accessibilityConfiguration")) {
                        try {
                            accessibilityJson = uiConfigs.getJSONObject("accessibilityConfiguration");
                        } catch (JSONException ignored) {
                        }
                        uiConfigs.remove("accessibilityConfiguration");
                    }

                    CameraOrientationMode cameraOrientationMode = getCameraOrientationModeFromUiConfigs(uiConfigs);
                    if (cameraOrientationMode != null) {
                        configuration.setOrientationLockMode(cameraOrientationMode);
                    }

                    ObjectMapper.map(uiConfigs, configuration);

                    if (accessibilityJson != null) {
                        final DocumentScannerAccessibilityConfiguration config = JsonUtils.extractDocumentScannerAccessibilityConfiguration(accessibilityJson);
                        configuration.setAccessibilityConfiguration(config);
                    }

                    final Intent intent = DocumentScannerActivity.newIntent(getApplicationContext(), configuration);
                    startScanbotActivityForResult(intent, REQUEST_SB_DOCUMENT_SCANNER);
                } catch (final Exception e) {
                    errorCallback(callbackContext, "Error starting DocumentScanner UI.", e);
                }
            }
        });
    }


    /**
     * Starts Scanbot Cropping UI.
     *
     * @throws JSONException
     */
    private void startCroppingActivity() {
        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                try {
                    final Page page = JsonPage.fromJson(getPageJsonArg(jsonArgs, true)).asSdkPage();
                    final CroppingConfiguration configuration = new CroppingConfiguration(page);

                    final JSONObject uiConfigs = getUiConfigs();

                    JSONObject accessibilityJson = null;
                    if (uiConfigs.has("accessibilityConfiguration")) {
                        try {
                            accessibilityJson = uiConfigs.getJSONObject("accessibilityConfiguration");
                        } catch (JSONException ignored) {
                        }
                        uiConfigs.remove("accessibilityConfiguration");
                    }

                    if (uiConfigs.has("interfaceOrientation")) {
                        final String orientation = uiConfigs.getString("interfaceOrientation");
                        uiConfigs.remove("interfaceOrientation");

                        switch (orientation) {
                            case "PORTRAIT":
                                configuration.setOrientationLockMode(OrientationMode.PORTRAIT);
                                break;
                            case "LANDSCAPE":
                                configuration.setOrientationLockMode(OrientationMode.LANDSCAPE);
                                break;
                        }
                    }

                    if (uiConfigs.has("topAndBottomButtonsSwapped")) {
                        final boolean topAndBottomButtonsSwapped = uiConfigs.getBoolean("topAndBottomButtonsSwapped");
                        configuration.setSwapTopBottomButtons(topAndBottomButtonsSwapped);
                        uiConfigs.remove("topAndBottomButtonsSwapped");
                    }

                    ObjectMapper.map(uiConfigs, configuration);

                    if (accessibilityJson != null) {
                        CroppingAccessibilityConfiguration config = JsonUtils.extractCroppingAccessibilityConfiguration(accessibilityJson);
                        configuration.setAccessibilityConfiguration(config);
                    }

                    final Intent intent = CroppingActivity.newIntent(getApplicationContext(), configuration);
                    startScanbotActivityForResult(intent, REQUEST_SB_CROPPING);
                } catch (final Exception e) {
                    errorCallback(callbackContext, "Error starting Cropping UI.", e);
                }
            }
        });
    }

    /**
     * Starts Scanbot Barcode Scanner UI.
     *
     * @throws JSONException
     */
    private void startBarcodeScannerActivity() {
        try {
            final BarcodeScannerConfiguration configuration = new BarcodeScannerConfiguration();
            final JSONObject uiConfigs = getUiConfigs();
            ObjectMapper.map(uiConfigs, configuration);
            if (uiConfigs.has("barcodeFormats")) {
                ArrayList<BarcodeFormat> nativeBarcodeFormats = getNativeFormats(uiConfigs);
                configuration.setBarcodeFormatsFilter(nativeBarcodeFormats);
            }
            configuration.setEngineMode(JsonUtils.extractEngineMode(uiConfigs));

            try {
                final BarcodeScannerAdditionalConfiguration additionalConfiguration
                        = JsonUtils.extractBarcodeScannerAdditionalConfiguration(uiConfigs);
                if (additionalConfiguration != null) {
                    configuration.setAdditionalDetectionParameters(additionalConfiguration);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Barcode Scanner additional configuration", e);
                return;
            }

            try {
                final ArrayList<BarcodeDocumentFormat> documentFormats = JsonUtils.extractBarcodeDocumentFormats(uiConfigs);
                if (!documentFormats.isEmpty()) {
                    configuration.setAcceptedDocumentFormats(documentFormats);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Accepted Document Format filters", e);
                return;
            }

            try {
                final BarcodeFilter filter = JsonUtils.extractBarcodeFilter(uiConfigs);
                if (filter != null) {
                    configuration.setBarcodeFilter(filter);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Barcode Scanner additional configuration", e);
                return;
            }

            final Intent intent = BarcodeScannerActivity.newIntent(getApplicationContext(), configuration);

            this.cordova.startActivityForResult(this, intent, REQUEST_SB_BARCODE_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting barcode scanner.", e);
        }
    }

    private BarcodeScannerAdditionalConfiguration extractBarcodeScannerAdditionalConfiguration(JSONObject configuration) throws JSONException {
        boolean changed = false;

        boolean gs1DecodingEnabled = BarcodeScannerAdditionalConfig.DEFAULT_GS1_DECODING_ENABLED;
        if (configuration.has("gs1DecodingEnabled")) {
            gs1DecodingEnabled = configuration.getBoolean("gs1DecodingEnabled");
            changed = true;
        }

        int minimumTextLength = BarcodeScannerAdditionalConfig.DEFAULT_MIN_TEXT_LENGTH;
        if (configuration.has("minimumTextLength")) {
            minimumTextLength = configuration.getInt("minimumTextLength");
            changed = true;
        }

        int maximumTextLength = BarcodeScannerAdditionalConfig.DEFAULT_MAX_TEXT_LENGTH;
        if (configuration.has("maximumTextLength")) {
            maximumTextLength = configuration.getInt("maximumTextLength");
            changed = true;
        }

        int minimum1DQuietZoneSize = BarcodeScannerAdditionalConfig.DEFAULT_MIN_1D_QUIET_ZONE_SIZE;
        if (configuration.has("minimum1DBarcodesQuietZone")) {
            minimum1DQuietZoneSize = configuration.getInt("minimum1DBarcodesQuietZone");
            changed = true;
        }

        EnumSet<MSIPlesseyChecksumAlgorithm> msiPlesseyChecksumAlgorithms =
                BarcodeScannerAdditionalConfig.Companion.getDEFAULT_MSI_PLESSEY_CHECKSUM_ALGORITHMS();
        if (configuration.has("msiPlesseyChecksumAlgorithm")) {
            msiPlesseyChecksumAlgorithms.clear();
            String algorithm = configuration.getString("msiPlesseyChecksumAlgorithm");
            msiPlesseyChecksumAlgorithms.add(MSIPlesseyChecksumAlgorithm.valueOf(algorithm));
            changed = true;
        }

        boolean stripCheckDigits = BarcodeScannerAdditionalConfig.DEFAULT_STRIP_CHECK_DIGITS;
        if (configuration.has("stripCheckDigits")) {
            stripCheckDigits = configuration.getBoolean("stripCheckDigits");
            changed = true;
        }

        boolean lowPowerMode = BarcodeScannerAdditionalConfig.DEFAULT_LOW_POWER_MODE;
        if (configuration.has("lowPowerMode")) {
            lowPowerMode = configuration.getBoolean("lowPowerMode");
            changed = true;
        }

        BarcodeDensity codeDensity = BarcodeScannerAdditionalConfig.getDEFAULT_CODE_DENSITY();
        if (configuration.has("codeDensity")) {
            String barcodeDensity = configuration.getString("codeDensity");
            codeDensity = BarcodeDensity.valueOf(barcodeDensity);
            changed = true;
        }

        return changed ? new BarcodeScannerAdditionalConfiguration(
                minimumTextLength,
                maximumTextLength,
                minimum1DQuietZoneSize,
                gs1DecodingEnabled,
                msiPlesseyChecksumAlgorithms,
                stripCheckDigits,
                lowPowerMode,
                codeDensity) : null;
    }

    private static EngineMode extractEngineMode(JSONObject configuration) throws JSONException {
        if (!configuration.has("engineMode")) {
            return EngineMode.NextGen;
        }

        String mode = configuration.getString("engineMode");
        if ("LEGACY".equals(mode)) {
            return EngineMode.LegacyFast;
        }
        return EngineMode.NextGen;
    }

    private void startBatchBarcodeScannerActivity() {
        try {
            final BatchBarcodeScannerConfiguration configuration = new BatchBarcodeScannerConfiguration();
            final JSONObject uiConfigs = getUiConfigs();
            ObjectMapper.map(uiConfigs, configuration);

            // • Barcode Format Filters
            try {
                final ArrayList<BarcodeFormat> barcodeFormats = JsonUtils.extractBarcodeFormats(uiConfigs);
                if (!barcodeFormats.isEmpty()) {
                    configuration.setBarcodeFormatsFilter(barcodeFormats);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Barcode Scanner format filters");
                return;
            }

            configuration.setEngineMode(JsonUtils.extractEngineMode(uiConfigs));

            // • Document Format Filters
            try {
                final ArrayList<BarcodeDocumentFormat> documentFormats = JsonUtils.extractBarcodeDocumentFormats(uiConfigs);
                if (!documentFormats.isEmpty()) {
                    configuration.setAcceptedDocumentFormats(documentFormats);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Accepted Document Format filters", e);
                return;
            }

            // • Additional Configuration
            try {
                final BarcodeScannerAdditionalConfiguration additionalConfiguration
                        = JsonUtils.extractBarcodeScannerAdditionalConfiguration(uiConfigs);
                if (additionalConfiguration != null) {
                    configuration.setAdditionalDetectionParameters(additionalConfiguration);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Barcode Scanner additional configuration", e);
                return;
            }

            try {
                final BarcodeFilter filter = JsonUtils.extractBarcodeFilter(uiConfigs);
                if (filter != null) {
                    configuration.setBarcodeFilter(filter);
                }
            } catch (JSONException e) {
                debugLog(e.toString());
                errorCallback(callbackContext, "Cannot parse Barcode Scanner additional configuration", e);
                return;
            }

            final Intent intent = BatchBarcodeScannerActivity.newIntent(getApplicationContext(), configuration, null);
            this.cordova.startActivityForResult(this, intent, REQUEST_SB_BARCODE_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting barcode scanner.", e);
        }
    }

    private ArrayList<BarcodeFormat> getNativeFormats(JSONObject uiConfigs) throws JSONException {
        JSONArray barcodeFormats = uiConfigs.getJSONArray("barcodeFormats");
        final ArrayList<BarcodeFormat> nativeBarcodeFormats = new ArrayList<>();

        for (int i = 0; i < barcodeFormats.length(); ++i) {
            nativeBarcodeFormats.add(BarcodeFormat.valueOf(barcodeFormats.getString(i)));
        }
        if (nativeBarcodeFormats.size() == 0) {
            nativeBarcodeFormats.addAll(BarcodeFormat.ALL_CODES);
        }
        return nativeBarcodeFormats;
    }

    private void startMrzScannerActivity() {
        try {
            final MRZScannerConfiguration configuration = new MRZScannerConfiguration();
            ObjectMapper.map(getUiConfigs(), configuration);
            final Intent intent = MRZScannerActivity.newIntent(getApplicationContext(), configuration);

            this.cordova.startActivityForResult(this, intent, REQUEST_SB_MRZ_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting MRZ scanner.", e);
        }
    }

    private void startEHICScannerActivity() {
        try {
            final HealthInsuranceCardScannerConfiguration configuration = new HealthInsuranceCardScannerConfiguration();
            ObjectMapper.map(getUiConfigs(), configuration);

            final Intent intent = HealthInsuranceCardScannerActivity.newIntent(getApplicationContext(), configuration);

            this.cordova.startActivityForResult(this, intent, REQUEST_SB_EHIC_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting EHIC scanner.", e);
        }
    }

    private void handleDocumentScannerResult(final Intent intent, final int resultCode) {
        final JSONArray pagesJsonArray = new JSONArray();

        try {
            DocumentScannerActivity.Result result = DocumentScannerActivity.extractResult(resultCode, intent);

            if (result.getResultOk()) {
                List<Page> snappedPages = result.getResult();
                final PageFileStorage pageFileStorage = this.sdkWrapper.pageFileStorage();
                for (final Parcelable p : snappedPages) {
                    final JsonPage jsonPage = JsonPage.fromSdkPage((Page) p, pageFileStorage);
                    pagesJsonArray.put(jsonPage.asJsonObj());
                }
            }

            successCallback(callbackContext, !result.getResultOk(), new JsonArgs()
                    .put("pages", pagesJsonArray)
            );
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform result from DocumentScannerActivity to JSON.", e);
        }
    }


    private void handleCroppingResult(final Intent intent, final int resultCode) {
        final JSONObject pageJsonObj;

        CroppingActivity.Result result = CroppingActivity.extractResult(resultCode, intent);

        if (result.getResultOk()) {
            final Page page = result.getResult();
            pageJsonObj = JsonPage.fromSdkPage(page, this.sdkWrapper.pageFileStorage()).asJsonObj();
        } else {
            pageJsonObj = null;
        }

        successCallback(this.callbackContext, !result.getResultOk(), "page", pageJsonObj);
    }


    private void handleBarcodeScannerResult(final Intent intent, final int resultCode) {
        try {
            final JsonArgs barcodeResultJsonObj = new JsonArgs();

            BarcodeScannerActivity.Result result = BarcodeScannerActivity.extractResult(resultCode, intent);

            if (!result.getResultOk()) {
                barcodeResultJsonObj.put("canceledDueToTimeout", result.isAutoCancelledByTimeout());
            } else {
                final BarcodeScanningResult barcodeResult = result.getResult();

                final String imageFilePath = intent.getStringExtra(BarcodeScannerActivity.SCANNED_BARCODE_IMAGE_PATH_EXTRA);
                final String previewFilePath = intent.getStringExtra(BarcodeScannerActivity.SCANNED_BARCODE_PREVIEW_FRAME_PATH_EXTRA);

                final JSONArray serializedBarcodes = new JSONArray();
                if (barcodeResult != null) {
                    for (final BarcodeItem item : barcodeResult.getBarcodeItems()) {
                        final JSONObject child = new JSONObject();
                        try {
                            child.put("text", item.getText());
                            child.put("type", item.getBarcodeFormat().toString());
                            child.put("textWithExtension", item.getTextWithExtension().toString());
                            child.put("rawBytes", ScanbotSdkPlugin.jsonFromRawBytes(item.getRawBytes()));
                            serializedBarcodes.put(child);
                        } catch (JSONException e) {
                            debugLog(e.toString());
                        }
                    }
                }

                final Uri imageFileUri;
                if (imageFilePath != null && !"".equals(imageFilePath)) {
                    imageFileUri = Uri.fromFile(new File(imageFilePath));
                } else if (previewFilePath != null && !"".equals(previewFilePath)) {
                    imageFileUri = Uri.fromFile(new File(previewFilePath));
                } else {
                    imageFileUri = null;
                }

                barcodeResultJsonObj
                        .put("barcodes", serializedBarcodes)
                        .put("imageFileUri", (imageFileUri != null ? imageFileUri.toString() : null));
            }

            successCallback(this.callbackContext, !result.getResultOk(), barcodeResultJsonObj);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform result from BarcodeScannerActivity to JSON.", e);
        }
    }


    private void handleMrzScannerResult(final Intent intent, final int resultCode) {
        final JSONArray fieldsArray = new JSONArray();

        try {
            final JSONObject mrzResult;
            MRZScannerActivity.Result result = MRZScannerActivity.extractResult(resultCode, intent);

            if (result.getResultOk()) {
                final MRZRecognitionResult mrzRecognitionResult = result.getResult();

                for (final MRZField field : mrzRecognitionResult.fields) {
                    final JSONObject jsonField = new JsonArgs()
                            .put("name", field.name.name())
                            .put("value", field.value)
                            .put("confidence", field.averageRecognitionConfidence)
                            .jsonObj();
                    fieldsArray.put(jsonField);
                }

                mrzResult = new JsonArgs()
                        .put("checkDigitsCount", mrzRecognitionResult.checkDigitsCount)
                        .put("validCheckDigitsCount", mrzRecognitionResult.validCheckDigitsCount)
                        .put("fields", fieldsArray)
                        .jsonObj();
            } else {
                mrzResult = null;
            }

            successCallback(callbackContext, !result.getResultOk(), new JsonArgs()
                    .put("mrzResult", mrzResult)
            );
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform MRZRecognitionResult to JSON.", e);
        }
    }

    private void handleEHICScannerResult(final Intent intent, final int resultCode) {
        final JSONArray fieldsArray = new JSONArray();

        try {
            final JSONObject json;

            HealthInsuranceCardScannerActivity.Result result = HealthInsuranceCardScannerActivity.extractResult(resultCode, intent);

            if (result.getResultOk()) {
                final HealthInsuranceCardRecognitionResult recognitionResult = result.getResult();
                for (final HealthInsuranceCardField field : recognitionResult.fields) {
                    final JSONObject jsonField = new JsonArgs()
                            .put("type", field.type.name())
                            .put("value", field.value)
                            .put("confidence", field.confidence)
                            .jsonObj();
                    fieldsArray.put(jsonField);
                }

                json = new JsonArgs().put("fields", fieldsArray).jsonObj();
            } else {
                json = null;
            }

            successCallback(callbackContext, !result.getResultOk(), new JsonArgs()
                    .put("ehicResult", json)
            );
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform EHICRecognitionResult to JSON.", e);
        }
    }

    private void startLicensePlateScannerActivity() {
        try {
            final JSONObject jsonConfigs = getUiConfigs();

            final LicensePlateScannerConfiguration scannerConfiguration = new LicensePlateScannerConfiguration();
            ObjectMapper.map(jsonConfigs, scannerConfiguration);

            if (jsonConfigs.has("detectorMode") && "CLASSIC".equals(jsonConfigs.get("detectorMode"))) {
                scannerConfiguration.setScanStrategy(LicensePlateScanStrategy.LicensePlateClassic);
            }

            final boolean confirmationDialogConfirmButtonFilled =
                    jsonConfigs.has("confirmationDialogConfirmButtonFilled")
                            && jsonConfigs.getBoolean("confirmationDialogConfirmButtonFilled");
            scannerConfiguration.setConfirmationDialogConfirmButtonFilled(confirmationDialogConfirmButtonFilled);

            final Intent intent = LicensePlateScannerActivity.newIntent(getApplicationContext(), scannerConfiguration);
            this.cordova.startActivityForResult(this, intent, REQUEST_SB_LP_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting License Plate Scanner.", e);
        }
    }

    private void handleLicensePlateScannerResult(final Intent intent, final int resultCode) {
        try {
            JSONObject licensePlateResult = null;
            LicensePlateScannerActivity.Result result = LicensePlateScannerActivity.extractResult(resultCode, intent);

            if (result.getResultOk()) {
                final LicensePlateScannerResult scanningResult = result.getResult();
                if (scanningResult != null) {
                    licensePlateResult = new JsonArgs()
                            .put("rawText", scanningResult.getRawText())
                            .put("confidence", scanningResult.getConfidence())
                            .put("countryCode", scanningResult.getCountryCode())
                            .put("licensePlate", scanningResult.getLicensePlate())
                            .jsonObj();
                }
            }
            successCallback(callbackContext, !result.getResultOk(), "licensePlateResult", licensePlateResult);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform License Plate Scanner result to JSON.", e);
        }
    }

    private void startDataScannerActivity() {
        try {
            final JSONObject uiConfigs = getUiConfigs();

            final JSONObject stepConfigs = JsonUtils.getJsonObject(jsonArgs, "scannerStep", null);
            if (stepConfigs == null) {
                errorCallback(callbackContext, "Missing required argument 'scannerStep'");
                return;
            }

            final TextDataScannerConfiguration scannerConfiguration = new TextDataScannerConfiguration();
            ObjectMapper.map(uiConfigs, scannerConfiguration);

            final String guidanceText = JsonUtils.getJsonArg(stepConfigs, "guidanceText", "");
            final String pattern = JsonUtils.getJsonArg(stepConfigs, "pattern", null);
            final boolean shouldMatchSubstring = JsonUtils.getJsonArg(stepConfigs, "shouldMatchSubstring", false);
            final double preferredZoom = JsonUtils.getJsonArg(stepConfigs, "preferredZoom", 1.4f);
            final JSONObject jsonAspectRatio = JsonUtils.getJsonObject(stepConfigs, "aspectRatio", new JSONObject());

            final FinderAspectRatio aspectRatio = new FinderAspectRatio(
                    JsonUtils.getJsonArg(jsonAspectRatio, "width", 4.0),
                    JsonUtils.getJsonArg(jsonAspectRatio, "height", 1.0));
            final double unzoomedFinderHeight = JsonUtils.getJsonArg(stepConfigs, "unzoomedFinderHeight", -1.0f);

            final HashSet<Character> allowedSymbolsSet = new HashSet<>();
            final String allowedSymbols = JsonUtils.getJsonArg(stepConfigs, "allowedSymbols", "");
            for (final char c : allowedSymbols.toCharArray()) {
                allowedSymbolsSet.add(c);
            }

            final TextFilterStrategy textFilterStrategy = (stepConfigs.has("textFilterStrategy")
                    && "LC_DOT_MATRIX_DISPLAY".equals(stepConfigs.get("textFilterStrategy"))) ?
                    TextFilterStrategy.LcdDotMatrixDisplay : TextFilterStrategy.Document;

            int significantShakeDelay = -1;
            if (stepConfigs.has("significantShakeDelay")) {
                significantShakeDelay = stepConfigs.getInt("significantShakeDelay");
            }

            final TextDataScannerStep step = new TextDataScannerStep(
                    UUID.randomUUID().toString(),
                    "Scan",
                    guidanceText,
                    pattern,
                    shouldMatchSubstring,
                    null,
                    null,
                    (float) preferredZoom,
                    aspectRatio,
                    (float) unzoomedFinderHeight,
                    allowedSymbolsSet,
                    textFilterStrategy,
                    significantShakeDelay);

            final Intent intent = TextDataScannerActivity.newIntent(getApplicationContext(), scannerConfiguration, step);
            this.cordova.startActivityForResult(this, intent, REQUEST_SB_DATA_SCANNER);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Error starting TextDataScannerActivity.", e);
        }
    }

    private void startGenericDocumentRecognizerActivity() {
        try {
            final JSONObject uiConfigs = getUiConfigs();
            final GenericDocumentRecognizerConfiguration config = new GenericDocumentRecognizerConfiguration();

            ObjectMapper.map(uiConfigs, config);

            CameraOrientationMode cameraOrientationMode = getCameraOrientationModeFromUiConfigs(uiConfigs);
            if (cameraOrientationMode != null) {
                config.setOrientationLockMode(cameraOrientationMode);
            }

            // We have to map the acceptedDocumentTypes manually, because the enum keys don't match
            ArrayList<RootDocumentType> documentTypes = JsonUtils.extractAcceptedDocumentTypes(uiConfigs);
            if (!documentTypes.isEmpty()) {
                config.setAcceptedDocumentTypes(documentTypes);
            }

            // Maps the field titles (eg. First Name, Last Name, Country Code ...)
            final HashMap<String, FieldProperties> fields = extractGenericDocumentRecognizerFieldProperties(uiConfigs, documentTypes);
            if (!fields.isEmpty()) {
                config.setFieldsDisplayConfiguration(fields);
            }

            // Maps the document titles (eg. ID Card (Back), ID Card(Front), German Passport ...)
            final HashMap<String, DocumentProperties> documentTitleProperties = extractGenericDocumentRecognizerTitleProperties(uiConfigs, documentTypes);
            if (!documentTitleProperties.isEmpty()) {
                config.setDocumentDisplayConfiguration(documentTitleProperties);
            }

            // Inconsistency: on iOS 'submitButtonTitle' has been renamed to 'viewResultsButtonTitle'
            if (uiConfigs.has("viewResultsButtonTitle")) {
                final String text = uiConfigs.getString("viewResultsButtonTitle");
                if (text != null) {
                    config.setSubmitButtonTitle(text);
                }
            }

            final Intent intent = GenericDocumentRecognizerActivity.newIntent(getApplicationContext(), config);
            this.cordova.startActivityForResult(this, intent, REQUEST_SB_GENERIC_DOCUMENT_RECOGNIZER);
        } catch (JSONException e) {
            debugLog(e.toString());
            errorCallback(callbackContext, "Cannot parse Accepted Document Type filters", e);
        } catch (Exception e) {
            debugLog(e.toString());
            errorCallback(callbackContext, "Error starting Generic Document Recognizer Activity.", e);
        }
    }

    private void startCheckRecognizerActivity() {
        try {
            final JSONObject uiConfigs = getUiConfigs();
            final CheckRecognizerConfiguration config = new CheckRecognizerConfiguration();

            ObjectMapper.map(uiConfigs, config);

            CameraOrientationMode cameraOrientationMode = getCameraOrientationModeFromUiConfigs(uiConfigs);
            if (cameraOrientationMode != null) {
                config.setOrientationLockMode(cameraOrientationMode);
            }

            config.setCameraPreviewMode(CameraPreviewMode.FILL_IN);

            // We have to map the acceptedDocumentTypes manually, because the enum keys don't match
            ArrayList<io.scanbot.check.entity.RootDocumentType> checkStandards = JsonUtils.extractAcceptedCheckStandards(uiConfigs);
            if (!checkStandards.isEmpty()) {
                config.setAcceptedCheckStandards(checkStandards);
            }

            final Intent intent = CheckRecognizerActivity.newIntent(getApplicationContext(), config);
            this.cordova.startActivityForResult(this, intent, REQUEST_SB_CHECK_RECOGNIZER);
        } catch (JSONException e) {
            errorCallback(callbackContext, "Cannot parse Check Recognizer configurations.", e);
        } catch (Exception e) {
            errorCallback(callbackContext, "Error starting Check Recognizer Activity.", e);
        }
    }

    private void handleDataScannerResult(final Intent intent, final int resultCode) {
        try {
            JSONObject dataResult = null;
            TextDataScannerActivity.Result result = TextDataScannerActivity.extractResult(resultCode, intent);

            if (result.getResultOk()) {
                final TextDataScannerStepResult stepResult = result.getResult().get(0);

                dataResult = new JsonArgs()
                        .put("textValue", stepResult.getText())
                        .put("confidence", stepResult.getConfidence())
                        .jsonObj();
            }
            successCallback(callbackContext, !result.getResultOk(), "dataResult", dataResult);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform Text Data Scanner result to JSON.", e);
        }
    }

    private void handleGenericDocumentRecognizerResult(final Intent intent, final int resultCode) {
        try {
            GenericDocumentRecognizerActivity.Result result = GenericDocumentRecognizerActivity.extractResult(resultCode, intent);

            final List<ResultWrapper<GenericDocument>> resultWrappers = result.getResult();//intent.getParcelableArrayListExtra(GenericDocumentRecognizerActivity.EXTRACTED_FIELDS_EXTRA);
            final JsonArgs data = extractGenericDocumentRecognizerResultFromResultWrappers(resultWrappers);

            data.put("status", !result.getResultOk() ? "CANCELED" : "OK");
            successCallback(callbackContext, !result.getResultOk(), data);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform Generic Document Recognizer result to JSON.", e);
        }
    }

    private void handleCheckRecognizerResult(final Intent intent, final int resultCode) {
        try {
            CheckRecognizerActivity.Result result = CheckRecognizerActivity.extractResult(resultCode, intent);

            JsonArgs data = extractCheckRecognizerResultFromCheckResult(result);

            successCallback(callbackContext, !result.getResultOk(), data);
        } catch (final Exception e) {
            errorCallback(callbackContext, "Could not transform Check Recognizer result to JSON.", e);
        }
    }

    private JsonArgs extractGenericDocumentRecognizerResultFromResultWrappers(List<ResultWrapper<GenericDocument>> resultWrappers) {
        JsonArgs outArgs = new JsonArgs();
        if (resultWrappers == null) {
            return outArgs;
        }

        String documentType = "";
        JsonArgs fields = new JsonArgs();
        final List<GenericDocument> documents = extractDocumentsFromResultWrappers(resultWrappers);

        putGdrFieldFromDocuments(documents, fields, "surname", "Surname");
        putGdrFieldFromDocuments(documents, fields, "givenNames", "GivenNames");
        putGdrFieldFromDocuments(documents, fields, "nationality", "Nationality");
        putGdrFieldFromDocuments(documents, fields, "birthDate", "BirthDate");
        putGdrFieldFromDocuments(documents, fields, "rawMrz", "RawMRZ");
        putGdrFieldFromDocuments(documents, fields, "expiryDate", "ExpiryDate");
        putGdrFieldFromDocuments(documents, fields, "birthplace", "Birthplace");
        putGdrFieldFromDocuments(documents, fields, "issueDate", "IssueDate");
        putGdrFieldFromDocuments(documents, fields, "issuingAuthority", "IssuingAuthority");
        putGdrFieldFromDocuments(documents, fields, "address", "Address");
        putGdrFieldFromDocuments(documents, fields, "eyeColor", "EyeColor");
        putGdrFieldFromDocuments(documents, fields, "height", "Height");
        putGdrFieldFromDocuments(documents, fields, "pin", "PIN");
        putGdrFieldFromDocuments(documents, fields, "pseudonym", "Pseudonym");
        putGdrFieldFromDocuments(documents, fields, "countryCode", "CountryCode");
        putGdrFieldFromDocuments(documents, fields, "gender", "Gender");
        putGdrFieldFromDocuments(documents, fields, "maidenName", "MaidenName");
        putGdrFieldFromDocuments(documents, fields, "passportType", "PassportType");
        putGdrFieldFromDocuments(documents, fields, "id", "ID");
        putGdrFieldFromDocuments(documents, fields, "licenseCategories", "LicenseCategories");
        putGdrFieldFromDocuments(documents, fields, "restrictions", "Restrictions");
        putGdrFieldFromDocuments(documents, fields, "validFrom", "ValidFrom");
        putGdrFieldFromDocuments(documents, fields, "validUntil", "ValidUntil");
        putImageInGdrJsonMapFromDocuments(documents, fields, "photoImageUri", "Photo");
        putImageInGdrJsonMapFromDocuments(documents, fields, "signatureImageUri", "Signature");

        for (GenericDocument document : documents) {
            GenericDocumentWrapper wrap = GenericDocumentLibrary.INSTANCE.wrap(document);

            if (wrap instanceof DePassport) {
                JsonArgs mrzFields = new JsonArgs();
                DePassport passport = (DePassport) wrap;

                MRZ mrz = passport.getMrz();
                putGdrFieldFromTextFieldWrapper(mrzFields, "birthDate", mrz.getBirthDate());
                putGdrFieldFromTextFieldWrapper(mrzFields, "documentNumber", mrz.getDocumentNumber());
                putGdrFieldFromTextFieldWrapper(mrzFields, "expiryDate", mrz.getExpiryDate());
                putGdrFieldFromTextFieldWrapper(mrzFields, "gender", mrz.getGender());
                putGdrFieldFromTextFieldWrapper(mrzFields, "givenNames", mrz.getGivenNames());
                putGdrFieldFromTextFieldWrapper(mrzFields, "issuingAuthority", mrz.getIssuingAuthority());
                putGdrFieldFromTextFieldWrapper(mrzFields, "nationality", mrz.getNationality());
                putGdrFieldFromTextFieldWrapper(mrzFields, "optional1", mrz.getOptional1());
                putGdrFieldFromTextFieldWrapper(mrzFields, "optional2", mrz.getOptional2());
                putGdrFieldFromTextFieldWrapper(mrzFields, "surname", mrz.getSurname());
                putGdrFieldFromTextFieldWrapper(mrzFields, "travelDocType", mrz.getTravelDocType());
                putGdrFieldFromTextFieldWrapper(mrzFields, "travelDocTypeVariant", mrz.getTravelDocTypeVariant());

                fields.put("mrz", mrzFields.jsonObj());
            } else if (wrap instanceof DeDriverLicenseBack) {
                JsonArgs driverLicenseCategories = new JsonArgs();

                DeDriverLicenseBack driverLicenseBack = (DeDriverLicenseBack) wrap;
                DeDriverLicenseBack.Categories categories = driverLicenseBack.getCategories();

                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "a", categories.getA());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "a1", categories.getA1());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "a2", categories.getA2());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "b", categories.getB());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "b1", categories.getB1());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "be", categories.getBe());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "c", categories.getC());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "c1", categories.getC1());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "c1e", categories.getC1e());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "ce", categories.getCe());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "d", categories.getD());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "d1", categories.getD1());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "d1e", categories.getD1e());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "de", categories.getDe());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "l", categories.getL());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "m", categories.getM());
                putGdrFieldFromDriverLicenseCategory(driverLicenseCategories, "t", categories.getT());

                fields.put("categories", driverLicenseCategories.jsonObj());
            }

            documentType = getDocumentTypeFromGenericDocumentWrapper(wrap);
        }

        outArgs.put("documentType", documentType);
        outArgs.put("fields", fields.jsonObj());

        return outArgs;
    }

    private static String getDocumentTypeFromGenericDocumentWrapper(GenericDocumentWrapper wrap) {
        String documentType = "";

        if (wrap instanceof DePassport) {
            documentType = "DePassport";
        } else if (wrap instanceof DeDriverLicenseBack || wrap instanceof DeDriverLicenseFront) {
            documentType = "DeDriverLicense";
        } else if (wrap instanceof DeIdCardBack || wrap instanceof DeIdCardFront) {
            documentType = "DeIdCard";
        }

        return documentType;
    }

    private JsonArgs extractCheckRecognizerResultFromCheckResult(CheckRecognizerActivity.Result checkResult) {
        JsonArgs outArgs = new JsonArgs();

        if (!checkResult.getResultOk()) {
            outArgs.put("status", "CANCELED");
        } else {
            final ResultWrapper<CheckRecognizerResult> resultWrapper = checkResult.getResult();

            if (resultWrapper == null) {
                outArgs.put("status", "FAIL");
            } else {

                final ResultRepository<CheckRecognizerResult> resultRepository = sdkWrapper.sdk().resultRepositoryForClass(resultWrapper.getClazz());
                final CheckRecognizerResult check = resultRepository.getResultAndErase(resultWrapper.getResultId());

                if (check != null) {
                    GenericDocument genericCheck = check.getCheck();

                    if (genericCheck != null) {
                        JsonArgs fields = new JsonArgs();

                        String checkType = genericCheck.getType().getName();
                        CheckRecognizerStatus status = check.getStatus();

                        try {
                            Bitmap photo = check.getCroppedImage();
                            if (photo != null) {
                                final Uri imageUri = sdkWrapper.storeImage(photo, ImageUtils.JPEG_QUALITY);
                                outArgs.put("imageUri", imageUri.toString());
                            }
                        } catch (Exception e) {
                            debugLog("Error saving check image:" + e.toString());
                        }

                        for (Field field : genericCheck.getFields()) {
                            JsonArgs fieldArgs = new JsonArgs();

                            JsonArgs value = getResultMapFromOcrResult(field.getValue());
                            fieldArgs.put("value", value);

                            fieldArgs.put("validationStatus", field.getValidationStatus().toString()); //     Invalid, Valid

                            final String normalizedCheckFieldName = JsonUtils.getNormalizedCheckFieldName(field.getType());
                            fields.put(normalizedCheckFieldName, fieldArgs);
                        }

                        final String resultStatus = status == CheckRecognizerStatus.SUCCESS ? "SUCCESS" : "FAIL";

                        outArgs.put("fields", fields.jsonObj());
                        outArgs.put("checkType", checkType);
                        outArgs.put("status", resultStatus);
                    } else {
                        outArgs.put("status", "FAIL");
                    }
                } else {
                    outArgs.put("status", "FAIL");
                }
            }
        }

        return outArgs;
    }

    private static void addFieldPropertyFromMap(
            final HashMap<String, FieldProperties> fields,
            final JSONObject map,
            final String key,
            final String fieldName
    ) {
        final String value = JsonUtils.getStringOrNull(map, key);
        if (value == null) {
            return;
        }
        fields.put(fieldName, new FieldProperties(value, FieldProperties.DisplayState.AlwaysVisible));
    }

    private static HashMap<String, DocumentProperties> extractGenericDocumentRecognizerTitleProperties(
            JSONObject uiConfig,
            List<RootDocumentType> documentTypes
    ) {

        final HashMap<String, DocumentProperties> properties = new HashMap<>();
        JSONObject configuration = null;

        try {
            configuration = JsonUtils.getJsonObject(uiConfig, "detailsFieldConfiguration", null);
        } catch (JSONException e) {
            // ignore
        }

        if (configuration != null) {
            if (configuration.has("dePassportDocumentTitle") && documentTypes.contains(RootDocumentType.DePassport)) {
                final String text = JsonUtils.getStringOrNull(configuration, "dePassportDocumentTitle");
                if (text != null) {
                    properties.put(DePassport.DOCUMENT_NORMALIZED_TYPE, new DocumentProperties(text));
                }
            }

            if (configuration.has("deIdCardBackDocumentTitle") && documentTypes.contains(RootDocumentType.DeIdCardBack)) {
                final String text = JsonUtils.getStringOrNull(configuration, "deIdCardBackDocumentTitle");
                if (text != null) {
                    properties.put(DeIdCardBack.DOCUMENT_NORMALIZED_TYPE, new DocumentProperties(text));
                }
            }

            if (configuration.has("deIdCardFrontDocumentTitle") && documentTypes.contains(RootDocumentType.DeIdCardFront)) {
                final String text = JsonUtils.getStringOrNull(configuration, "deIdCardFrontDocumentTitle");
                if (text != null) {
                    properties.put(DeIdCardFront.DOCUMENT_NORMALIZED_TYPE, new DocumentProperties(text));
                }
            }

            if (configuration.has("deDriverLicenseBackDocumentTitle") && documentTypes.contains(RootDocumentType.DeDriverLicenseBack)) {
                final String text = JsonUtils.getStringOrNull(configuration, "deDriverLicenseBackDocumentTitle");
                if (text != null) {
                    properties.put(DeDriverLicenseBack.DOCUMENT_NORMALIZED_TYPE, new DocumentProperties(text));
                }
            }

            if (configuration.has("deDriverLicenseFrontDocumentTitle") && documentTypes.contains(RootDocumentType.DeDriverLicenseFront)) {
                final String text = JsonUtils.getStringOrNull(configuration, "deDriverLicenseFrontDocumentTitle");
                if (text != null) {
                    properties.put(DeDriverLicenseFront.DOCUMENT_NORMALIZED_TYPE, new DocumentProperties(text));
                }
            }
        }

        return properties;
    }

    private static HashMap<String, FieldProperties> extractGenericDocumentRecognizerFieldProperties(
            JSONObject uiConfig,
            List<RootDocumentType> documentTypes
    ) {
        final HashMap<String, FieldProperties> fields = new HashMap<String, FieldProperties>();
        JSONObject configuration = null;

        try {
            configuration = JsonUtils.getJsonObject(uiConfig, "detailsFieldConfiguration", null);
        } catch (JSONException e) {
            // ignore
        }

        if (configuration != null) {
            final HashMap<String, String> deIdCardBackFields = new HashMap<String, String>() {{
                put("fieldAddressTitle", DeIdCardBack.NormalizedFieldNames.ADDRESS);
                put("fieldEyeColorTitle", DeIdCardBack.NormalizedFieldNames.EYE_COLOR);
                put("fieldHeightTitle", DeIdCardBack.NormalizedFieldNames.HEIGHT);
                put("fieldIssueDateTitle", DeIdCardBack.NormalizedFieldNames.ISSUE_DATE);
                put("fieldIssuingAuthorityTitle", DeIdCardBack.NormalizedFieldNames.ISSUING_AUTHORITY);
                put("fieldRawMrzTitle", DeIdCardBack.NormalizedFieldNames.RAW_MRZ);
                put("fieldPseudonymTitle", DeIdCardBack.NormalizedFieldNames.PSEUDONYM);
            }};

            final HashMap<String, String> deIdCardFrontFields = new HashMap<String, String>() {{
                put("fieldBirthDateTitle", DeIdCardFront.NormalizedFieldNames.BIRTH_DATE);
                put("fieldBirthPlaceTitle", DeIdCardFront.NormalizedFieldNames.BIRTHPLACE);
                put("fieldExpiryDateTitle", DeIdCardFront.NormalizedFieldNames.EXPIRY_DATE);
                put("fieldGivenNamesTitle", DeIdCardFront.NormalizedFieldNames.GIVEN_NAMES);
                put("fieldIdTitle", DeIdCardFront.NormalizedFieldNames.ID);
                put("fieldMaidenNameTitle", DeIdCardFront.NormalizedFieldNames.MAIDEN_NAME);
                put("fieldNationalityTitle", DeIdCardFront.NormalizedFieldNames.NATIONALITY);
                put("fieldPinTitle", DeIdCardFront.NormalizedFieldNames.PIN);
                put("fieldPhotoTitle", DeIdCardFront.NormalizedFieldNames.PHOTO);
                put("fieldSignatureTitle", DeIdCardFront.NormalizedFieldNames.SIGNATURE);
                put("fieldSurnameTitle", DeIdCardFront.NormalizedFieldNames.SURNAME);
            }};

            final HashMap<String, String> dePassportFields = new HashMap<String, String>() {{
                put("fieldBirthDateTitle", DePassport.NormalizedFieldNames.BIRTH_DATE);
                put("fieldBirthPlaceTitle", DePassport.NormalizedFieldNames.BIRTHPLACE);
                put("fieldCountryCodeTitle", DePassport.NormalizedFieldNames.COUNTRY_CODE);
                put("fieldExpiryDateTitle", DePassport.NormalizedFieldNames.EXPIRY_DATE);
                put("fieldGenderTitle", DePassport.NormalizedFieldNames.GENDER);
                put("fieldGivenNamesTitle", DePassport.NormalizedFieldNames.GIVEN_NAMES);
                put("fieldIdTitle", DePassport.NormalizedFieldNames.ID);
                put("fieldIssueDateTitle", DePassport.NormalizedFieldNames.ISSUE_DATE);
                put("fieldIssuingAuthorityTitle", DePassport.NormalizedFieldNames.ISSUING_AUTHORITY);
                put("fieldMaidenNameTitle", DePassport.NormalizedFieldNames.MAIDEN_NAME);
                put("fieldNationalityTitle", DePassport.NormalizedFieldNames.NATIONALITY);
                put("fieldPassportTypeTitle", DePassport.NormalizedFieldNames.PASSPORT_TYPE);
                put("fieldPhotoTitle", DePassport.NormalizedFieldNames.PHOTO);
                put("fieldRawMrzTitle", DePassport.NormalizedFieldNames.RAW_MRZ);
                put("fieldSignatureTitle", DePassport.NormalizedFieldNames.SIGNATURE);
                put("fieldSurnameTitle", DePassport.NormalizedFieldNames.SURNAME);
            }};

            final HashMap<String, String> deDriverLicenseBackFields = new HashMap<String, String>() {{
                put("fieldRestrictionsTitle", DeDriverLicenseBack.NormalizedFieldNames.RESTRICTIONS);
            }};

            final HashMap<String, String> deDriverLicenseFrontFields = new HashMap<String, String>() {{
                put("fieldBirthDateTitle", DeDriverLicenseFront.NormalizedFieldNames.BIRTH_DATE);
                put("fieldBirthPlaceTitle", DeDriverLicenseFront.NormalizedFieldNames.BIRTHPLACE);
                put("fieldExpiryDateTitle", DeDriverLicenseFront.NormalizedFieldNames.EXPIRY_DATE);
                put("fieldGivenNamesTitle", DeDriverLicenseFront.NormalizedFieldNames.GIVEN_NAMES);
                put("fieldIdTitle", DeDriverLicenseFront.NormalizedFieldNames.ID);
                put("fieldIssueDateTitle", DeDriverLicenseFront.NormalizedFieldNames.ISSUE_DATE);
                put("fieldIssuingAuthorityTitle", DeDriverLicenseFront.NormalizedFieldNames.ISSUING_AUTHORITY);
                put("fieldLicenseCategoriesTitle", DeDriverLicenseFront.NormalizedFieldNames.LICENSE_CATEGORIES);
                put("fieldPhotoTitle", DeDriverLicenseFront.NormalizedFieldNames.PHOTO);
                put("fieldSignatureTitle", DeDriverLicenseFront.NormalizedFieldNames.SIGNATURE);
                put("fieldSurnameTitle", DeDriverLicenseFront.NormalizedFieldNames.SURNAME);
            }};

            if (documentTypes.contains(RootDocumentType.DeIdCardBack)) {
                for (Map.Entry<String, String> entry : deIdCardBackFields.entrySet()) {
                    addFieldPropertyFromMap(fields, configuration, entry.getKey(), entry.getValue());
                }
            }

            if (documentTypes.contains(RootDocumentType.DeIdCardFront)) {
                for (Map.Entry<String, String> entry : deIdCardFrontFields.entrySet()) {
                    addFieldPropertyFromMap(fields, configuration, entry.getKey(), entry.getValue());
                }
            }

            if (documentTypes.contains(RootDocumentType.DePassport)) {
                for (Map.Entry<String, String> entry : dePassportFields.entrySet()) {
                    addFieldPropertyFromMap(fields, configuration, entry.getKey(), entry.getValue());
                }
            }

            if (documentTypes.contains(RootDocumentType.DeDriverLicenseBack)) {
                for (Map.Entry<String, String> entry : deDriverLicenseBackFields.entrySet()) {
                    addFieldPropertyFromMap(fields, configuration, entry.getKey(), entry.getValue());
                }
            }

            if (documentTypes.contains(RootDocumentType.DeDriverLicenseFront)) {
                for (Map.Entry<String, String> entry : deDriverLicenseFrontFields.entrySet()) {
                    addFieldPropertyFromMap(fields, configuration, entry.getKey(), entry.getValue());
                }
            }
        }

        return fields;
    }

    private List<GenericDocument> extractDocumentsFromResultWrappers(
            List<ResultWrapper<GenericDocument>> wrappers
    ) {
        final List<GenericDocument> documents = new ArrayList<>();

        for (ResultWrapper<GenericDocument> wrapper : wrappers) {
            // Get the ResultRepository from the ScanbotSDK instance
            final ResultRepository<GenericDocument> resultRepository = sdkWrapper.sdk().resultRepositoryForClass(wrapper.getClazz());

            // Receive an instance of GenericDocument class from the repository
            // This call will also remove the result from the repository (to make the memory usage less)
            final GenericDocument document = resultRepository.getResultAndErase(wrapper.getResultId());
            if (document == null) {
                continue;
            }

            documents.add(document);
        }

        return documents;
    }

    private void putGdrFieldFromTextFieldWrapper(
            final JsonArgs dest,
            final String jsonKey,
            final TextFieldWrapper textFieldWrapper
    ) {
        if (textFieldWrapper != null) {
            JsonArgs ocrResult = getResultMapFromOcrResult(textFieldWrapper.getValue());
            dest.put(jsonKey, ocrResult);
        }
    }

    private void putGdrFieldFromDriverLicenseCategory(
            final JsonArgs dest,
            final String jsonKey,
            final DeDriverLicenseBack.Category category
    ) {
        if (category != null) {
            JsonArgs categoryData = new JsonArgs();

            putGdrFieldFromTextFieldWrapper(categoryData, "restrictions", category.getRestrictions());
            putGdrFieldFromTextFieldWrapper(categoryData, "validFrom", category.getValidFrom());
            putGdrFieldFromTextFieldWrapper(categoryData, "validUntil", category.getValidUntil());

            dest.put(jsonKey, categoryData);
        }
    }

    private void putGdrFieldFromDocuments(
            final List<GenericDocument> documents,
            final JsonArgs dest,
            final String jsonKey,
            final String documentKey
    ) {
        for (GenericDocument document : documents) {
            final Field field = document.fieldByTypeName(documentKey);
            if (field == null) {
                continue;
            }
            final OcrResult result = field.getValue();
            if (result == null) {
                return;
            }

            final JsonArgs fieldMap = getResultMapFromOcrResult(result);

            dest.put(jsonKey, fieldMap);
        }
    }

    private JsonArgs getResultMapFromOcrResult(OcrResult result) {
        final JsonArgs fieldMap = new JsonArgs();
        fieldMap.put("text", result.getText());
        fieldMap.put("confidence", result.getConfidence());
        return fieldMap;
    }

    private void putImageInGdrJsonMapFromDocuments(
            final List<GenericDocument> documents,
            final JsonArgs dest,
            final String jsonKey,
            final String documentKey
    ) {
        try {
            final Bitmap photo = getImageFromGdrDocuments(documents, documentKey);
            if (photo != null) {
                final Uri imageUri = sdkWrapper.storeImage(photo, getImageQualityArg(this.jsonArgs));
                dest.put(jsonKey, imageUri.toString());
            }
        } catch (Exception e) {
            debugLog(e.toString());
        }
    }

    private Bitmap getImageFromGdrDocuments(
            final List<GenericDocument> documents,
            final String fieldKey
    ) {
        for (GenericDocument document : documents) {
            final Field field = document.fieldByTypeName(fieldKey);
            if (field == null) {
                continue;
            }
            final Bitmap image = field.getImage();
            if (image == null) {
                continue;
            }

            return image;
        }

        return null;
    }

    private CameraOrientationMode getCameraOrientationModeFromUiConfigs(JSONObject uiConfigs) {
        CameraOrientationMode mode = null;

        if (uiConfigs.has("interfaceOrientation")) {
            final String orientation = JsonUtils.getStringOrNull(uiConfigs, "interfaceOrientation");

            switch (orientation) {
                case "PORTRAIT":
                    mode = CameraOrientationMode.PORTRAIT;
                    break;
                case "LANDSCAPE":
                    mode = CameraOrientationMode.LANDSCAPE;
                    break;
            }
        }

        return mode;
    }
}
