package io.scanbot.sdk.plugin.cordova;

import io.scanbot.sdk.persistence.CameraImageFormat;
import io.scanbot.sdk.persistence.fileio.AESEncryptedFileIOProcessor;

public class ScanbotSdkConfiguration {
    private boolean loggingEnabled = false;
    private boolean enableNativeLogging = false;
    private String licenseKey;
    private int storageImageQuality = 80;
    private CameraImageFormat storageImageFormat = CameraImageFormat.JPG;
    private String storageBaseDirectory = null;
    private String documentDetectorMode = null;
    private String fileEncryptionPassword = null;
    private AESEncryptedFileIOProcessor.AESEncrypterMode fileEncryptionMode
            = AESEncryptedFileIOProcessor.AESEncrypterMode.AES256;
    private boolean useCameraX = false;
    private boolean allowXnnpackAcceleration = true;
    private boolean allowGpuAcceleration = true;


    public boolean isLoggingEnabled() {
        return loggingEnabled;
    }

    public void setLoggingEnabled(boolean loggingEnabled) {
        this.loggingEnabled = loggingEnabled;
    }

    public String getLicenseKey() {
        return licenseKey;
    }

    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }

    public String getDocumentDetectorMode() {
        return documentDetectorMode;
    }

    public void setDocumentDetectorMode(String documentDetectorMode) {
        this.documentDetectorMode = documentDetectorMode;
    }

    public int getStorageImageQuality() {
        return storageImageQuality;
    }

    public void setStorageImageQuality(int storageImageQuality) {
        if (storageImageQuality > 100) {
            storageImageQuality = 100;
        } else if (storageImageQuality < 1) {
            storageImageQuality = 1;
        }
        this.storageImageQuality = storageImageQuality;
    }

    public CameraImageFormat getStorageImageFormat() {
        return storageImageFormat;
    }

    public void setStorageImageFormat(CameraImageFormat storageImageFormat) {
        this.storageImageFormat = storageImageFormat;
    }

    public String getStorageBaseDirectory() {
        return storageBaseDirectory;
    }

    public void setStorageBaseDirectory(String storageBaseDirectory) {
        this.storageBaseDirectory = storageBaseDirectory;
    }

    public Boolean encryptImages() {
        return getFileEncryptionPassword() != null && !"".equals(getFileEncryptionPassword());
    }

    public AESEncryptedFileIOProcessor encryptionProcessor() {
        return new AESEncryptedFileIOProcessor(getFileEncryptionPassword(), getFileEncryptionMode());
    }

    public String getFileEncryptionPassword() {
        return fileEncryptionPassword;
    }

    public void setFileEncryptionPassword(String fileEncryptionPassword) {
        this.fileEncryptionPassword = fileEncryptionPassword;
    }

    public AESEncryptedFileIOProcessor.AESEncrypterMode getFileEncryptionMode() {
        return fileEncryptionMode;
    }

    public void setFileEncryptionMode(AESEncryptedFileIOProcessor.AESEncrypterMode fileEncryptionMode) {
        this.fileEncryptionMode = fileEncryptionMode;
    }

    public boolean getUseCameraX() {
        return useCameraX;
    }

    public void setUseCameraX(boolean useCameraX) {
        this.useCameraX = useCameraX;
    }

    public boolean getAllowXnnpackAcceleration() {
        return allowXnnpackAcceleration;
    }

    public void setAllowXnnpackAcceleration(boolean allowXnnpackAcceleration) {
        this.allowXnnpackAcceleration = allowXnnpackAcceleration;
    }

    public boolean getAllowGpuAcceleration() {
        return allowGpuAcceleration;
    }

    public void setAllowGpuAcceleration(boolean allowGpuAcceleration) {
        this.allowGpuAcceleration = allowGpuAcceleration;
    }

    public boolean getEnableNativeLogging() {
        return enableNativeLogging;
    }

    public void setEnableNativeLogging(boolean enableNativeLogging) {
        this.enableNativeLogging = enableNativeLogging;
    }
}
