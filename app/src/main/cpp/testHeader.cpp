//
// Created by Guo Yizhe on 2017/10/21.
//

#include "testHeader.h"
#include "common.h"

TESTJNI::TESTJNI() {
    LOG("this is TESTJNI Constuctor");
}

TESTJNI::~TESTJNI() {
    LOG("this is TESTJNI ~Constuctor");
}

int TESTJNI::testJNI() {
    str = "add";
    test.uint1 = 5;
    LOG("%s",str.c_str());
    LOG("%d",test.uint1);
    return 1;

}

