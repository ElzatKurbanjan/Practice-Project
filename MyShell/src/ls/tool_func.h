#ifndef _TOOL_FUNC_H
#define _TOOL_FUNC_H

#include "ls.h"

extern unsigned int get_win_width();
extern void construct_an_output_item(const char *, const struct dirent *, OUTPUT_ITEM *, int);
extern unsigned int calc_col_count(unsigned int win_width, OUTPUT_ITEM *items, int count, int *each_col_length);
extern void print_file(OUTPUT_ITEM item, int assigned_length);
void convert_mode2str(unsigned int mode, char *c_mode);
unsigned int numlen(unsigned long num);

#endif