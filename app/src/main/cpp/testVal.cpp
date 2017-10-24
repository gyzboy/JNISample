//
// Created by Guo Yizhe on 2017/10/23.
//

#include <cwchar>
#include <malloc.h>
#include <string>
#include "testVal.h"


//int aa = 20;
int aa(20);

//const int bb(50);
extern const int bb(60);

int val = 1;

int &refval = val; // 引用了一个变量

//int &refval1 = 12;  // 错误，12是个字面常量，常量必须要用常量引用


void testArrayData(JNIEnv *env);

TEST_VAL::TEST_VAL(JNIEnv *env,jstring str) {

    LOG("--------test Val---------");
    LOG("bb = %d", bb);
    refval = 2;  // 等价于 val = 2
    LOG("val = %d", val);
    LOG("refval1 = %p", &refval);
    LOG("refval = %d", refval);


    LOG("--------test const Val----------");
    const int val = 1;
    const int &ref1 = val; // 引用了一个一般常量
    const int &ref2 = 12; // 引用了一个字面常量
//    int &ref3 = val; // 错误，常量必须要使用常量引用，ref3是个变量引用
    int var = 2;
//    const int &ref2 = var; // 常量引用指向了一个变量，这时候
//    refval2 = 3;  // 不允许通过常量引用来做任何更改操作
//    varval = 3;   // 但是可以用原始变量来更改内容


    //new和delete是成对出现的
    jint *intVal = new jint(3);
    LOG("intVal:%d", *intVal);
    jint *intVal1 = new jint[4];
    intVal1[0] = 40;
    LOG("intVal1:%d", intVal1[0]);
    delete intVal;
    delete[]intVal1;
    int aa = 3;//分配在栈中,不需要手动delete
    LOG("intVal2:%d", aa);

    jbyte *byteVal = new jbyte('3');
    LOG("charVal:%c", *byteVal);
    delete byteVal;

    char strVal[] = "adfs";
    jstring jStr = env->NewStringUTF(strVal);//供java使用的string,无法直接打印值
    std::string cStr = "cString";//c的string可以通过c_str函数直接打印
    LOG("strVal:%s", cStr.c_str());

    char *tmp = NULL;
    jboolean isCopy;
    tmp = (char *) env->GetStringUTFChars(str, &isCopy);
    if(tmp == NULL){
        return;
    }
    LOG("tmp:%s",tmp);
    env->ReleaseStringUTFChars(str,tmp);

    testArrayData(env);

}

VAL TEST_VAL::getVal(JNIEnv *env) {
    VAL *val = new VAL();
    val->aa = 40;
    char c[] = "charStr";
    val->str = env->NewStringUTF("helloCstr");
    return *val;
}

void testArrayData(JNIEnv *env){
    jintArray jIntArray = env->NewIntArray(4);
    int array[4];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    env->SetIntArrayRegion(jIntArray, 0, 4, array);
//------------第一种方法-------------

//在本地代码中，首先通过 JNI的GetArrayLength 函数获取数组的长度，已知数组是 jintArray 类型，可以得出数组的元素类型是 jint，
//然后根据数组的长度和数组元素类型，申请相应大小的缓冲区。如果缓冲区不大的话，当然也可以直接在栈上申请内存，那样效率更高，
//但是没那么灵活，因为 Java 数组的大小变了，本地代码也跟着修改。
//接着调用 GetIntArrayRegion 函数将 Java 数组中的所有元素拷贝到 C 缓冲区中，并累加数组中所有元素的和，
//最后释放存储 java 数组元素的 C 缓冲区，并返回计算结果。GetIntArrayRegion 函数第 1 个参数是 JNIEnv 函数指针，
//第 2 个参数是 Java 数组对象，第 3 个参数是拷贝数组的开始索引，第 4 个参数是拷贝数组的长度，第 5 个参数是拷贝目的地。

//    //1. 获取数组长度
//    int length = env->GetArrayLength(jIntArray);
//    jint *buff;
//    //2. 根据数组长度和数组元素的数据类型申请存放java数组元素的缓冲区
//    buff = (jint *) malloc(sizeof(jint) * length);
//    //3. 初始化缓冲区
//    memset(buff, 0, sizeof(jint) * length);
//    //4. 拷贝Java数组中的所有元素到缓冲区中
//    env->GetIntArrayRegion(jIntArray, 0, length, buff);
//
//    for (int i = 0; i < length; ++i) {
//        LOG("jintArray elements %d", buff[i]);
//    }
//    free(buff);

//------------第二种方法-------------
//GetIntArrayElements 第三个参数表示返回的数组指针是原始数组，还是拷贝原始数据到临时缓冲区的指针，
// 如果是 JNI_TRUE：表示临时缓冲区数组指针，JNI_FALSE：表示临时原始数组指针。
// 开发当中，我们并不关心它从哪里返回的数组指针，这个参数填 NULL 即可，但在获取到的指针必须做校验，
// 因为当原始数据在内存当中不是连续存放的情况下，JVM 会复制所有原始数据到一个临时缓冲区，并返回这个临时缓冲区的指针。
// 有可能在申请开辟临时缓冲区内存空间时，会内存不足导致申请失败，这时会返回 NULL

    int length = env->GetArrayLength(jIntArray);
    jint *buff;
    buff = env->GetIntArrayElements(jIntArray, NULL);
    //本地代码在访问数组对象时会暂停 GC 线程。不过使用这对函数也有个限制，在 Get/ReleasePrimitiveArrayCritical 这两个函数期间不能调用任何会让线程阻塞或等待 JVM 中其它线程的本地函数或JNI函数，和处理字符串的 Get/ReleaseStringCritical 函数限制一样
//    buff = env->GetPrimitiveArrayCritical(jIntArray,NULL);
    if(buff == NULL){
        LOG("error");
    }
    for (int i = 0; i < length; ++i) {
        LOG("jintArray elements %d",buff[i]);
    }
    env->ReleaseIntArrayElements(jIntArray,buff,0);

//    对于小量的、固定大小的数组，应该选择 Get/SetArrayRegion 函数来操作数组元素是效率最高的。
//    因为这对函数要求提前分配一个 C 临时缓冲区来存储数组元素，你可以直接在 Stack（栈）上或用 malloc 在堆上来动态申请，当然在栈上申请是最快的。
//    像这种复制少量数组元素的代价是很小的，几乎可以忽略。这对函数的另外一个优点就是，
//    允许你传入一个开始索引和长度来实现对子数组元素的访问和操作（SetArrayRegion函数可以修改数组），不过传入的索引和长度不要越界，
//    函数会进行检查，如果越界了会抛出 ArrayIndexOutOfBoundsException 异常
}

