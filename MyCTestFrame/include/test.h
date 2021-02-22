/*************************************************************************
	> File Name: test.h
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jan 2021 05:47:45 AM PST
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#include <expect.h>

#define TEST(a, b)\
void a##_##b();\
__attribute__((constructor))\
void reg_##a##_##b() {\
    add_function(a##_##b, #a"."#b);\
    return;\
}\
void a##_##b()

int RUN_ALL_TESTS();
void add_function(TestFunc, const char*);

#endif
