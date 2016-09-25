//
// Created by 王力 on 9/24/16.
//

#ifndef ANTI_DEBUG_LOG_H
#define ANTI_DEBUG_LOG_H

#define NATIVE_TAG "Anti-Debug"
#define  LOGV(...) __ android_log_print(ANDROID_LOG_VERBOSE, NATIVE_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,NATIVE_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,NATIVE_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,NATIVE_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,NATIVE_TAG,__VA_ARGS__)

#endif //ANTI_DEBUG_LOG_H
