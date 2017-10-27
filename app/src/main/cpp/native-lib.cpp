#include <jni.h>
#include <string>

#include<android/log.h>
#include "testHeader.h"
#include "testVal.h"

int castIntTest();

extern int testValInt;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonOne(JNIEnv *env, jclass type) {
    char msg[60] = "hello jni";
    jstring result;
    result = (*env).NewStringUTF(msg);
    LOG("%d",castIntTest());
    TESTJNI *testjni = new TESTJNI();
    testjni->testJNI();
    return result;
}

int castIntTest(){
    return 10;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonThree(JNIEnv *env, jclass type,
                                                               jint size) {
    jobjectArray result;
    jclass clsIntArray;
    jint i,j;

    clsIntArray = (*env).FindClass("[I");
    if(clsIntArray == NULL){
        return NULL;
    }
    result = (*env).NewObjectArray(size,clsIntArray,NULL);
    if(result == NULL){
        return NULL;
    }

    for (i = 0; i < size; ++i) {
        jint buff[256];
        jintArray intArr = (*env).NewIntArray(size);
        if(intArr == NULL){
            return NULL;
        }
        for (j = 0; j < size; ++j) {
            buff[j] = i + j;
        }
        (*env).SetIntArrayRegion(intArr,0,size,buff);
        (*env).SetObjectArrayElement(result,i,intArr);
        (*env).DeleteLocalRef(intArr);
    }
    (*env).DeleteLocalRef(clsIntArray);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonTwo(JNIEnv *env,jclass type, jstring string    ) {

    LOG("a = %d",aa);
    LOG("bb = %d",bb);

    TEST_VAL *testval = new TEST_VAL(env,string);
    testval->getVal(env);
    testValInt = 50;


    return env->NewStringUTF("LessonTwo");
}

int testValInt = 10;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_megvii_guoyizhe_jnisamples_MainActivity_sayHello(JNIEnv *env, jobject instance) {
    return env->NewStringUTF("hello");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_megvii_guoyizhe_jnisamples_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
