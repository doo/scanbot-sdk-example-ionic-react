package io.scanbot.sdk.plugin.cordova;

import org.apache.cordova.CallbackContext;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import android.os.Environment;

import io.scanbot.sdk.plugin.cordova.utils.JsonUtils;

public class ScanbotSdkTest extends ScanbotCordovaPluginBase {

    @Override
    protected String getLogTag() {
        return ScanbotSdkTest.class.getSimpleName();
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        System.out.println(action);

        if ("saveFile".equals(action)) {

            final JSONObject jsonArgs = (args.length() > 0 ? args.getJSONObject(0) : new JSONObject());
            String url = JsonUtils.getJsonArg(jsonArgs, "url", null);
            String token = JsonUtils.getJsonArg(jsonArgs, "token", null);
            String path = save(url, token);

            JSONObject result = new JSONObject();
            result.put("path", path);
            callbackContext.success(result);
        }

        return true;
    }

    private String save(String source, String token) {
        String folder = "/storage/emulated/0/Download/tests/";

        File check = new File(folder);
        boolean created = check.mkdirs();
        if (created) {
            System.out.println("External files directory did not exist. Now it does");
        } else {
            System.out.println("External files directory already exists, nothing to create");
        }

        String[] split = source.split("/");
        String filename = split[split.length - 1];

        try {
            File f3 = new File(folder);
            if (!f3.exists()) {
                f3.mkdirs();
            }
            URL url = new URL(source);

            HttpURLConnection httpConn = (HttpURLConnection) url.openConnection();
            httpConn.setRequestProperty("Authorization", String.format("token %s", token));

            // opens input stream from the HTTP connection
            InputStream inputStream = httpConn.getInputStream();

            // opens an output stream to save into file
            FileOutputStream outputStream = new FileOutputStream(new File(folder + filename));

            int bytesRead = -1;
            byte[] buffer = new byte[1024];
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            outputStream.close();
            inputStream.close();

            httpConn.disconnect();

            return "file://" + folder + filename;

        } catch (MalformedURLException mue) {
            System.out.println("Malformed URL");
            return null;
        } catch (IOException ioe) {
            System.out.println("IO");
            return null;
        } catch (SecurityException se) {
            System.out.println("Security");
            return null;
        }
    }
}