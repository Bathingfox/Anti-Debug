package com.learning.anti_debug;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        NativeUtil nativeUtil = new NativeUtil();
        TextView textView = (TextView) findViewById(R.id.show);
        textView.setText(nativeUtil.getCString());
        nativeUtil.nativeLog("Get a string from native!");
    }
}
