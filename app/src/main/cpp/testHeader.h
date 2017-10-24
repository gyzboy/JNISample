//
// Created by Guo Yizhe on 2017/10/21.
//

#include <string>
#include "../../../../../../ndk/platforms/android-21/arch-x86_64/usr/include/sys/types.h"

#ifndef JNISAMPLES_TESTHEADER_H
#define JNISAMPLES_TESTHEADER_H


typedef struct {
    uint uint1;
    u_char u_char1;
    u_long u_long1;
} TEST;

class TESTJNI {
private:
    std::string str;
    TEST test;
public:
    TESTJNI();
    ~TESTJNI();
    int testJNI();
};
#endif //JNISAMPLES_TESTHEADER_H