/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2019 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova.utils;

import android.graphics.PointF;
import android.graphics.RectF;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import io.scanbot.genericdocument.entity.Field;
import io.scanbot.genericdocument.entity.RootDocumentType;
import io.scanbot.sdk.barcode.BarcodeFilter;
import io.scanbot.sdk.barcode.entity.BarcodeDensity;
import io.scanbot.sdk.barcode.entity.BarcodeDocumentFormat;
import io.scanbot.sdk.barcode.entity.BarcodeFormat;
import io.scanbot.sdk.barcode.entity.BarcodeItem;
import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfig;
import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfigBuilder;
import io.scanbot.sdk.barcode.entity.BarcodeScannerConfigBuilder;
import io.scanbot.sdk.barcode.entity.BarcodeScanningResult;
import io.scanbot.sdk.barcode.entity.EngineMode;
import io.scanbot.sdk.barcode.entity.MSIPlesseyChecksumAlgorithm;
import io.scanbot.sdk.core.contourdetector.DetectionResult;
import io.scanbot.sdk.core.contourdetector.DetectionStatus;
import io.scanbot.sdk.ocr.process.OcrResult;
import io.scanbot.sdk.ocr.process.OcrResultBlock;
import io.scanbot.sdk.persistence.Page;
import io.scanbot.sdk.plugin.cordova.CordovaBarcodeExtensionFilter;
import io.scanbot.sdk.process.ImageFilterType;
import io.scanbot.sdk.ui.view.barcode.configuration.BarcodeScannerAdditionalConfiguration;
import io.scanbot.sdk.ui.view.camera.configuration.DocumentScannerAccessibilityConfiguration;
import io.scanbot.sdk.ui.view.edit.configuration.CroppingAccessibilityConfiguration;
import kotlin.Unit;
import kotlin.jvm.functions.Function1;

public final class JsonUtils {

    private static final String LOG_TAG = JsonUtils.class.getSimpleName();

    // ImageFilter mapping: JS constants => SDK
    private static final Map<String, ImageFilterType> imageFilterMapping = new HashMap<String, ImageFilterType>();

    static {
        imageFilterMapping.put("NONE", ImageFilterType.NONE);
        imageFilterMapping.put("COLOR_ENHANCED", ImageFilterType.COLOR_ENHANCED);
        imageFilterMapping.put("GRAYSCALE", ImageFilterType.GRAYSCALE);
        imageFilterMapping.put("BINARIZED", ImageFilterType.BINARIZED);
        imageFilterMapping.put("COLOR_DOCUMENT", ImageFilterType.COLOR_DOCUMENT);
        imageFilterMapping.put("PURE_BINARIZED", ImageFilterType.PURE_BINARIZED);
        imageFilterMapping.put("BACKGROUND_CLEAN", ImageFilterType.BACKGROUND_CLEAN);
        imageFilterMapping.put("BLACK_AND_WHITE", ImageFilterType.BLACK_AND_WHITE);
        imageFilterMapping.put("OTSU_BINARIZATION", ImageFilterType.OTSU_BINARIZATION);
        imageFilterMapping.put("DEEP_BINARIZATION", ImageFilterType.DEEP_BINARIZATION);
        imageFilterMapping.put("EDGE_HIGHLIGHT", ImageFilterType.EDGE_HIGHLIGHT);
        imageFilterMapping.put("LOW_LIGHT_BINARIZATION", ImageFilterType.LOW_LIGHT_BINARIZATION);
        imageFilterMapping.put("LOW_LIGHT_BINARIZATION_2", ImageFilterType.LOW_LIGHT_BINARIZATION_2);
        imageFilterMapping.put("SENSITIVE_BINARIZATION", ImageFilterType.SENSITIVE_BINARIZATION);
    }

    // Document Detection Result mapping: SDK => JS constants
    private static final Map<DetectionStatus, String> detectionResultMapping = new HashMap<DetectionStatus, String>();

