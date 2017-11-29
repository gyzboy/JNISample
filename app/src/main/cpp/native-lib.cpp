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
    LOG("%d", castIntTest());
    TESTJNI *testjni = new TESTJNI();
    testjni->testJNI();
    return result;
}

int castIntTest() {
    return 10;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonThree(JNIEnv *env, jclass type,
                                                               jint size) {
    jobjectArray result;
    jclass clsIntArray;
    jint i, j;

    clsIntArray = (*env).FindClass("[I");
    if (clsIntArray == NULL) {
        return NULL;
    }
    result = (*env).NewObjectArray(size, clsIntArray, NULL);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size; ++i) {
        jint buff[256];
        jintArray intArr = (*env).NewIntArray(size);
        if (intArr == NULL) {
            return NULL;
        }
        for (j = 0; j < size; ++j) {
            buff[j] = i + j;
        }
        (*env).SetIntArrayRegion(intArr, 0, size, buff);
        (*env).SetObjectArrayElement(result, i, intArr);
        (*env).DeleteLocalRef(intArr);
    }
    (*env).DeleteLocalRef(clsIntArray);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonTwo(JNIEnv *env, jclass type,
                                                             jstring string) {

    LOG("a = %d", aa);
    LOG("bb = %d", bb);

    TEST_VAL *testval = new TEST_VAL(env, string);
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
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jcharArray JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_LessonFour(JNIEnv *env, jclass type,
                                                              jcharArray origin_) {
    jchar *origin = env->GetCharArrayElements(origin_, NULL);
    char c[2] = {'4', '5'};
    jsize size = env->GetArrayLength(origin_);
    for (int i = 0; i < size; ++i) {
        origin[i] = 'C';
    }

    env->ReleaseCharArrayElements(origin_, origin, 1);//最后一个标志是否将更改后的元素复制到原数组中
    jcharArray array = env->NewCharArray(size);
    env->SetCharArrayRegion(array, 0, size, origin);
    return origin_;
}extern "C"
JNIEXPORT void JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_InterfaceTest(JNIEnv *env, jclass type,
                                                                 jobject callback) {

//    jobject obj = env->GetObjectClass(test);
//生成一个全局引用，回调的时候findclass才不会为null
//    jobject callback = env->NewGlobalRef(jcallback);

    LOG("start");
    //通过强转后的jcallback 获取到要回调的类
    jclass javaClass = env->GetObjectClass(callback);
    if (javaClass == 0) {
        LOG("Unable to find class");
        return;
    }
    LOG("method");
    //获取要回调的方法ID
    jmethodID javaCallbackId = env->GetMethodID(javaClass,
                                                "getInfo", "(Ljava/lang/String;)V");//函数名称,()里为传入参数,V为返回值
    if (javaCallbackId == NULL) {
        LOG("Unable to find method:onProgressCallBack");
        return;
    }

    LOG("call method");
    jstring str = env->NewStringUTF("hello interface");
    env->CallVoidMethod(callback, javaCallbackId, str);//根据不同的返回值调用不同的Call方法
//    env->DeleteGlobalRef(callback);

}