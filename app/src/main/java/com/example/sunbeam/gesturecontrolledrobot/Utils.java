package com.example.sunbeam.gesturecontrolledrobot;

public class Utils {

    public static String createURL(String api) {
        return String.format("%s/%s", Constants.SERVER_URL, api);
    }

    public static String createExpressURL(String api) {
        return String.format("%s/%s", Constants.EXPRESS_SERVER_URL, api);
    }
}