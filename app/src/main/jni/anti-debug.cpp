//
// Created by 王力 on 9/23/16.
//

#include "anti-debug.h"
#include "log.h"

#define CLASSNAME "com/learning/anti_debug/NativeUtil"

static void anti_debug(void) __attribute__((constructor));

//void* be_timeout_check(){
//    time_t ts;
//    time(&ts);
//    pid_t pid = getpid();
//    while(true) {
//        time_t ts_now;
//        time(&ts_now);
//        double diff = difftime(ts_now, ts);
//        if(diff > 10.0){
//            LOGD("Timeout! Kill process: %d", pid);
//            kill(pid, SIGKILL);
//        }
//        sleep(2);
//    }
//}

void be_attached_check(){
    try {
        const int bufsize = 1024;
        char filename[bufsize];
        char line[bufsize];
        pid_t pid = getpid();
        sprintf(filename, "/proc/%d/status", pid);
        FILE* fd = fopen(filename, "r");
        if(fd != NULL) {
            while (fgets(line, bufsize, fd)) {
                LOGD("%s", line);
                if (strncmp(line, "TracerPid", 9) == 0) {
                    int statue = atoi(&line[10]);
                    if (statue != 0) {
                        LOGD("Be attached!!! kill %d", pid);
                        fclose(fd);
                        kill(pid, SIGKILL);
                    }
                    break;
                }
            }
            fclose(fd);
        } else {

        }
    } catch (...){

    }
}

void* task_thread(void* val) {
    long timeval = (long)val;
    LOGD("The time val is %d", timeval);
    while (true) {
        LOGD("Start be_attached_check...");
        be_attached_check();
//        sleep(val);
        sleep(timeval);
    }
}

static void anti_debug() {
    pthread_t id;
    long timeval = 10;
    LOGD("Call anti debug...");
    if(pthread_create(&id, NULL, (void *(*)(void *))&task_thread, (void *)timeval) != 0) {
        LOGE("Failed to create a debug checking thread!");
        exit(-1);
    };
//    if(pthread_create(&id, NULL, (void *(*)(void *))&be_timeout_check, (void *)timeval) != 0) {
//        LOGE("Failed to create a debug checking thread!");
//        exit(-1);
//    }
    pthread_detach(id);
}

static jstring getCString(JNIEnv* env, jobject obj) {
    return env->NewStringUTF("Hello from native layer!!!");
}

static jint nativeLog(JNIEnv* env, jobject obj, jstring msg) {
    jclass class_Log;
    class_Log = env->FindClass("android/util/Log");

    assert(class_Log != NULL);

    jmethodID idV = env->GetStaticMethodID(class_Log, "v", "(Ljava/lang/String;Ljava/lang/String;)I");
//    LOGV("Call Log.v failed?\n");
    jint ret = env->CallStaticIntMethod(class_Log, idV, env->NewStringUTF(NATIVE_TAG), msg);

    return ret;
}

static JNINativeMethod gMethods[] = {
        {"getCString", "()Ljava/lang/String;", (void*)getCString},
        {"nativeLog", "(Ljava/lang/String;)I", (void*)nativeLog},
};

static int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods,
                                 int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);

    if(clazz == NULL)
        return JNI_FALSE;

    if(env->RegisterNatives(clazz, gMethods, numMethods) < 0)
        return JNI_FALSE;

    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env) {

    if(!registerNativeMethods(env, CLASSNAME, gMethods, sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    anti_debug();

    JNIEnv *env = NULL;
    jint result = JNI_ERR;

    if(vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
        return result;

    assert(env != NULL);

    if(!registerNatives(env)) {
        LOGE("Register native methods failed!");
        return result;
    }

    return JNI_VERSION_1_6;
}