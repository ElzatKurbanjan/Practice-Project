#ifndef _EXPECT_H
#define _EXPECT_H

#include <color.h>
#include <type.h>

extern FunctionInfo test_info;

#define TYPE(a) _Generic((a),\
    int : "%d",\
    double : "lf",\
    float : "%f",\
    long long : "%lld",\
    const char * : "%s",\
    char * : "%s"\
)

#define P(a, color) {\
    char temp[1000];\
    sprintf(temp, color("%s"), TYPE(a));\
    printf(temp, a);\
}

#define EXPECT(a, b, cond) {\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    test_info.total++;\
    if (_a cond _b) {\
        test_info.success += 1;\
    } else {\
        printf("\n");\
        printf(YELLOW_HL("\t%s:%d:  failure\n"), __FILE__, __LINE__);\
        printf(YELLOW_HL("\t\texpect : " #a " " #cond " " #b "\n\t\t" "actual : "));\
        P(_a, YELLOW_HL);\
        printf(YELLOW_HL(" vs "));\
        P(_b, YELLOW_HL);\
        printf("\n\n");\
    }\
    printf(GREEN_HL("[-- case --] "));\
    printf("%s %s %s ? %s\n", #a, #cond, #b, _a cond _b ? GREEN("TRUE") : RED("FALSE"));\
}

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)

#endif