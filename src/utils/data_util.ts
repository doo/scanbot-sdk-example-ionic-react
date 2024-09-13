import { BrightnessFilter, ColorDocumentFilter, ContrastFilter, CustomBinarizationFilter, GrayscaleFilter, ScanbotBinarizationFilter, WhiteBlackPointFilter } from "capacitor-plugin-scanbot-sdk";
import { CoreFeatureEnum } from "../enums/core_feature_enum";
import { CoreFeatureIdEnum } from "../enums/core_feature_id_enum";
import { PDFPageSizeEnum } from "../enums/pdf_page_size_enum";
import { TiffOptionsEnum } from "../enums/tiff_option_enum";
import { CoreFeatureModel } from "../models/core_feature_model";

export const CORE_FEATURES: CoreFeatureModel[] = [
    {
        id: CoreFeatureIdEnum.DocumentDetector,
        title: "Document Scanner",
        description: "The Scanbot SDK provides a Ready-To-Use UI screen component for document scanning.",
        items: [
            { key: CoreFeatureEnum.Document, value: "Scan Document" },
            { key: CoreFeatureEnum.FinderDocument, value: "Finder Document Scanner" },
            { key: CoreFeatureEnum.ImageResult, value: "View Image Results" },
        ],
    },
    {
        id: CoreFeatureIdEnum.BarcodeDetactor,
        title: "Barcode Scanner & Detector",
        description: "The Scanbot SDK provides a Ready-To-Use UI screen component for Barcode and QR-Code scanning.",
        items: [
            { key: CoreFeatureEnum.SingleBarcode, value: "RTU UI Single Scanning" },
            { key: CoreFeatureEnum.MultiBarcode, value: "RTU UI Multi Scanning" },
            { key: CoreFeatureEnum.MultiARBarcode, value: "RTU UI Multi AR Scanning" },
            { key: CoreFeatureEnum.ImportBarcodeImage, value: "Import Image & Detect Barcodes" },
        ],
    },
    {
        id: CoreFeatureIdEnum.DataDetactor,
        title: "Data Detectors",
        description: "The Scanbot SDK provides a Ready-To-Use UI screen component for detect data from MRZ, ID CARDS, EHIC, etc... ",
        items: [
            { key: CoreFeatureEnum.MRZ, value: "Scan MRZ" },
            { key: CoreFeatureEnum.EHIC, value: "Scan Health Insurance Card" },
            { key: CoreFeatureEnum.Check, value: "Scan Checks" },
            { key: CoreFeatureEnum.ImportCheckOnImage, value: "Import Image & Detect Check" },
            { key: CoreFeatureEnum.LicensePlate, value: "Scan License Plate" },
            { key: CoreFeatureEnum.MedicalCertificate, value: "Scan Medical Certificate" },
            { key: CoreFeatureEnum.TextData, value: "Scan Text Data" },
            { key: CoreFeatureEnum.GenericDocument, value: "Scan Generic Documents" },
        ],
    },
    {
        id: CoreFeatureIdEnum.Other,
        title: "Test Other SDK API Methods",
        description: "The Scanbot SDK provides more API methods.",
        items: [
            { key: CoreFeatureEnum.LicenseInfo, value: "View License Info" },
            { key: CoreFeatureEnum.OCRInfo, value: "View OCR Info" },
            { key: CoreFeatureEnum.LearnMore, value: "Learn More About the Scanbot SDK" },
        ],
    },
];

export const GetItemList = (selectedItemId: CoreFeatureIdEnum) => {
    return CORE_FEATURES.find(item => item.id == selectedItemId)?.items!;
}

export const PDFPageSizeList = [
    { key: PDFPageSizeEnum.A3, value: "A3" },
    { key: PDFPageSizeEnum.A4, value: "A4" },
    { key: PDFPageSizeEnum.A5, value: "A5" },
    { key: PDFPageSizeEnum.B4, value: "B4" },
    { key: PDFPageSizeEnum.B5, value: "B5" },
    { key: PDFPageSizeEnum.COMM10, value: "COMM10" },
    { key: PDFPageSizeEnum.CUSTOM, value: "CUSTOM" },
    { key: PDFPageSizeEnum.EXECUTIVE, value: "EXECUTIVE" },
    { key: PDFPageSizeEnum.LEGAL, value: "LEGAL" },
    { key: PDFPageSizeEnum.LETTER, value: "LETTER" },
    { key: PDFPageSizeEnum.US4x6, value: "US4x6" },
    { key: PDFPageSizeEnum.US4x8, value: "US4x8" },
];

export const TiffOptions = [
    { key: TiffOptionsEnum.Binarized, value: "Binarized Images (1-bit)" },
    { key: TiffOptionsEnum.Color, value: "Color Images" },
];

export const FilterOptions = [
    { key: new ScanbotBinarizationFilter(), value: 'Scanbot Binarization Filter' },
    { key: new CustomBinarizationFilter({ preset: 'PRESET_1' }), value: 'Custom Binarization Filter' },
    { key: new ColorDocumentFilter(), value: 'Color Document Filter' },
    { key: new BrightnessFilter({ brightness: 0.2 }), value: 'Brightness Filter' },
    { key: new ContrastFilter({ contrast: 2 }), value: 'Contrast Filter' },
    { key: new GrayscaleFilter(), value: 'Grayscale Filter' },
    { key: new WhiteBlackPointFilter({ blackPoint: 0.2, whitePoint: 0.8 }), value: 'White Black Point Filter' },
];
