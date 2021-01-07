/*************************************************************************
	> File Name: use_test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 06 Jan 2021 07:10:29 AM PST
 ************************************************************************/

#include <stdio.h>
#include <test.h>

int add(int a, int b){
    return a + b;
}

TEST(func, add) {
    EXPECT_EQ(add(1,2), 3);
    EXPECT_EQ(add(2,4), 7);
    EXPECT_EQ(add(2,4), 6);
}

TEST(func, add2) {
    EXPECT_EQ(add(1, -1), 0);
}

int main(int argc, char *argv[]) {

    return RUN_ALL_TESTS();
}

