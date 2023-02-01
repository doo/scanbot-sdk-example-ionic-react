package io.scanbot.sdk.plugin.cordova;

import java.util.Map;

import io.scanbot.sdk.barcode.BarcodeFilter;
import io.scanbot.sdk.barcode.entity.BarcodeItem;
import io.scanbot.sdk.barcode.entity.BarcodeMetadataKey;

public class CordovaBarcodeExtensionFilter extends BarcodeFilter {
    public enum Type {
        WithExtension,
        WithEAN2Extension,
        WithEAN5Extension
    }

    private final Type filterType;
    public CordovaBarcodeExtensionFilter(Type filterType) {
        this.filterType = filterType;
    }

    @Override
    public boolean acceptsBarcode(BarcodeItem barcode) {
        if (!super.acceptsBarcode(barcode)) {
            return false;
        }

        final String extension = getExtensionOrEmpty(barcode);
        if (extension.equals("")) {
            return false;
        }

        switch (this.filterType) {
            case WithExtension:
                return true;
            case WithEAN2Extension:
                return extension.trim().length() == 2;
            case WithEAN5Extension:
                return extension.trim().length() == 5;
            default:
                return false;
        }
    }

    private static String getExtensionOrEmpty(final BarcodeItem barcodeItem)
    {
        final Map<BarcodeMetadataKey, String> metadata = barcodeItem.getMetadata();

        if (!metadata.containsKey(BarcodeMetadataKey.UpcEanExtension)) {
            return "";
        }
        return metadata.get(BarcodeMetadataKey.UpcEanExtension);
    }
}
