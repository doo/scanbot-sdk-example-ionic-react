/*
    Scanbot SDK Cordova Plugin

    Copyright (c) 2019 doo GmbH. All rights reserved.
 */
package io.scanbot.sdk.plugin.cordova.utils;

import android.graphics.Color;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import io.scanbot.sdk.ui.camera.FinderAspectRatio;

public final class ObjectMapper {
    private static Map<String, Map<String, Method>> methodCache = new HashMap<String, Map<String, Method>>();

    /*
     *  Properties listed here will be skipped by the Object Mapper
     */
    private final static String[] kIgnoredProperties = new String[]{
            "engineMode",
            "barcodeFilter"
    };

    private final static HashMap<String, String> kRenamePropertiesMap = new HashMap<String, String>() {{
        put("interfaceOrientation", "orientationLockMode");
    }};

    public static void map(final JSONObject source, final Object target)
            throws IllegalAccessException, InvocationTargetException, JSONException {
        map(toMap(source), target);
    }

    @SuppressWarnings("unchecked")
    private static void map(final Map<String, Object> source, final Object target)
            throws IllegalAccessException, InvocationTargetException {
        final Class cls = target.getClass();

        final Map<String, Method> methodMap;
        if (!methodCache.containsKey(cls.getName())) {
            methodMap = new HashMap<String, Method>();
            methodCache.put(cls.getName(), methodMap);

            final Method[] methods = cls.getMethods();
            for (final Method m : methods) {
                methodMap.put(m.getName(), m);
            }
        } else {
            methodMap = methodCache.get(cls.getName());
        }

        if (methodMap == null) {
            throw new IllegalAccessException("Internal error. methodMap is null");
        }

        for (HashMap.Entry<String, Object> entry : source.entrySet()) {
            String prop = entry.getKey();
            Object value = entry.getValue();
            if (value == null) {
                continue;
            }

            if (shouldIgnoreProperty(prop)) {
                continue;
            }

            prop = renamePropertyIfNeeded(prop);

            // Android has no orientationMode like ALL, so we are skipping this property when 'ALL'
            if (prop.equals("orientationLockMode") && value.equals("ALL")) {
                continue;
            }

            final String setterName = "set" + prop.substring(0, 1).toUpperCase() + prop.substring(1);

            // The default FRONT camera module should be FRONT_MIRRORED on Android
            if (prop.equals("cameraModule") && value.equals("FRONT")) {
                value = "FRONT_MIRRORED";
            }

            if (methodMap.containsKey(setterName)) {
                final Method setter = methodMap.get(setterName);

                if (setter == null) {
                    throw new IllegalAccessException("Internal error. Setter method not found: " + setterName);
                }

                if (setterName.equals("setFinderAspectRatio")) {
                    Map<String, Object> pointMap = (Map<String, Object>) value;
                    int x = ((Number) pointMap.get("width")).intValue();
                    int y = ((Number) pointMap.get("height")).intValue();
                    setter.invoke(target, new FinderAspectRatio(x, y));
                } else if (setter.getParameterTypes().length == 2 && value instanceof Map) {
                    // map Size to a binary function
                    Map<String, Object> pointMap = (Map<String, Object>) value;
                    int x = ((Number) pointMap.get("width")).intValue();
                    int y = ((Number) pointMap.get("height")).intValue();
                    setter.invoke(target, x, y);
                } else {
                    final Class paramType = setter.getParameterTypes()[0];
                    if (setterName.contains("Color")) {
                        value = Color.parseColor((String) value);
                    } else if (paramType == int.class) {
                        value = ((Number) value).intValue();
                    } else if (paramType == float.class) {
                        value = ((Number) value).floatValue();
                    } else if (paramType == double.class) {
                        value = ((Number) value).doubleValue();
                    } else if (paramType.isEnum()) {
                        try {
                            value = Enum.valueOf(paramType, (String) value);
                        } catch (Exception ignored) {
                            // If the enum cannot be mapped properly, the property will not be set
                            return;
                        }
                    }

                    setter.invoke(target, value);
                }

                //usedProperties.add(prop);
            }
        }

        //return usedProperties.toArray(new String[0]);
    }

    private static Map<String, Object> toMap(JSONObject object) throws JSONException {
        Map<String, Object> map = new HashMap<String, Object>();

        Iterator<String> keysItr = object.keys();
        while (keysItr.hasNext()) {
            String key = keysItr.next();
            Object value = object.get(key);

            if (value instanceof JSONArray) {
                value = toList((JSONArray) value);
            } else if (value instanceof JSONObject) {
                value = toMap((JSONObject) value);
            }
            map.put(key, value);
        }
        return map;
    }

    private static List<Object> toList(JSONArray array) throws JSONException {
        List<Object> list = new ArrayList<Object>();
        for (int i = 0; i < array.length(); i++) {
            Object value = array.get(i);
            if (value instanceof JSONArray) {
                value = toList((JSONArray) value);
            } else if (value instanceof JSONObject) {
                value = toMap((JSONObject) value);
            }
            list.add(value);
        }
        return list;
    }

    private static boolean shouldIgnoreProperty(final String propertyKey) {
        for (String property : kIgnoredProperties) {
            if (property.equals(propertyKey)) {
                return true;
            }
        }
        return false;
    }

    private static String renamePropertyIfNeeded(final String propertyKey) {
        if (kRenamePropertiesMap.containsKey(propertyKey)) {
            return kRenamePropertiesMap.get(propertyKey);
        }
        return propertyKey;
    }
}
