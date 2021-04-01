#ifndef _LS_H
#define _LS_H

#include <time.h>

#define NAME_STR_LENGTH 256
#define MODE_STR_LENGTH 12
#define MAX_ITEM_COUNT 1024
#define MAX_COL_COUNT 512
#define SPACE_BETWEEN_NAMES 2

typedef struct _output_item {
    unsigned int mode;
    unsigned long link;
    long int size;
    struct tm m_time;
    char user_name[NAME_STR_LENGTH];
    char group_name[NAME_STR_LENGTH];
    char file_name[NAME_STR_LENGTH];
} OUTPUT_ITEM;

typedef enum _flags {
    LS_LIST = 0,
    LS_ALL
} FLAGS;

#endif