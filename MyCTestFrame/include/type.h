#ifndef _TYPE_H
#define _TYPE_H

#include <list.h>

typedef void (*TestFunc)();

typedef struct _function {
    TestFunc func;
    const char *name;
} Function;

typedef struct _function_info {
    int total;
    int success;
} FunctionInfo;

typedef struct _func_list {
    Function func;
    struct list_head list;
} FunctionList;

#endif