    static {
        detectionResultMapping.put(DetectionStatus.OK, "OK");
        detectionResultMapping.put(DetectionStatus.OK_BARCODE, "OK_BARCODE");
        detectionResultMapping.put(DetectionStatus.OK_BUT_BAD_ANGLES, "OK_BUT_BAD_ANGLES");
        detectionResultMapping.put(DetectionStatus.OK_BUT_BAD_ASPECT_RATIO, "OK_BUT_BAD_ASPECT_RATIO");
        detectionResultMapping.put(DetectionStatus.OK_BUT_TOO_SMALL, "OK_BUT_TOO_SMALL");
        detectionResultMapping.put(DetectionStatus.OK_OFF_CENTER, "OK_OFF_CENTER");
        detectionResultMapping.put(DetectionStatus.ERROR_TOO_DARK, "ERROR_TOO_DARK");
        detectionResultMapping.put(DetectionStatus.ERROR_TOO_NOISY, "ERROR_TOO_NOISY");
        detectionResultMapping.put(DetectionStatus.ERROR_NOTHING_DETECTED, "ERROR_NOTHING_DETECTED");
    }

    private JsonUtils() {
    }


    public static JSONArray sdkPolygonToJson(final List<PointF> polygon) {
        final JSONArray result = new JSONArray();
        for (final PointF p : polygon) {
            final JsonArgs jsonPoint = new JsonArgs();
            jsonPoint.put("x", p.x).put("y", p.y);
            result.put(jsonPoint.jsonObj());
        }
        return result;
    }

    public static List<PointF> jsonPolygonToSdk(final JSONArray jsonPolygon) throws JSONException {
        final List<PointF> polygon = new ArrayList<PointF>();
        if (jsonPolygon != null && jsonPolygon.length() > 0) {
            if (jsonPolygon.length() == 4) {
                for (int i = 0; i < 4; i++) {
                    final JSONObject jsonPoint = jsonPolygon.getJSONObject(i);
                    polygon.add(new PointF((float) jsonPoint.getDouble("x"), (float) jsonPoint.getDouble("y")));
                }
            } else {
                debugLog("Invalid polygon (does not contain 4 points): " + jsonPolygon.toString());
            }
        }
        return polygon;
    }

    public static ImageFilterType jsImageFilterToSdkFilter(final String imageFilter) {
        if (imageFilterMapping.containsKey(imageFilter)) {
            return imageFilterMapping.get(imageFilter);
        }
        debugLog("Warning! Unsupported imageFilter: " + imageFilter);
        return ImageFilterType.NONE;
    }

    public static String sdkImageFilterToJsFilter(final ImageFilterType filter) {
        for (Map.Entry<String, ImageFilterType> e : imageFilterMapping.entrySet()) {
            if (e.getValue().equals(filter)) {
                return e.getKey();
            }
        }
        debugLog("Warning! Unsupported ImageFilterType: " + filter.name());
        return filter.name();
    }

    public static String sdkDetectionResultToJsString(final DetectionStatus detectionResult) {
        if (detectionResultMapping.containsKey(detectionResult)) {
            return detectionResultMapping.get(detectionResult);
        }
        debugLog("Warning! Unsupported DetectionResult: " + detectionResult);
        return DetectionStatus.ERROR_NOTHING_DETECTED.name();
    }

    public static DetectionStatus jsDetectionResultToSdkDetectionResult(final String detectionResult) {
        if (!detectionResultMapping.values().contains(detectionResult)) {
            debugLog("Warning! Unsupported DetectionResult string: " + detectionResult);
            return DetectionStatus.ERROR_NOTHING_DETECTED;
        }
        return DetectionStatus.valueOf(detectionResult);
    }

    public static boolean getJsonArg(final JSONObject args, final String key, final boolean defaultValue) throws JSONException {
        if (args.has(key)) {
            return args.getBoolean(key);
        }
        return defaultValue;
    }

