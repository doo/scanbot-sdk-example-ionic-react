/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova.utils;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.net.Uri;
import android.media.ExifInterface;

import java.io.IOException;
import java.io.File;

import io.scanbot.sdk.util.FileChooserUtils;
import io.scanbot.sdk.util.bitmap.BitmapUtils;

public final class ImageUtils {

    /**
     * Default JPG image quality
     */
    public static final int JPEG_QUALITY = 80;

    private ImageUtils() {
    }

    public static Bitmap loadImage(final String imageFilePath) {
        return BitmapUtils.decodeQuietly(imageFilePath, null);
    }

    public static Bitmap loadImage(final Uri imageUri, final Context context) throws IOException {
        final String filePath = FileChooserUtils.getPath(context, imageUri);

        if (filePath == null) {
            throw new IOException("Invalid/unsupported image file URI: " + imageUri);
        }

        if (!new File(filePath).exists()) {
            throw new IOException("File does not exist: " + filePath);
        }

        return loadImage(filePath);
    }


    public static Bitmap resizeImage(final Bitmap originalImage, final float width, final float height) {
        final float oldWidth = originalImage.getWidth();
        final float oldHeight = originalImage.getHeight();

        final float scaleFactor;
        if (oldWidth > oldHeight) {
            scaleFactor = width / oldWidth;
        } else {
            scaleFactor = height / oldHeight;
        }

        final float newHeight = oldHeight * scaleFactor;
        final float newWidth = oldWidth * scaleFactor;

        return Bitmap.createScaledBitmap(originalImage, (int) newWidth, (int) newHeight, false);
    }

    public static Bitmap rotateBitmap(Bitmap source, int degrees) {
        Matrix matrix = new Matrix();
        matrix.postRotate(degrees);
        return Bitmap.createBitmap(source, 0, 0, source.getWidth(), source.getHeight(), matrix, true);
    }

    public static Bitmap prepareImageForImport(final Uri imageUri, final Context context) throws IOException {
        final String imagePath = FileChooserUtils.getPath(context, imageUri);
        final ExifInterface exif = new ExifInterface(imagePath);
        final Bitmap bitmap = loadImage(imagePath);
        final int exifOrientation = exif.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);
        final int rotationInDegrees = exifToDegrees(exifOrientation);
        final Matrix matrix = new Matrix();
        if (exifOrientation != 0) {
            matrix.preRotate(rotationInDegrees);
            return Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), matrix, false);
        }
        return bitmap;
    }

    private static int exifToDegrees(final int exifOrientation) {
        switch (exifOrientation) {
            case ExifInterface.ORIENTATION_ROTATE_90: return 90;
            case ExifInterface.ORIENTATION_ROTATE_180: return 180;
            case ExifInterface.ORIENTATION_ROTATE_270: return 270;
            default: return 0;
        }
    }

}
