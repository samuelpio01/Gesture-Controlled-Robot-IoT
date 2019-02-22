package com.example.sunbeam.gesturecontrolledrobot;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.koushikdutta.async.future.FutureCallback;
import com.koushikdutta.ion.Ion;


public class Control extends AppCompatActivity {

    ImageView lastActionView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        setTitle("Control Activity");
        lastActionView = findViewById(R.id.lastAction);

        BroadcastReceiver receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {

               String value =intent.getStringExtra("value");
               Log.e("Broadcast Rx","Value (int) = "+value);


                if (value.equals("0")) {

                    lastActionView.setImageResource(R.drawable.default_stop);
                    //Toast.makeText(Control.this, "Last action = Stop", Toast.LENGTH_SHORT).show();

                } else if (value.equals("1")) {

                    lastActionView.setImageResource(R.drawable.default_forward);
                    //Toast.makeText(Control.this, "Last action = Forward", Toast.LENGTH_SHORT).show();

                } else if (value.equals("2")) {

                    lastActionView.setImageResource(R.drawable.default_backward);
                    //Toast.makeText(Control.this, "Last action = Reverse", Toast.LENGTH_SHORT).show();

                } else if (value.equals("3")) {

                    lastActionView.setImageResource(R.drawable.default_left);
                   // Toast.makeText(Control.this, "Last action = Left", Toast.LENGTH_SHORT).show();

                } else if (value.equals("4")) {

                    lastActionView.setImageResource(R.drawable.default_right);
                   // Toast.makeText(Control.this, "Last action = Right", Toast.LENGTH_SHORT).show();
                }

            }


        };

        // will be used to filter the intent based on the action
        IntentFilter intentFilter = new IntentFilter("com.example.sunbeam.gesturecontrolledrobot.CART_DIRECTION_CHANGED");

        // register a receiver for a filter (action)
        registerReceiver(receiver, intentFilter);


    }
// http://172.x.x.x:80/cart/0,1,2,3,4

    public void button_forward(View v){
        String url = Utils.createExpressURL(Constants.API_FORWARD);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()

                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        Log.e("Action","Moving in forward direction");
                        Toast.makeText(Control.this, "Moving in Forward Direction", Toast.LENGTH_SHORT).show();
                    }
                });
    }

    public void button_backward(View v){
        String url = Utils.createExpressURL(Constants.API_BACKWARD);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()
                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        Log.e("Action","Moving in reverse direction");
                     Toast.makeText(Control.this, "Moving in Reverse Direction", Toast.LENGTH_SHORT).show();
                    }
                });
    }


    public void button_left(View v){
        String url = Utils.createExpressURL(Constants.API_LEFT);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()
                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        Log.e("Action","Taking a left turn");
                       Toast.makeText(Control.this, "Taking a Left turn", Toast.LENGTH_SHORT).show();
                    }
                });
    }

    public void button_right(View v){
        String url = Utils.createExpressURL(Constants.API_RIGHT);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()
                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        Log.e("Action","Taking a right turn");
                        Toast.makeText(Control.this, "Taking a Right turn", Toast.LENGTH_SHORT).show();
                    }
                });
    }

    public void button_stop(View v){
        String url = Utils.createExpressURL(Constants.API_STOP);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()
                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        Log.e("Action","Stop");
                        Toast.makeText(Control.this, "STOP", Toast.LENGTH_SHORT).show();
                    }
                });
    }

    public void onRefresh(View v) {
        String url = Utils.createExpressURL(Constants.API_GET);
        Ion.with(this)
                .load("GET", url)
                .asJsonObject()
                .setCallback(new FutureCallback<JsonObject>() {
                    @Override
                    public void onCompleted(Exception e, JsonObject result) {
                        if (e == null) {
                            JsonArray myarray = result.get("data").getAsJsonArray();
                            JsonObject myobject = (JsonObject) myarray.get(0);
                            Log.e("My result", "" + myobject.get("value"));

                            int val = Integer.parseInt("" + myobject.get("value"));
                            Log.e("Integer value", "" + val);

                            if (val == 0) {
                                lastActionView.setImageResource(R.drawable.default_stop);
                                Toast.makeText(Control.this, "Last action = Stop", Toast.LENGTH_SHORT).show();
                            } else if (val == 1) {
                                lastActionView.setImageResource(R.drawable.default_forward);
                                Toast.makeText(Control.this, "Last action = Forward", Toast.LENGTH_SHORT).show();
                            } else if (val == 2) {
                                lastActionView.setImageResource(R.drawable.default_backward);
                                Toast.makeText(Control.this, "Last action = Reverse", Toast.LENGTH_SHORT).show();
                            } else if (val == 3) {
                                lastActionView.setImageResource(R.drawable.default_left);
                                Toast.makeText(Control.this, "Last action = Left", Toast.LENGTH_SHORT).show();
                            } else if (val == 4) {
                                lastActionView.setImageResource(R.drawable.default_right);
                                Toast.makeText(Control.this, "Last action = Right", Toast.LENGTH_SHORT).show();
                            }
                        }
                    }
                });
    }

}