    public static String getJsonArg(final JSONObject args, final String key, final String defaultValue) throws JSONException {
        if (args.has(key)) {
            return args.getString(key);
        }
        return defaultValue;
    }

    public static int getJsonArg(final JSONObject args, final String key, final int defaultValue) throws JSONException {
        if (args.has(key)) {
            return args.getInt(key);
        }
        return defaultValue;
    }

    public static double getJsonArg(final JSONObject args, final String key, final double defaultValue) throws JSONException {
        if (args.has(key)) {
            return args.getDouble(key);
        }
        return defaultValue;
    }

    public static List<String> getJsonArg(final JSONObject args, final String arrayKey) throws JSONException {
        final List<String> result = new ArrayList<String>();
        if (args.has(arrayKey)) {
            final JSONArray jsonArray = args.getJSONArray(arrayKey);
            for (int i = 0; i < jsonArray.length(); i++) {
                result.add(jsonArray.getString(i));
            }
        }
        return result;
    }

    public static JSONArray getJsonArray(final JSONObject args, final String arrayKey, final JSONArray defaultValue) throws JSONException {
        if (args.has(arrayKey)) {
            return args.getJSONArray(arrayKey);
        }
        return defaultValue;
    }

    public static JSONObject getJsonObject(final JSONObject args, final String key, final JSONObject defaultValue) throws JSONException {
        if (args.has(key)) {
            return args.getJSONObject(key);
        }
        return defaultValue;
    }

    private static void debugLog(final String msg) {
        LogUtils.debugLog(LOG_TAG, msg);
    }

    private static void errorLog(final String msg) {
        LogUtils.errorLog(LOG_TAG, msg);
    }

    private static void errorLog(final String msg, final Throwable e) {
        LogUtils.errorLog(LOG_TAG, msg, e);
    }

    public static JSONObject resultToJson(OcrResult result) throws JSONException {
        JSONObject resultJson = new JSONObject();
        JSONArray pagesJson = new JSONArray();

        for (OcrResult.OCRPage page : result.ocrPages) {
            pagesJson.put(pageToJson(page));
        }

        resultJson.put("pages", pagesJson);
        return resultJson;
    }

    private static JSONObject pageToJson(OcrResult.OCRPage page) throws JSONException {
        JSONObject pageJson = new JSONObject();

        pageJson.put("text", page.text);

        JSONArray wordsJson = new JSONArray();
        for (OcrResultBlock block : page.words) {
            wordsJson.put(blockToJson(block));
        }
        pageJson.put("words", wordsJson);

        JSONArray linesJson = new JSONArray();
        for (OcrResultBlock block : page.lines) {
            linesJson.put(blockToJson(block));
        }
        pageJson.put("lines", linesJson);

        JSONArray paragraphsJson = new JSONArray();
        for (OcrResultBlock block : page.paragraphs) {
            paragraphsJson.put(blockToJson(block));
        }
        pageJson.put("paragraphs", paragraphsJson);

        return pageJson;
    }

    private static JSONObject blockToJson(OcrResultBlock block) throws JSONException {
        JSONObject blockJson = new JSONObject();

        blockJson.put("boundingBox", boundingBoxToJson(block.boundingBox));
        blockJson.put("text", block.text);
        blockJson.put("confidence", block.confidenceValue);

        return blockJson;
    }

    private static JSONObject boundingBoxToJson(RectF box) throws JSONException {
        JSONObject boxJson = new JSONObject();

        boxJson.put("x", box.centerX());
        boxJson.put("y", box.centerY());
        boxJson.put("width", box.width());
        boxJson.put("height", box.height());

        return boxJson;
    }

    public static String getStringOrNull(JSONObject args, String key) {
        try {
            return args.getString(key);
        } catch (JSONException e) {
            return null;
        }
    }

