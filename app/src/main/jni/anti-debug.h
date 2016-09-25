//
// Created by 王力 on 9/23/16.
//

#ifndef ANTI_DEBUG_ANTI_DEBUG_H
#define ANTI_DEBUG_ANTI_DEBUG_H

#include <jni.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

static jstring getCString(JNIEnv* env, jobject obj);
static jint nativeLog(JNIEnv* env, jobject obj, jstring msg);

#ifdef __cplusplus
}
#endif

#endif //ANTI_DEBUG_ANTI_DEBUG_H
