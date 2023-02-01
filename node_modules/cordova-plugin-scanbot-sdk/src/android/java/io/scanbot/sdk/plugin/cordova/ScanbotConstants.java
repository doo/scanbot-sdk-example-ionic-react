/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova;

public final class ScanbotConstants {

    private ScanbotConstants() {
    }

    // Activity Request Codes:
    public static final int REQUEST_SB_DOCUMENT_SCANNER = 31885; // Scanbot Document Scanner Activity Request Code
    public static final int REQUEST_SB_CROPPING = 31886; // Scanbot Cropping Activity Request Code
    public static final int REQUEST_SB_BARCODE_SCANNER = 31887; // Scanbot Barcode Scanner Activity Request Code
    public static final int REQUEST_SB_MRZ_SCANNER = 31888; // Scanbot MRZ Scanner Activity Request Code
    public static final int REQUEST_SB_EHIC_SCANNER = 31889; // Scanbot EHIC Scanner Activity Request Code
    public static final int REQUEST_SB_LP_SCANNER = 31890; // Scanbot License Plate Scanner Activity Request Code
    public static final int REQUEST_SB_DATA_SCANNER = 31891; // Scanbot Data Scanner Activity Request Code
    public static final int REQUEST_SB_GENERIC_DOCUMENT_RECOGNIZER = 31892; // Scanbot Generic Document Recognizer Activity Request Code
    public static final int REQUEST_SB_CHECK_RECOGNIZER = 31893; //Scanbot Check Recognizer Activity Request Code
}
