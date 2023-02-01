/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.PointF;
import android.net.Uri;
import android.provider.MediaStore;

import io.scanbot.sap.SdkLicenseInfo;
import io.scanbot.sdk.ScanbotSDK;
import io.scanbot.sdk.barcode.ScanbotBarcodeDetector;
import io.scanbot.sdk.blob.BlobFactory;
import io.scanbot.sdk.blob.BlobManager;
import io.scanbot.sdk.core.contourdetector.ContourDetector;
import io.scanbot.sdk.core.contourdetector.DetectionResult;
import io.scanbot.sdk.docprocessing.PageProcessor;
import io.scanbot.sdk.entity.Language;
import io.scanbot.sdk.ocr.OpticalCharacterRecognizer;
import io.scanbot.sdk.ocr.process.OcrResult;
import io.scanbot.sdk.persistence.BarcodeFileStorage;
import io.scanbot.sdk.persistence.Page;
import io.scanbot.sdk.persistence.PageFileStorage;
import io.scanbot.sdk.persistence.cleanup.Cleaner;
import io.scanbot.sdk.persistence.fileio.FileIOProcessor;
import io.scanbot.sdk.plugin.cordova.utils.StorageUtils;
import io.scanbot.sdk.plugin.cordova.utils.LogUtils;
import io.scanbot.sdk.process.CropOperation;
import io.scanbot.sdk.process.FilterOperation;
import io.scanbot.sdk.process.ImageFilterType;
import io.scanbot.sdk.process.ImageProcessor;
import io.scanbot.sdk.process.Operation;
import io.scanbot.sdk.process.PDFPageSize;
import io.scanbot.sdk.process.PDFRenderer;
import io.scanbot.sdk.util.bitmap.BitmapUtils;
import io.scanbot.sdk.tiff.TIFFWriter;
import io.scanbot.sdk.tiff.model.TIFFImageWriterCompressionOptions;
import io.scanbot.sdk.tiff.model.TIFFImageWriterParameters;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.*;

/**
 * Scanbot SDK Wrapper for the Cordova Plugin
 */
public class ScanbotSdkWrapper {

    private static final String LOG_TAG = ScanbotSdkWrapper.class.getSimpleName();

    private final Context context;

    public ScanbotSdkWrapper(final Context context) {
        this.context = context;
    }

    public ScanbotSDK sdk() {
        return new ScanbotSDK((Activity) this.context);
    }

    public FileIOProcessor fileProcessor() {
        return new ScanbotSDK((Activity) this.context).fileIOProcessor();
    }

    public PageFileStorage pageFileStorage() {
        return new ScanbotSDK((Activity) this.context).getPageFileStorage();
    }

    public PageProcessor pageProcessor() {
        return new ScanbotSDK((Activity) this.context).createPageProcessor();
    }

    public BarcodeFileStorage barcodeFileStorage() {
        return new ScanbotSDK((Activity) this.context).createBarcodeFileStorage();
    }

    public ScanbotBarcodeDetector barcodeDetector() {
        return new ScanbotSDK((Activity) this.context).createBarcodeDetector();
    }

    public ContourDetector contourDetector() {
        return new ScanbotSDK((Activity) this.context).createContourDetector();
    }

    public ImageProcessor imageProcessor() {
        return new ScanbotSDK((Activity) this.context).imageProcessor();
    }

    public SdkLicenseInfo getLicenseInfo() {
        return new ScanbotSDK((Activity) this.context).getLicenseInfo();
    }

    public Bitmap loadImage(final String imageFilePath) throws IOException {
        final Bitmap bitmap = BitmapUtils.decodeQuietly(imageFilePath, null);
        if (bitmap == null) {
            throw new IOException("Could not load image. Bitmap is null.");
        }
        return bitmap;
    }


    public Bitmap loadImage(final Uri imageUri) throws IOException {
        return MediaStore.Images.Media.getBitmap(this.context.getContentResolver(), imageUri);
    }


    public File storeImageAsFile(final Bitmap image, final int quality) throws IOException {
        final File pictureFile = StorageUtils.generateRandomPluginStorageFile("jpg", this.context);
        final FileOutputStream fos = new FileOutputStream(pictureFile);
        image.compress(Bitmap.CompressFormat.JPEG, quality, fos);
        fos.close();
        return pictureFile;
    }


    public Uri storeImage(final Bitmap image, final int quality) throws IOException {
        return Uri.fromFile(storeImageAsFile(image, quality));
    }


    public DocumentDetectionResult documentDetection(final Bitmap bitmap) {
        debugLog("Applying document detection on bitmap...");

        final ContourDetector detector = contourDetector();
        final DetectionResult sdkDetectionResult = detector.detect(bitmap);
        if(sdkDetectionResult == null){
            return null;
        }

        final List<PointF> polygon = sdkDetectionResult.getPolygonF();

        final Bitmap documentImage = imageProcessor().processBitmap(bitmap, new CropOperation(polygon), false);
        return new DocumentDetectionResult(sdkDetectionResult, polygon, documentImage);
    }

    public List<String> getInstalledOcrLanguages(final PdfSdk pdfSdk) throws IOException {
        debugLog("Detecting installed OCR languages...");

        final List<String> installedLanguages = new ArrayList<String>();
        final Set<Language> allLanguagesWithAvailableOcrBlobs = pdfSdk.blobManager.getAllLanguagesWithAvailableOcrBlobs();
        for (final Language language : allLanguagesWithAvailableOcrBlobs) {
            installedLanguages.add(get2LetterLanguageCode(language));
        }
        return installedLanguages;
    }
    private String get2LetterLanguageCode(final Language lng) {
        final List<String> tags = lng.getLanguageTags();
        if (!tags.isEmpty()) {
            return tags.get(0); // should be the 2-letter code
        }
        return lng.getOcrBlobLanguageTag();
    }

