package io.scanbot.sdk.plugin.cordova.helpers;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import io.scanbot.sdk.barcode.entity.BarcodeDocumentFormat;
import io.scanbot.sdk.barcode.entity.BarcodeFormat;
import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfig;
import io.scanbot.sdk.barcode.entity.BarcodeScannerConfigBuilder;
import io.scanbot.sdk.barcode.entity.EngineMode;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import kotlin.Unit;
import kotlin.jvm.functions.Function1;

public class ScanbotBarcodeDetectorConfigBuilder implements Function1<BarcodeScannerConfigBuilder, Unit> {

    final JSONObject options;

    public ScanbotBarcodeDetectorConfigBuilder(final JSONObject options) {
        this.options = options;
    }

    @Override
    public Unit invoke(BarcodeScannerConfigBuilder barcodeScannerConfigBuilder) {
        try {
            final ArrayList<BarcodeFormat> barcodeFormats = JsonUtils.extractBarcodeFormats(options);
            final ArrayList<BarcodeDocumentFormat> barcodeDocumentFormats = JsonUtils.extractBarcodeDocumentFormats(options);

            if (!barcodeFormats.isEmpty()) {
                barcodeScannerConfigBuilder.setBarcodeFormats(barcodeFormats);
            }

            if (!barcodeDocumentFormats.isEmpty()) {
                barcodeScannerConfigBuilder.setAcceptedDocumentFormats(barcodeDocumentFormats);
            }

            // Engine Mode
            final EngineMode engineMode = JsonUtils.extractEngineMode(options);
            barcodeScannerConfigBuilder.setEngineMode(engineMode);

            // Additional Parameters
            final BarcodeScannerAdditionalConfig additionalConfiguration = JsonUtils.extractBarcodeScannerAdditionalConfig(options);
            if (additionalConfiguration != null) {
                barcodeScannerConfigBuilder.setAdditionalConfig(additionalConfiguration);
            }
        } catch (JSONException e) {
        }

        return Unit.INSTANCE;
    }
}
