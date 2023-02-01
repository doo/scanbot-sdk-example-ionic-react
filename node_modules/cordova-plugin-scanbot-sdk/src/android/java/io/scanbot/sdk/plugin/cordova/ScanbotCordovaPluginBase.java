/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import io.scanbot.sdk.plugin.cordova.utils.ImageUtils;
import io.scanbot.sdk.plugin.cordova.utils.JsonArgs;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import io.scanbot.sdk.plugin.cordova.utils.LogUtils;
import io.scanbot.sdk.process.PDFPageSize;
import io.scanbot.sdk.tiff.model.TIFFImageWriterCompressionOptions;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Base abstract class for Scanbot Cordova Plugins
 */
public abstract class ScanbotCordovaPluginBase extends CordovaPlugin {

    protected ScanbotSdkWrapper sdkWrapper;


    protected abstract String getLogTag();


    /**
     * Called after plugin construction and fields have been initialized.
     */
    @Override
    protected void pluginInitialize() {
        sdkWrapper = new ScanbotSdkWrapper(cordova.getActivity());
    }

    /**
     * Called when the Activity is being destroyed (e.g. if a plugin calls out to an
     * external Activity and the OS kills the CordovaActivity in the background).
     * The plugin should save its state in this method only if it is awaiting the
     * result of an external Activity and needs to preserve some information so as
     * to handle that result; onRestoreStateForActivityResult() will only be called
     * if the plugin is the recipient of an Activity result
     *
     * @return  Bundle containing the state of the plugin or null if state does not
     *          need to be saved
     */
    @Override
    public Bundle onSaveInstanceState() {
        final Bundle state = new Bundle();
        //state.putBoolean("loggingEnabled", loggingEnabled);
        return state;
    }

    /**
     * Called when a plugin is the recipient of an Activity result after the
     * CordovaActivity has been destroyed. The Bundle will be the same as the one
     * the plugin returned in onSaveInstanceState()
     *
     * @param state             Bundle containing the state of the plugin
     * @param callbackContext   Replacement Context to return the plugin result to
     */
    @Override
    public void onRestoreStateForActivityResult(final Bundle state, final CallbackContext callbackContext) {
        this.sdkWrapper = new ScanbotSdkWrapper(cordova.getActivity());
    }

    protected String getImageFileUriArg(final JSONObject args) throws JSONException {
        return getImageFileUriArg(args, null);
    }

    protected String getImageFileUriArg(final JSONObject args, final String prefix) throws JSONException {
        final String key = prefix == null ? "imageFileUri" : prefix + "ImageFileUri";

        final String imageFileUri = JsonUtils.getJsonArg(args, key, null);
        if (imageFileUri != null && !"".equals(imageFileUri.trim())) {
            return Uri.parse(imageFileUri).toString();
        }
        final String errorMsg = "Missing required JSON argument: " + key;
        errorLog(errorMsg);
        throw new JSONException(errorMsg);
    }

    protected int getDegreesArg(final JSONObject args) throws JSONException {
        return JsonUtils.getJsonArg(args, "degrees", 0);
    }

    protected String getImageFilterArg(final JSONObject args) throws JSONException {
        final String imageFilter = JsonUtils.getJsonArg(args, "imageFilter", null);
        if (imageFilter != null && !"".equals(imageFilter.trim())) {
            return imageFilter;
        }
        final String errorMsg = "Missing required JSON argument: imageFilter";
        errorLog(errorMsg);
        throw new JSONException(errorMsg);
    }

    protected List<Uri> getImagesArg(final JSONObject args) throws JSONException {
        if (!args.has("images")) {
            final String errorMsg = "Missing required JSON argument: images";
            errorLog(errorMsg);
            throw new JSONException(errorMsg);
        }
        final List<Uri> result = new ArrayList<Uri>();
        for (final String imageFileUri: JsonUtils.getJsonArg(args, "images")) {
            result.add(Uri.parse(imageFileUri));
        }
        return result;
    }

    protected PDFPageSize getPDFPageSizeArg(final JSONObject args) throws JSONException {
        if (!args.has("pageSize")) {
            return PDFPageSize.FROM_IMAGE;
        }

        final String pageSizeName = args.getString("pageSize");

        if (pageSizeName.equals("FROM_IMAGE")) return PDFPageSize.FROM_IMAGE;
        if (pageSizeName.equals("A4")) return PDFPageSize.A4;
        if (pageSizeName.equals("FIXED_A4")) return PDFPageSize.FIXED_A4;
        if (pageSizeName.equals("US_LETTER")) return PDFPageSize.US_LETTER;
        if (pageSizeName.equals("FIXED_US_LETTER")) return PDFPageSize.FIXED_US_LETTER;
        if (pageSizeName.equals("AUTO_LOCALE")) return PDFPageSize.AUTO_LOCALE;
        if (pageSizeName.equals("AUTO")) return PDFPageSize.AUTO;
        return PDFPageSize.AUTO;
    }

