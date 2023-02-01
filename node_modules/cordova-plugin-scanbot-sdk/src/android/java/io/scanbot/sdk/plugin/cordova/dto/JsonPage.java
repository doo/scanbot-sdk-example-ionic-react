package io.scanbot.sdk.plugin.cordova.dto;

import android.graphics.PointF;
import android.net.Uri;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import io.scanbot.sdk.core.contourdetector.DetectionResult;
import io.scanbot.sdk.core.contourdetector.DetectionStatus;
import io.scanbot.sdk.persistence.Page;
import io.scanbot.sdk.persistence.PageFileStorage;
import io.scanbot.sdk.persistence.PageImageSource;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import io.scanbot.sdk.process.ImageFilterType;

import static io.scanbot.sdk.plugin.cordova.utils.StorageUtils.uriWithHash;

public class JsonPage {

    private static String JSON_PROP_PAGE_ID = "pageId";
    private static String JSON_PROP_POLYGON = "polygon";
    private static String JSON_PROP_DETECTION_RESULT = "detectionResult";
    private static String JSON_PROP_FILTER = "filter";
    private static String JSON_PROP_DOCUMENT_IMAGE_SIZE_LIMIT = "documentImageSizeLimit";
    private static String JSON_PROP_ORIG_IMAGE_FILE = "originalImageFileUri";
    private static String JSON_PROP_DOC_IMAGE_FILE = "documentImageFileUri";
    private static String JSON_PROP_ORIG_PREVIEW_IMAGE_FILE = "originalPreviewImageFileUri";
    private static String JSON_PROP_DOC_PREVIEW_IMAGE_FILE = "documentPreviewImageFileUri";
    private static String JSON_PROP_IS_CAPTURED_AUTOMATICALLY = "isCapturedAutomatically";

    public final String pageId;
    public final JSONArray polygon;
    public final String detectionResult;
    public final String filter;
    public final JSONObject documentImageSizeLimit;

    public final String originalImageFileUri;
    public final String documentImageFileUri;

    public final String originalPreviewImageFileUri;
    public final String documentPreviewImageFileUri;

    public final boolean isCapturedAutomatically;

    private JsonPage(final String pageId,
                     final JSONArray polygon,
                     final String detectionResult,
                     final String originalImageFileUri,
                     final String documentImageFileUri,
                     final String originalPreviewImageFileUri,
                     final String documentPreviewImageFileUri,
                     final String filter,
                     final JSONObject documentImageSizeLimit,
                     final boolean isCapturedAutomatically) {
        this.pageId = pageId;
        this.polygon = polygon;
        this.detectionResult = detectionResult;
        this.originalImageFileUri = originalImageFileUri;
        this.documentImageFileUri = documentImageFileUri;
        this.originalPreviewImageFileUri = originalPreviewImageFileUri;
        this.documentPreviewImageFileUri = documentPreviewImageFileUri;
        this.filter = filter;
        this.documentImageSizeLimit = documentImageSizeLimit;
        this.isCapturedAutomatically = isCapturedAutomatically;
    }

    private static String fileExistsCheck(final Uri fileUri) {
        return ((fileUri != null && new File(fileUri.getPath()).exists()) ? fileUri.toString() : null);
    }

    public static JsonPage fromSdkPage(final Page page, final PageFileStorage pageFileStorage) {
        return new JsonPage(
                page.getPageId(),
                JsonUtils.sdkPolygonToJson(page.getPolygon()),
                JsonUtils.sdkDetectionResultToJsString(page.getDetectionStatus()),
                fileExistsCheck(pageFileStorage.getImageURI(page.getPageId(), PageFileStorage.PageFileType.ORIGINAL)),
                fileExistsCheck(pageFileStorage.getImageURI(page.getPageId(), PageFileStorage.PageFileType.DOCUMENT)),
                fileExistsCheck(pageFileStorage.getPreviewImageURI(page.getPageId(), PageFileStorage.PageFileType.ORIGINAL)),
                fileExistsCheck(pageFileStorage.getPreviewImageURI(page.getPageId(), PageFileStorage.PageFileType.DOCUMENT)),
                JsonUtils.sdkImageFilterToJsFilter(page.getFilter()),
                JsonUtils.jsonFromSize(page.getDocumentImageSizeLimit()),
                page.getPageImageSource() == PageImageSource.AUTOSNAPPING
        );
    }

    public static JsonPage fromJson(final JSONObject jsonData) throws JSONException {
        // page ID is required
        final String pageId = JsonUtils.getJsonArg(jsonData, JSON_PROP_PAGE_ID, null);
        if (pageId == null) {
            throw new IllegalArgumentException("Missing required JSON field: " + JSON_PROP_PAGE_ID);
        }

        return new JsonPage(
                pageId,
                JsonUtils.getJsonArray(jsonData, JSON_PROP_POLYGON, new JSONArray()),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_DETECTION_RESULT, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_ORIG_IMAGE_FILE, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_DOC_IMAGE_FILE, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_ORIG_PREVIEW_IMAGE_FILE, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_DOC_PREVIEW_IMAGE_FILE, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_FILTER, JsonUtils.sdkImageFilterToJsFilter(ImageFilterType.NONE)),
                JsonUtils.getJsonObject(jsonData, JSON_PROP_DOCUMENT_IMAGE_SIZE_LIMIT, null),
                JsonUtils.getJsonArg(jsonData, JSON_PROP_IS_CAPTURED_AUTOMATICALLY, false)
        );
    }

    public JSONObject asJsonObj() {
        final Map<String, Object> argsMap = new HashMap<String, Object>();
        argsMap.put(JSON_PROP_PAGE_ID, this.pageId);
        argsMap.put(JSON_PROP_POLYGON, this.polygon);
        argsMap.put(JSON_PROP_FILTER, this.filter);
        argsMap.put(JSON_PROP_DETECTION_RESULT, this.detectionResult);
        argsMap.put(JSON_PROP_ORIG_IMAGE_FILE, uriWithHash(this.originalImageFileUri));
        argsMap.put(JSON_PROP_ORIG_PREVIEW_IMAGE_FILE, uriWithHash(this.originalPreviewImageFileUri));

        if (this.documentImageFileUri != null) {
            argsMap.put(JSON_PROP_DOC_IMAGE_FILE, uriWithHash(this.documentImageFileUri));
            argsMap.put(JSON_PROP_DOC_PREVIEW_IMAGE_FILE, uriWithHash(this.documentPreviewImageFileUri));
        }
        if (this.documentImageSizeLimit != null) {
            argsMap.put(JSON_PROP_DOCUMENT_IMAGE_SIZE_LIMIT, this.documentImageSizeLimit);
        }

        argsMap.put(JSON_PROP_IS_CAPTURED_AUTOMATICALLY, this.isCapturedAutomatically);

        return new JSONObject(argsMap);
    }

    public Page asSdkPage() throws JSONException {
        final List<PointF> polygon = JsonUtils.jsonPolygonToSdk(this.polygon);
        final DetectionStatus detectionResult = JsonUtils.jsDetectionResultToSdkDetectionResult(this.detectionResult);
        final ImageFilterType filterType = JsonUtils.jsImageFilterToSdkFilter(this.filter);
        final Page.Size sdkDocumentImageSizeLimit = JsonUtils.sizeFromJson(this.documentImageSizeLimit);
        return new Page(pageId, polygon, detectionResult, filterType, sdkDocumentImageSizeLimit);
    }
}