    public OcrResult performOcr(final List<String> languagesIsoCodes,
                                OpticalCharacterRecognizer ocrRecognizer,
                                final List<Uri> images,
                                String outputFormat,
                                boolean encrypted) throws IOException {
        debugLog("Performing OCR...");

        final Set<Language> languages = new HashSet<Language>();
        for (final String languageIsoCode : languagesIsoCodes) {
            languages.add(Language.languageByLanguageTag(languageIsoCode));
        }

        final Set<Language> installedLanguages = ocrRecognizer.getInstalledLanguages();

        if (!installedLanguages.containsAll(languages)) {
            throw new IOException("OCR blobs for selected languages were not found.");
        }

        if (outputFormat.equals("PLAIN_TEXT")) {
            return ocrRecognizer.recognizeTextFromUris(images, encrypted, languages);
        }
        else {
            return ocrRecognizer.recognizeTextWithPdfFromUris(images, encrypted, PDFPageSize.FROM_IMAGE, languages);
        }
    }


    public Bitmap cropAndWarpImage(final Bitmap bitmap, final List<PointF> polygon) {
        return imageProcessor().processBitmap(bitmap, new CropOperation(polygon), false);
    }


    public Bitmap applyImageFilter(final Bitmap bitmap, final ImageFilterType imageFilter) {
        debugLog("Applying image filter on bitmap...");

        final List<PointF> polygon = new ArrayList<>();
        List<Operation> operations = new ArrayList<>();
        operations.add(new FilterOperation(imageFilter));
        operations.add(new CropOperation(polygon));

        return imageProcessor().processBitmap(bitmap, operations, false);
    }


    public File createPdf(final List<Uri> images, final PDFPageSize pageSize, final PdfSdk pdfSdk, boolean encrypted) {
        PDFRenderer pdfRenderer = pdfSdk.scanbotSDK.createPdfRenderer();

        return pdfRenderer.renderDocumentFromImages(images, encrypted, pageSize);
    }

    public File writeTiff(final List<Uri> images, final boolean binarized, final int dpi,
                          final TIFFImageWriterCompressionOptions compression, boolean sourceFilesEncrypted) throws IOException {
        final List<File> files = new ArrayList<>();
        for (final Uri uri : images) {
            files.add(new File(uri.getPath()));
        }

        final File tiffTargetFile = StorageUtils.generateRandomPluginStorageFile("tiff", this.context);

        final ImageFilterType filter = binarized ? ImageFilterType.PURE_BINARIZED : ImageFilterType.NONE;

        final TIFFImageWriterParameters parameters = new TIFFImageWriterParameters(filter, dpi, compression, new ArrayList<>());

        final TIFFWriter tiffWriter = sdk().createTiffWriter();
        tiffWriter.writeTIFFFromFiles(files, sourceFilesEncrypted, tiffTargetFile, parameters);
        return tiffTargetFile;
    }

    public Uri getFilteredDocumentPreviewUri(final Page page, final ImageFilterType filterType) throws IOException {
        final Uri filteredPreviewUri = pageFileStorage().getFilteredPreviewImageURI(page.getPageId(), filterType);
        if (!new File(filteredPreviewUri.getPath()).exists()) {
            pageProcessor().generateFilteredPreview(page, filterType);
        }
        return filteredPreviewUri;
    }

    public Page applyImageFilterOnPage(final Page page, final ImageFilterType filterType) throws IOException {
        return new ScanbotSDK((Activity) this.context).createPageProcessor().applyFilter(page, filterType);
    }

    public Page rotatePage(final Page page, final int times) throws IOException {
        return new ScanbotSDK((Activity) this.context).createPageProcessor().rotate(page, times);
    }

    public Page detectDocumentOnPage(final Page page) throws IOException {
        return new ScanbotSDK((Activity) this.context).createPageProcessor().detectDocument(page);
    }


    private void debugLog(final String msg) {
        LogUtils.debugLog(LOG_TAG, msg);
    }

    private void errorLog(final String msg) {
        LogUtils.errorLog(LOG_TAG, msg);
    }


    public static final class DocumentDetectionResult {
        public final DetectionResult sdkDetectionResult;
        public final List<PointF> polygon = new ArrayList<PointF>();
        public final Bitmap documentImage;

        public DocumentDetectionResult(final DetectionResult sdkDetectionResult,
                                       final List<PointF> polygon,
                                       final Bitmap documentImage) {
            this.sdkDetectionResult = sdkDetectionResult;
            if (polygon != null) {
                this.polygon.addAll(polygon);
            }
            this.documentImage = documentImage;
        }
    }


    public static final class PdfSdk {
        public final ScanbotSDK scanbotSDK;
        public final Cleaner sdkCleaner;
        public final BlobManager blobManager;
        public final BlobFactory blobFactory;

        public PdfSdk(final Activity activity) {
            this.scanbotSDK = new ScanbotSDK(activity);
            this.sdkCleaner = scanbotSDK.createCleaner();
            this.blobManager = scanbotSDK.createBlobManager();
            this.blobFactory = scanbotSDK.createBlobFactory();
        }
    }


}