    protected int getTimesArg(final JSONObject args) throws JSONException {
        if (args.has("times")) {
            return args.getInt("times");
        }
        final String errorMsg = "Missing required JSON argument: times";
        errorLog(errorMsg);
        throw new JSONException(errorMsg);
    }

    protected List<String> getLanguagesArg(final JSONObject args) throws JSONException {
        return JsonUtils.getJsonArg(args, "languages");
    }

    protected int getImageQualityArg(final JSONObject args) throws JSONException {
        int quality = JsonUtils.getJsonArg(args, "quality", ImageUtils.JPEG_QUALITY);
        if (quality <= 0 || quality > 100) {
            quality = ImageUtils.JPEG_QUALITY;
        }
        return quality;
    }

    protected boolean getOneBitEncodedArg(final JSONObject args) throws JSONException {
        return JsonUtils.getJsonArg(args, "oneBitEncoded", false);
    }

    protected JSONObject getPageJsonArg(final JSONObject args, final boolean required) throws JSONException {
        final JSONObject page = JsonUtils.getJsonObject(args, "page", null);
        if (required && page == null) {
            throw new JSONException("Missing required JSON field: page");
        }
        return page;
    }

    protected JSONArray getPagesJsonArg(final JSONObject args, final boolean required) throws JSONException {
        final JSONArray pages = JsonUtils.getJsonArray(args, "pages", null);
        if (required && pages == null) {
            throw new JSONException("Missing required JSON field: pages");
        }
        return pages;
    }

    protected int getDpiArg(final JSONObject args, final int defaultValue) throws JSONException {
        return JsonUtils.getJsonArg(args, "dpi", defaultValue);
    }

    protected TIFFImageWriterCompressionOptions getTiffCompressionArg(
            final JSONObject args, final TIFFImageWriterCompressionOptions defaultValue) throws JSONException {
        if (args.has("compression")) {
            final String enumName = "COMPRESSION_" + args.getString("compression");
            return TIFFImageWriterCompressionOptions.valueOf(enumName);
        }
        return defaultValue;
    }


    protected void debugLog(final String msg) {
        LogUtils.debugLog(getLogTag(), msg);
    }

    protected void errorLog(final String msg) {
        LogUtils.errorLog(getLogTag(), msg);
    }

    protected void errorLog(final String msg, final Throwable e) {
        LogUtils.errorLog(getLogTag(), msg, e);
    }

    /**
     * Loads an image by file path or file URI.
     * @param imageFile Must be a valid file path or a valid file URI.
     * @return
     * @throws IOException
     */
    protected Bitmap loadImage(final String imageFile) throws IOException {
        if (imageFile != null && !"".equals(imageFile.trim())) {
            if (imageFile.contains("://")) {
                // looks like an URI
                final Uri uri = Uri.parse(imageFile);
                return sdkWrapper.loadImage(uri);
            }
            // must be a path:
            return sdkWrapper.loadImage(imageFile);
        }
        throw new IllegalArgumentException("Invalid imageFile. Must be a file URI or a file path: " + imageFile);
    }

    private JsonArgs baseSuccessCallbackResult(final boolean canceled) {
        return new JsonArgs().put("status", (canceled ? "CANCELED" : "OK"));
    }

    private JsonArgs baseErrorCallbackResult(final String errorMessage) {
        return new JsonArgs().put("status", "ERROR").put("message", errorMessage);
    }

    protected void successCallback(final CallbackContext callbackContext, final boolean canceled, final String dataFieldName, final JSONObject data) {
        final JsonArgs result = baseSuccessCallbackResult(canceled);
        if (dataFieldName != null) {
            result.put(dataFieldName, data);
        }
        callbackContext.success(result.jsonObj());
    }

    protected void successCallback(final CallbackContext callbackContext, final boolean canceled, final JsonArgs data) throws JSONException {
        final JSONObject result = baseSuccessCallbackResult(canceled).jsonObj();
        for (final Map.Entry<String, Object> e: data.getArgsMap().entrySet()) {
            result.put(e.getKey(), e.getValue());
        }
        callbackContext.success(result);
    }

    protected void successCallback(final CallbackContext callbackContext, final boolean canceled, final String successMessage) {
        final JsonArgs result = baseSuccessCallbackResult(canceled)
                .put("message", successMessage);
        callbackContext.success(result.jsonObj());
    }

    protected void errorCallback(final CallbackContext callbackContext, final String errorMessage) {
        errorLog(errorMessage);
        callbackContext.error(baseErrorCallbackResult(errorMessage).jsonObj());
    }

    protected void errorCallback(final CallbackContext callbackContext, final String errorMessage, final Exception e) {
        final String fullErrorMessage = errorMessage + " " + e.getMessage();
        errorLog(fullErrorMessage, e);
        callbackContext.error(baseErrorCallbackResult(fullErrorMessage).jsonObj());
    }

    protected void startScanbotActivityForResult(final Intent intent, final int requestCode) {
        cordova.startActivityForResult(this, intent, requestCode);
    }

    protected Context getApplicationContext() {
        return this.cordova.getActivity().getApplicationContext();
    }

}
