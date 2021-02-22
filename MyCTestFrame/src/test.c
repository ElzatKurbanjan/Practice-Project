/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jan 2021 06:03:05 AM PST
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <color.h>
#include <type.h>

static FunctionList function_list = {{0, 0}, \
                                    LIST_HEAD_INIT(function_list.list)};
FunctionInfo test_info = {0};

void add_function(TestFunc func, const char *str) {
    FunctionList *fl = (FunctionList *)malloc(sizeof(FunctionList));

    fl->func.func = func;
    fl->func.name = strdup(str);
    list_add_tail(&fl->list, &function_list.list);

    return;
}

int RUN_ALL_TESTS() {
    FunctionList *iterator = NULL;
    FunctionList *iterator_tmp = NULL;
    
    list_for_each_entry(iterator, &function_list.list, list) {
        printf(GREEN_HL("[====== RUN ======]") BLUE_HL(" %s\n"), iterator->func.name);
        test_info.total = 0;
        test_info.success = 0;
        iterator->func.func();
        double rate = 100.0 * test_info.success / test_info.total;
        printf(GREEN_HL("[------ END ------]"));
        if (fabs(rate - 100.0) < 1e-6) {
            printf(GREEN_HL(" pass: %.2lf%%"), rate);
        } else {
            printf(RED_HL(" pass: %.2lf%%"), rate);
        }
        printf(BLUE_HL("    total : %d    succuss : %d\n"), test_info.total, test_info.success);

        if (!list_is_last(&iterator->list, &function_list.list)) {
            printf("\n");
        }
    }

    /* 释放资源 */
    list_for_each_entry_safe(iterator, iterator_tmp, &function_list.list, list) {
        list_del(&iterator->list);
        free(iterator);
    }

    return 0;
}
