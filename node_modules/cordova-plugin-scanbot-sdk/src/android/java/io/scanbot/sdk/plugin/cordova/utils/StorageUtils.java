/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova.utils;


import android.app.Activity;
import android.content.Context;
import android.net.Uri;

import org.apache.cordova.LOG;

import java.io.*;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

public final class StorageUtils {

    private static final String LOG_TAG = StorageUtils.class.getSimpleName();

    private static File customStorageBaseDirectory = null;
    private static final String PLUGIN_STORAGE_SUB_DIR = "sbsdk-plugin-storage";

    private StorageUtils() {
    }


    public static synchronized void setCustomStorageBaseDirectory(final File dir) {
        customStorageBaseDirectory = dir;
    }


    private static File getPluginStorageBaseDirectory(final Context context) throws IOException {
        final File pluginStorageDir;
        if (customStorageBaseDirectory != null) {
            pluginStorageDir = new File(customStorageBaseDirectory, PLUGIN_STORAGE_SUB_DIR);
        } else {
            pluginStorageDir = new File(context.getFilesDir(), PLUGIN_STORAGE_SUB_DIR);
        }

        pluginStorageDir.mkdirs();
        if (!pluginStorageDir.isDirectory()) {
            throw new IOException("Could not create/get plugin storage directory: " + pluginStorageDir.getAbsolutePath());
        }
        return pluginStorageDir;
    }


    public static File generateRandomPluginStorageFile(final String extension, final Context context) throws IOException {
        final String imageFileName = UUID.randomUUID().toString() + "." + extension;
        return new File(getPluginStorageBaseDirectory(context), imageFileName);
    }


    public static void cleanupPluginStorageDirectory(final Activity activity) throws IOException {
        final File dir = getPluginStorageBaseDirectory(activity);
        LOG.d(LOG_TAG, "Deleting content of the plugin storage directory: " + dir.getAbsolutePath());
        cleanDirectory(dir);
    }


    public static void copyFile(final File source, final File target) throws IOException {
        final InputStream in = new FileInputStream(source);
        final OutputStream out = new FileOutputStream(target);
        byte[] buf = new byte[1024];
        int len;
        while ((len = in.read(buf)) > 0) {
            out.write(buf, 0, len);
        }
        in.close();
        out.close();
    }

    public static String uriWithHash(String fileUriStr) {
        if (fileUriStr == null || "".equals(fileUriStr)) {
            return fileUriStr;
        }

        Uri fileUri = Uri.parse(fileUriStr);
        String path = fileUri.getPath();
        File file = new File(path);
        RandomAccessFile fileReader = null;
        try {
            MessageDigest digest = MessageDigest.getInstance("MD5");
            ByteBuffer lengthBuffer = ByteBuffer.allocate(8);
            long length = file.length();
            lengthBuffer.putLong(length);
            digest.update(lengthBuffer.array());
            fileReader = new RandomAccessFile(file, "r");
            byte[] buffer = new byte[32768];
            if (length > buffer.length) {
                fileReader.seek((length - buffer.length) / 2);
            }
            fileReader.read(buffer);
            digest.update(buffer);
            String hash = new BigInteger(1, digest.digest()).toString(16);
            return fileUri.buildUpon().appendQueryParameter("minihash", hash).build().toString();
        } catch (NoSuchAlgorithmException e) {
            LogUtils.debugLog(LOG_TAG, e.toString());
        } catch (FileNotFoundException e) {
            LogUtils.debugLog(LOG_TAG, e.toString());
        } catch (IOException e) {
            LogUtils.debugLog(LOG_TAG, e.toString());
        } finally {
            if (fileReader != null) {
                try {
                    fileReader.close();
                } catch (IOException e) {
                    LogUtils.debugLog(LOG_TAG, e.toString());
                }
            }
        }
        return fileUri.toString();
    }

    private static void cleanDirectory(final File directory) throws IOException {
        final File[] files = verifiedListFiles(directory);

        IOException exception = null;
        for (final File file : files) {
            try {
                forceDelete(file);
            } catch (final IOException ioe) {
                exception = ioe;
            }
        }

        if (null != exception) {
            throw exception;
        }
    }

    private static File[] verifiedListFiles(File directory) throws IOException {
        if (!directory.exists()) {
            final String message = directory + " does not exist";
            throw new IllegalArgumentException(message);
        }

        if (!directory.isDirectory()) {
            final String message = directory + " is not a directory";
            throw new IllegalArgumentException(message);
        }

        final File[] files = directory.listFiles();
        if (files == null) {  // null if security restricted
            throw new IOException("Failed to list contents of " + directory);
        }
        return files;
    }

    private static void forceDelete(final File file) throws IOException {
        if (file.isDirectory()) {
            deleteDirectory(file);
        } else {
            final boolean filePresent = file.exists();
            if (!file.delete()) {
                if (!filePresent) {
                    throw new FileNotFoundException("File does not exist: " + file);
                }
                throw new IOException("Could not delete file: " + file);
            }
        }
    }

    private static void deleteDirectory(final File directory) throws IOException {
        if (!directory.exists()) {
            return;
        }

        cleanDirectory(directory);

        if (!directory.delete()) {
            throw new IOException("Could not delete directory: " + directory);
        }
    }
}
