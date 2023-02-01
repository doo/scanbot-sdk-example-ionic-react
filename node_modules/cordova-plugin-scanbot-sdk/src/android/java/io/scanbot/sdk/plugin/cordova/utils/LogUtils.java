/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2017 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova.utils;

import org.apache.cordova.LOG;


public final class LogUtils {

    // global static loggingEnabled flag (set on ScanbotSdkPlugin.initializeSdk(..))
    private static boolean loggingEnabled = false;

    private LogUtils() {}


    public static synchronized void setLoggingEnabled(final boolean flag) {
        loggingEnabled = flag;
    }

    public static synchronized boolean isLoggingEnabled() {
        return loggingEnabled;
    }


    public static void debugLog(final String logTag, final String msg) {
        if (loggingEnabled) {
            LOG.d(logTag, msg);
        }
    }

    public static void errorLog(final String logTag, final String msg) {
        LOG.e(logTag, msg);
    }

    public static void errorLog(final String logTag, final String msg, final Throwable e) {
        LOG.e(logTag, msg, e);
    }

}