    public static Page.Size sizeFromJson(JSONObject obj) throws JSONException {
        return obj != null ? new Page.Size(obj.getInt("width"), obj.getInt("height")) : new Page.Size();
    }

    public static JSONObject jsonFromSize(Page.Size size) {
        if (size.getWidth() == Integer.MAX_VALUE && size.getHeight() == Integer.MAX_VALUE) {
            return null;
        }
        final Map<String, Object> argsMap = new HashMap<String, Object>();
        argsMap.put("width", size.getWidth());
        argsMap.put("height", size.getHeight());
        return new JSONObject(argsMap);
    }

    public static JSONArray jsonFromBarcodeItems(List<BarcodeItem> items) throws JSONException {
        JSONArray result = new JSONArray();
        for (BarcodeItem item : items) {
            result.put(jsonFromBarcodeItem(item));
        }
        return result;
    }

    public static JSONObject jsonFromBarcodeItem(BarcodeItem item) throws JSONException {
        JSONObject result = new JSONObject();
        result.put("type", item.getBarcodeFormat().toString());
        result.put("text", item.getText());
        return result;
    }

    public static List<BarcodeFormat> formatsFromString(String input) throws JSONException {
        JSONArray barcodeFormats = new JSONArray(input);
        final ArrayList<BarcodeFormat> result = new ArrayList<>();

        for (int i = 0; i < barcodeFormats.length(); ++i) {
            result.add(BarcodeFormat.valueOf(barcodeFormats.getString(i)));
        }

        return result;
    }

    public static ArrayList<BarcodeFormat> extractBarcodeFormats(final JSONObject configuration) throws JSONException {

        final ArrayList<BarcodeFormat> nativeBarcodeFormats = new ArrayList<>();

        if (!configuration.has("barcodeFormats")) {
            return nativeBarcodeFormats;
        }

        JSONArray barcodeFormats = configuration.getJSONArray("barcodeFormats");

        for (int i = 0; i < barcodeFormats.length(); ++i) {
            nativeBarcodeFormats.add(BarcodeFormat.valueOf(barcodeFormats.getString(i)));
        }

        return nativeBarcodeFormats;
    }

    public static ArrayList<BarcodeDocumentFormat> extractBarcodeDocumentFormats(final JSONObject configuration) throws JSONException {

        ArrayList<BarcodeDocumentFormat> nativeFormats = new ArrayList<>();

        if (!configuration.has("acceptedDocumentFormats")) {
            return nativeFormats;
        }

        JSONArray formats = configuration.getJSONArray("acceptedDocumentFormats");

        for (int i = 0; i < formats.length(); ++i) {
            String format = formats.getString(i);
            nativeFormats.add(BarcodeDocumentFormat.valueOf(format));
        }

        return nativeFormats;
    }

    public static ArrayList<RootDocumentType> extractAcceptedDocumentTypes(final JSONObject configuration) throws JSONException {
        ArrayList<RootDocumentType> nativeDocumentTypes = new ArrayList<>();

        if (!configuration.has("acceptedDocumentTypes")) {
            return new ArrayList(RootDocumentType.Companion.getALL_TYPES());
        }

        JSONArray documentTypes = configuration.getJSONArray("acceptedDocumentTypes");

        for (int i = 0; i < documentTypes.length(); ++i) {
            String format = documentTypes.getString(i);

            final RootDocumentType documentType = genericDocumentTypeToNativeString(format);
            if (documentType != null) {
                nativeDocumentTypes.add(documentType);
            }
        }

        return nativeDocumentTypes;
    }

