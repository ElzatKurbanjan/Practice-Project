/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jan 2021 06:03:05 AM PST
 ************************************************************************/
#include <test.h>
#include <string.h>

static Function func_arr[100] = {0};
static int func_count = 0;

void add_function(TestFunc func, const char *str){
    func_arr[func_count].func = func;
    func_arr[func_count].name = strdup(str);
    func_count++;
    return;
}

int RUN_ALL_TESTS() {
    for (int i = 0; i < func_count; i++) {
        func_arr[i].func();
    }
    return 0;
}

