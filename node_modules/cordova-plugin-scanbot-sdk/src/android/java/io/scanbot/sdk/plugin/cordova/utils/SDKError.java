package io.scanbot.sdk.plugin.cordova.utils;

public class SDKError {

    public static String incompatibleCompression(String name) {
        String description = "The given compression type " + name + " is only applicable to binarized images.";
        return "Incompatible compression type. " + description;
    }
}
