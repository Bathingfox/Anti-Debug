package com.learning.anti_debug;

/**
 * Created by wangli on 9/23/16.
 */

public class NativeUtil {
    static {
        System.loadLibrary("anti-debug");
    }

    public native String getCString();
    public native int nativeLog(String msg);
}
