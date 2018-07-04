#include <jni.h>
#include <string>

#include<android/log.h>
#include "testHeader.h"
#include "testVal.h"

#include<pthread.h>
#include<unistd.h>

#include <iostream>
#include <fstream>
using namespace std;

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

    LOG("%p",&string);

    jboolean issCopy = JNI_FALSE;
    char *str = (char *) env->GetStringUTFChars(string, &issCopy);
    str[0] = 'D';
    LOG("%s",str);
    LOG("%p",str);

    jboolean isCopy = JNI_TRUE;
    char *string1 = (char *)env->GetStringUTFChars(string,&isCopy);
    string1[1] = 'Z';
    LOG("%s",string1);
    LOG("%p",string1);
    jstring returnValue = env->NewStringUTF(str);

    return returnValue;
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
        LOG("%c",origin[i]);
    }

    jint length = env->GetArrayLength(origin_);
    jchar chars[length];
    env->GetCharArrayRegion(origin_,0,length,chars);
    for (int i = 0; i < length; ++i) {
        LOG("%c",chars[i]);
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
//线程数
#define NUMTHREAD  5
//全局变量
JavaVM *g_jvm = NULL;
jobject g_obj = NULL;

JavaVM* gJvm = nullptr;
static jobject gClassLoader;
static jmethodID gFindClassMethod;


jclass findClass(JNIEnv *env, const char* name) {
    jclass result = nullptr;
    if (env)
    {
        //这句会出错，所以要处理错误
        result = env->FindClass(name);
        jthrowable exception = env->ExceptionOccurred();
        if (exception)
        {
            env->ExceptionClear();
            return static_cast<jclass>(env->CallObjectMethod(gClassLoader, gFindClassMethod, env->NewStringUTF(name)));
        }
    }
    return result;
}

JNIEnv* getEnv() {
    JNIEnv *env;
    int status = gJvm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if(status < 0) {
        status = gJvm->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            return nullptr;
        }
    }
    return env;
}

void *thread_fun(void *arg){
    JNIEnv *env;
    jclass cls;
    jmethodID mid;
    int mNeedDetach = 0;
    

//    int getEnvStat = g_jvm->GetEnv((void **)&env,JNI_VERSION_1_6);
//    if (getEnvStat == JNI_EDETACHED) {
//        //如果没有， 主动附加到jvm环境中，获取到env
//        if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
//            return NULL;
//        }
//        mNeedDetach = JNI_TRUE;
//    }

    LOG("tid = %d",gettid());

    env = getEnv();

    //找到相应的类
//    cls = env->GetObjectClass(g_obj);
    cls = findClass(env,"com/megvii/guoyizhe/jnisamples/LessonActivity");
    if(cls == NULL){
        LOG("FindClass() Error.....");
        g_jvm->DetachCurrentThread();
        return NULL;
    }
    //找到对应方法
    mid = env->GetStaticMethodID(cls,"getFromJNI","(I)V");
    if(mid == NULL){
        LOG("FindMethod() Error.....");
        g_jvm->DetachCurrentThread();
        return NULL;
    }
    LOG("JNI call method");
    //调用静态方法
    env->CallStaticVoidMethod(cls,mid, *((int*)(&arg)));
    LOG("JNI call method end");

    //Detach主线程
    if(mNeedDetach) {
        g_jvm->DetachCurrentThread();
    }
    LOG("detach over");
    return NULL;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_ThreadTest(JNIEnv *env, jclass type,
                                                              jobject cls) {

    //保存全局JVM以便在子线程中使用
    env->GetJavaVM(&g_jvm);
    g_obj = env->NewGlobalRef(cls);
    int i;
    pthread_t pt[NUMTHREAD];
    for (i = 0; i < NUMTHREAD; i++){
        pthread_create(&pt[i], NULL, &thread_fun, (void *)i);
    }

//    env->DeleteGlobalRef(g_obj);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *pjvm, void *reserved) {
    LOG("JNI OnLoad");
    gJvm = pjvm;  // cache the JavaVM pointer
    JNIEnv* env = getEnv();
    //replace with one of your classes in the line below
    jclass randomClass = env->FindClass("com/megvii/guoyizhe/jnisamples/LessonActivity");
    jclass classClass = env->GetObjectClass(randomClass);
    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader",
                                                      "()Ljava/lang/ClassLoader;");
    jobject localClassLoader = env->CallObjectMethod(randomClass, getClassLoaderMethod);
    gClassLoader = env->NewGlobalRef(localClassLoader);
    //我在Android中用findClass不行，改成loadClass才可以找到class
    gFindClassMethod = env->GetMethodID(classLoaderClass, "findClass",
                                        "(Ljava/lang/String;)Ljava/lang/Class;");

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *pjvm, void *reserved) {
    LOG("JNI OnUnload");
}

//env虚拟机的环境
//jstr 要转换的java字符串  GetStringUTFChars也可以

char* Jstring2cstr(JNIEnv* env,jstring jstr){
    char* rtn=NULL;
    jclass clsstring=env->FindClass("java/lang/String");
    jstring strencode=env->NewStringUTF("GB2312");
    jmethodID mid=env->GetMethodID(clsstring,"getBytes","(Ljava/lang/String;)[B");
    jbyteArray barr=(jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize alen=env->GetArrayLength(barr);
    jbyte* ba=env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen>0){
        rtn=(char*)malloc(alen+1);
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    return rtn;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_megvii_guoyizhe_jnisamples_LessonActivity_NioTest(JNIEnv *env, jclass type,
                                                           jobject buffer) {


//    if(buffer != NULL) {
//        unsigned char *result = (unsigned char *) env->GetDirectBufferAddress(buffer);
//        for (int i = 0; i < 10; ++i) {
//            LOG("%c", result[i]);
//        }
//    }

}