    public static ArrayList<io.scanbot.check.entity.RootDocumentType> extractAcceptedCheckStandards(final JSONObject configuration) throws JSONException {
        ArrayList<io.scanbot.check.entity.RootDocumentType> nativeCheckTypes = new ArrayList<>();

        if (!configuration.has("acceptedCheckStandards")) {
            return new ArrayList(io.scanbot.check.entity.RootDocumentType.Companion.getALL_TYPES());
        }

        JSONArray checkTypes = configuration.getJSONArray("acceptedCheckStandards");

        for (int i = 0; i < checkTypes.length(); ++i) {
            String format = checkTypes.getString(i);

            final io.scanbot.check.entity.RootDocumentType checkType = genericCheckTypeToNativeString(format);
            if (checkType != null) {
                nativeCheckTypes.add(checkType);
            }
        }

        return nativeCheckTypes;
    }

    public static BarcodeScannerAdditionalConfig extractBarcodeScannerAdditionalConfig(JSONObject configuration) throws JSONException {
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

        return changed ? new BarcodeScannerAdditionalConfig(
                minimumTextLength,
                maximumTextLength,
                minimum1DQuietZoneSize,
                gs1DecodingEnabled,
                msiPlesseyChecksumAlgorithms,
                stripCheckDigits,
                lowPowerMode,
                codeDensity) : null;
    }

    public static BarcodeScannerAdditionalConfiguration extractBarcodeScannerAdditionalConfiguration(JSONObject configuration) throws JSONException {
        final BarcodeScannerAdditionalConfig config = extractBarcodeScannerAdditionalConfig(configuration);
        return config != null ? new BarcodeScannerAdditionalConfiguration(
                config.getMinimumTextLength(),
                config.getMaximumTextLength(),
                config.getMinimum1DQuietZoneSize(),
                config.getGs1DecodingEnabled(),
                config.getMsiPlesseyChecksumAlgorithms(),
                config.getStripCheckDigits(),
                config.getLowPowerMode(),
                config.getCodeDensity()) : null;
    }

    public static EngineMode extractEngineMode(JSONObject configuration) throws JSONException {
        if (!configuration.has("engineMode")) {
            return EngineMode.NextGen;
        }

        String mode = configuration.getString("engineMode");
        if ("LEGACY".equals(mode)) {
            return EngineMode.LegacyFast;
        }
        return EngineMode.NextGen;
    }

    public static RootDocumentType genericDocumentTypeToNativeString(final String documentType) {
        switch (documentType) {
            case "DeIdBack":
                return RootDocumentType.DeIdCardBack;
            case "DeIdFront":
                return RootDocumentType.DeIdCardFront;
            case "DePassport":
                return RootDocumentType.DePassport;
            case "DeDriverLicenseBack":
                return RootDocumentType.DeDriverLicenseBack;
            case "DeDriverLicenseFront":
                return RootDocumentType.DeDriverLicenseFront;
            default:
                return null;
        }
    }

    public static io.scanbot.check.entity.RootDocumentType genericCheckTypeToNativeString(final String documentType) {
        switch (documentType) {
            case "USACheck":
                return io.scanbot.check.entity.RootDocumentType.USACheck;
            case "FRACheck":
                return io.scanbot.check.entity.RootDocumentType.FRACheck;
            case "KWTCheck":
                return io.scanbot.check.entity.RootDocumentType.KWTCheck;
            case "AUSCheck":
                return io.scanbot.check.entity.RootDocumentType.AUSCheck;
            case "INDCheck":
                return io.scanbot.check.entity.RootDocumentType.INDCheck;
            case "UnknownCheck":
                return io.scanbot.check.entity.RootDocumentType.UnknownCheck;
            default:
                return null;
        }
    }

    public static DocumentScannerAccessibilityConfiguration extractDocumentScannerAccessibilityConfiguration(final JSONObject configuration) {
        return new DocumentScannerAccessibilityConfiguration(
                getStringOrNull(configuration, "flashButtonAccessibilityLabel"),
                getStringOrNull(configuration, "flashButtonAccessibilityHint"),
                getStringOrNull(configuration, "multiPageButtonAccessibilityLabel"),
                getStringOrNull(configuration, "multiPageButtonAccessibilityHint"),
                getStringOrNull(configuration, "autoSnappingButtonAccessibilityLabel"),
                getStringOrNull(configuration, "autoSnappingButtonAccessibilityHint"),
                getStringOrNull(configuration, "cancelButtonAccessibilityLabel"),
                getStringOrNull(configuration, "cancelButtonAccessibilityHint"),
                getStringOrNull(configuration, "pageCounterButtonAccessibilityLabel"),
                getStringOrNull(configuration, "pageCounterAccessibilityHint"),
                getStringOrNull(configuration, "shutterButtonAccessibilityLabel"),
                getStringOrNull(configuration, "shutterButtonAccessibilityHint")
        );
    }

