package io.scanbot.sdk.plugin.cordova.helpers;

import org.json.JSONException;
import org.json.JSONObject;

import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfig;
import io.scanbot.sdk.barcode.entity.BarcodeScannerAdditionalConfigBuilder;
import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;
import kotlin.Unit;
import kotlin.jvm.functions.Function1;

public class ScanbotBarcodeDetectorAdditionalConfigBuilder implements Function1<BarcodeScannerAdditionalConfigBuilder, Unit> {

    final JSONObject options;

    public ScanbotBarcodeDetectorAdditionalConfigBuilder(final JSONObject options) {
        this.options = options;
    }

    @Override
    public Unit invoke(BarcodeScannerAdditionalConfigBuilder builder) {
        final BarcodeScannerAdditionalConfig config;
        try {
            config = JsonUtils.extractBarcodeScannerAdditionalConfig(options);
            if (config == null) {
                return Unit.INSTANCE;
            }

            builder.setLowPowerMode(config.getLowPowerMode());
            builder.setMinimumTextLength(config.getMinimumTextLength());
            builder.setMaximumTextLength(config.getMaximumTextLength());
            builder.setMinimum1DQuietZoneSize(config.getMinimum1DQuietZoneSize());
            builder.setStripCheckDigits(config.getStripCheckDigits());
            builder.setGs1DecodingEnabled(config.getGs1DecodingEnabled());
            builder.setMsiPlesseyChecksumAlgorithms(config.getMsiPlesseyChecksumAlgorithms());
        } catch (JSONException e) {
        }
        return Unit.INSTANCE;
    }
}
