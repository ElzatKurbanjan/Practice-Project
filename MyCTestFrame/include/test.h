/*************************************************************************
	> File Name: test.h
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jan 2021 05:47:45 AM PST
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#define COLOR(content, color) "\033[" #color "m" content "\033[0m"
#define COLOR_HL(content, color) "\033[1;" #color "m" content "\033[0m"

#define GREEN(content) COLOR(content, 32)
#define RED(content) COLOR(content, 31)
#define BLUE(content) COLOR(content, 34)
#define YELLOW(content) COLOR(content, 33)

#define GREEN_HL(content) COLOR_HL(content, 32)
#define RED_HL(content) COLOR_HL(content, 31)
#define BLUE_HL(content) COLOR_HL(content, 34)
#define YELLOW_HL(content) COLOR_HL(content, 33)

typedef struct _FunctionInfo {
    int total;
    int success;
} FunctionInfo;
extern FunctionInfo test_info;

#define TEST(a, b)\
void a##_##b();\
__attribute__((constructor))\
void reg_##a##_##b() {\
    add_function(a##_##b, #a"."#b);\
    return;\
}\
void a##_##b()

#define EXPECT_EQ(a, b) {\
    printf(GREEN_HL("[-- case --] "));\
    test_info.total++;\
    test_info.success += (a == b);\
    printf("%s== %s ? %s\n", #a, #b, a == b ? GREEN("TRUE") : RED("FALSE"));\
}

typedef void (*TestFunc)();

typedef struct _Function {
    TestFunc func;
    const char *name;
} Function;


void add_function(TestFunc, const char*);
int RUN_ALL_TESTS();

#endif
