//
// Created by Guo Yizhe on 2017/10/23.
//

#ifndef JNISAMPLES_TESTVAL_H
#define JNISAMPLES_TESTVAL_H

#include <jni.h>
#include "common.h"

//同一个.h头文件被同一 .c 文件多次引用时（可能是间接多次引用），编译生成相应的 .o 文件，链接时候会报 foo bar 重复定义。
//1、一个可能想到的方法是在头文件中加入宏定义，防止头文件被重复引用
//2、在头文件中只声明函数、变量
extern int aa;

extern const int bb;

typedef struct {
    int aa;
    jstring str;
    jintArray jArray;
}VAL;

class TEST_VAL{
public:
    TEST_VAL(JNIEnv *env,jstring str);
    ~TEST_VAL();
    VAL getVal(JNIEnv *env);
};

#endif //JNISAMPLES_TESTVAL_H
