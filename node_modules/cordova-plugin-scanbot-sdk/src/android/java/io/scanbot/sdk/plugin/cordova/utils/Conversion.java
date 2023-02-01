package io.scanbot.sdk.plugin.cordova.utils;

import io.scanbot.sap.SdkFeature;
import io.scanbot.sap.Status;

public class Conversion {

    public static String featureToString(SdkFeature feature) {
        switch (feature) {
            case Check:
                return "Check";
            case OCR:
                return "OCR";
            case Barcode:
                return "QRCode";
            case NoSdkFeature:
                return "NoFeature";
            case CloudUpload:
                return "CloudUpload";
            case PDFCreation:
                return "PDFCreation";
            case W2Detection:
                return "W2Detection";
            case EdgeDetection:
                return "EdgeDetection";
            case CreditCardRecognition:
                return "CreditCardRecognition";
            case DataIntelligence:
                return "DataIntelligence";
            case MRZRecognition:
                return "MRZRecognition";
            case MedicalCertRecognition:
                return "MedicalCertRecognition";
            case EdgeDetectionUI:
                return "EdgeDetectionUI";
            case EHICRecognition:
                return "EHICRecognition";
            case ImageProcessing:
                return "ImageProcessing";
            case InvoiceDetection:
                return "InvoiceDetection";
            case MultipleObjectsDetection:
                return "MultipleObjectsDetection";
            case PayformDetection:
                return "PayformDetection";
            case TextOrientationDetection:
                return "TextOrientationDetection";
            default:
                return "Unknown";
        }
    }

    public static String statusToString(Status status) {
        switch (status) {
            case StatusOkay:
                return "Okay";
            case StatusTrial:
                return "Trial";
            case StatusFailureExpired:
                return "Expired";
            case StatusFailureWrongOS:
                return "WrongOS";
            case StatusFailureCorrupted:
                return "Corrupted";
            case StatusFailureAppIDMismatch:
                return "AppIDMismatch";
            case StatusFailureNotSet:
                return "NotSet";
            default:
                return "Unknown";
        }
    }

}
