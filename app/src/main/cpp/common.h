//
// Created by Guo Yizhe on 2017/10/21.
//

#ifndef JNISAMPLES_COMMON_H
#define JNISAMPLES_COMMON_H

#endif //JNISAMPLES_COMMON_H

#include<android/log.h>
#define TAG "JNISample"
#define LOGOPEN  1
#if(LOGOPEN == 1)
    #define LOG(...) __android_log_print(ANDROID_LOG_VERBOSE,TAG,__VA_ARGS__)
#else
    #define LOG(...) NULL
#endif