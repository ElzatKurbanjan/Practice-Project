/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jan 2021 06:03:05 AM PST
 ************************************************************************/
#include <test.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static Function func_arr[100] = {0};
static int func_count = 0;
FunctionInfo test_info = {0};

void add_function(TestFunc func, const char *str){
    func_arr[func_count].func = func;
    func_arr[func_count].name = strdup(str);
    func_count++;
    return;
}

int RUN_ALL_TESTS() {
    for (int i = 0; i < func_count; i++) {
        printf(GREEN_HL("[====== RUN ======]") BLUE_HL(" %s\n"), func_arr[i].name);
        test_info.total = 0;
        test_info.success = 0;
        func_arr[i].func();
        double rate = 100.0 * test_info.success / test_info.total;
        printf(GREEN_HL("[------ END ------]"));
        if (fabs(rate - 100.0) < 1e-6) {
            printf(GREEN_HL(" pass: %.2lf%%"), rate);
        } else {
            printf(RED_HL(" pass: %.2lf%%"), rate);
        }
        printf(BLUE_HL("    total : %d    succuss : %d\n"), test_info.total, test_info.success);
    }
    return 0;
}

