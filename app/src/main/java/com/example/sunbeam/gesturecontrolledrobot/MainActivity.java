package com.example.sunbeam.gesturecontrolledrobot;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onNext(View view) {
        Intent intent= new Intent(this,Control.class);
        startActivity(intent);
    }

    public void onClose(View view) {
        finishAffinity();
    }
}