    public static CroppingAccessibilityConfiguration extractCroppingAccessibilityConfiguration(final JSONObject configuration) {
        return new CroppingAccessibilityConfiguration(
                getStringOrNull(configuration, "cancelButtonAccessibilityLabel"),
                getStringOrNull(configuration, "cancelButtonAccessibilityHint"),
                getStringOrNull(configuration, "doneButtonAccessibilityLabel"),
                getStringOrNull(configuration, "doneButtonAccessibilityHint"),
                getStringOrNull(configuration, "detectButtonAccessibilityLabel"),
                getStringOrNull(configuration, "detectButtonAccessibilityHint"),
                getStringOrNull(configuration, "resetButtonAccessibilityLabel"),
                getStringOrNull(configuration, "resetButtonAccessibilityHint"),
                getStringOrNull(configuration, "rotateButtonAccessibilityLabel"),
                getStringOrNull(configuration, "rotateButtonAccessibilityHint")
        );
    }

    public static BarcodeFilter extractBarcodeFilter(final JSONObject options) throws JSONException {
        if (!options.has("barcodeFilter")) {
            return null;
        }
        final String filterType = options.getString("barcodeFilter");
        try {
            final CordovaBarcodeExtensionFilter.Type type =
                    CordovaBarcodeExtensionFilter.Type.valueOf(filterType);
            return new CordovaBarcodeExtensionFilter(type);
        } catch (IllegalArgumentException exception) {
            final String errMsg = String.format("The value passed in 'barcodeFilter' (%s) does not exist", filterType);
            Log.e("SCANBOT_SDK", errMsg);
        }

        return null;
    }

    public static List<BarcodeItem> getBarcodeItemsFromResultWithFilter(BarcodeScanningResult result, BarcodeFilter filter) {
        if (result == null) {
            return new ArrayList<>();
        }

        final List<BarcodeItem> filteredBarcodeItems = new ArrayList<>();
        for (BarcodeItem barcodeItem : result.getBarcodeItems()) {
            if (!filter.acceptsBarcode(barcodeItem)) {
                continue;
            }
            filteredBarcodeItems.add(barcodeItem);
        }
        return filteredBarcodeItems;
    }

    public static String getNormalizedCheckFieldName(Field.Type fieldType) {
        String res;

        switch (fieldType.getName()) {
            case "FontType":
                res = "fontType";
                break;
            case "RawString":
                res = "rawString";
                break;
            case "AccountNumber":
                res = "accountNumber";
                break;
            case "AuxiliaryOnUs":
                res = "auxiliaryOnUs";
                break;
            case "TransitNumber":
                res = "transitNumber";
                break;
            case "ChequeNumber":
                res = "chequeNumber";
                break;
            case "RoutingNumber":
                res = "routingNumber";
                break;
            case "SortCode":
                res = "sortCode";
                break;
            case "AuxDomestic":
                res = "auxDomestic";
                break;
            case "BSB":
                res = "bsb";
                break;
            case "ExtraAuxDomestic":
                res = "extraAuxDomestic";
                break;
            case "TransactionCode":
                res = "transactionCode";
                break;
            case "SerialNumber":
                res = "serialNumber";
                break;
            case "SortNumber":
                res = "sortNumber";
                break;
            default:
                res = fieldType.getName();
        }

        return res;
    }
}
