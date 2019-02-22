package com.example.sunbeam.gesturecontrolledrobot;

import android.content.Intent;
import android.util.Log;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

import org.json.JSONException;
import org.json.JSONObject;



public class MyFirebaseMessagingService extends FirebaseMessagingService {

    private static final String TAG = "MessagingService";

    public void onMessageReceived(RemoteMessage remoteMessage) {
        // ...

        // TODO(developer): Handle FCM messages here.
        // Not getting messages here? See why this may be: https://goo.gl/39bRNJ


        Log.d("MyFirebaseMsgingService", "From: " + remoteMessage.getFrom());

        // Check if message contains a data payload.
        if (remoteMessage.getData().size() > 0) {

            try {
                Log.e(TAG, "Message data payload: " + remoteMessage.getData());
                String data = remoteMessage.getData().toString();
                JSONObject info = new JSONObject(data);
                String value = info.getString("value");

                Log.e(TAG, "Value ID: " + data);

                Intent intent = new Intent();
                intent.setAction("com.example.sunbeam.gesturecontrolledrobot.CART_DIRECTION_CHANGED");
                intent.putExtra("value", value);

                // send the intent to all the applications installed on the device
                sendBroadcast(intent);

            } catch (JSONException e) {
                e.printStackTrace();
            }


        }
    }
}