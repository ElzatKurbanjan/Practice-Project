#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "common_error.h"
#include "tool_func.h"
#include "color.h"

unsigned int get_win_width() {
    struct winsize size = {0};

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&size) < 0) {
        perror("ioctl");
        return 0;
    }

    return size.ws_col;
}

void convert_mode2str(unsigned int mode, char *c_mode) {
    char mode_tb[9] = {'x', 'w', 'r', 'x', 'w', 'r', 'x', 'w', 'r'};
    int i = 0;
    int j = 0;

    for (; i < 9; ++i) {
        if (mode & (1 << i)) {
            c_mode[i] = mode_tb[i];
        } else {
            c_mode[i] = '-';
        }
    }

    switch (mode & S_IFMT)
    {
        case S_IFREG :
            c_mode[i] = '-'; 
            break;
        
        case S_IFDIR :
            c_mode[i] = 'd';
            break;

        case S_IFLNK :
            c_mode[i] = 'l';
            break;

        case S_IFBLK :
            c_mode[i] = 'b';
            break;

        case S_IFIFO :
            c_mode[i] = 'p';
            break;

        case S_IFCHR :
            c_mode[i] = 'c';
            break;

        case S_IFSOCK :
            c_mode[i] = 's';
            break;

        default:
            break;
    }

    /* reverse */
    for (; i > j; --i, ++j) {
        c_mode[j] = c_mode[j] ^ c_mode[i];
        c_mode[i] = c_mode[j] ^ c_mode[i];
        c_mode[j] = c_mode[j] ^ c_mode[i];
    }

    return;
}

void print_file(OUTPUT_ITEM item, int assigned_length) {
    switch (item.mode & S_IFMT) {
        case S_IFREG : 
            if ((item.mode & S_IXUSR) || \
                (item.mode & S_IXGRP) || \
                (item.mode & S_IXOTH)) {
                    printf(GREEN_HL("%-*s"), assigned_length, item.file_name);
                } else{
                    printf("%-*s", assigned_length, item.file_name);
                }
            break;

        case S_IFDIR :
            printf(BLUE_HL("%-*s"), assigned_length, item.file_name);
            break;
        
        case S_IFCHR :
        case S_IFBLK :
            printf(YELLO_HL("%-*s"), assigned_length, item.file_name);
            break;

        case S_IFLNK : 
            printf(CYAN_HL("%-*s"), assigned_length, item.file_name);
            break;

        default :
            printf("%-*s", assigned_length, item.file_name);
    }
    
    return;
}

void construct_an_output_item(const char *pathname, const struct dirent *dir_content, OUTPUT_ITEM *items, int index) {
    char file_path[1024] = {0};
    struct stat file_stat = {0};
    struct tm file_time = {0};

    sprintf(file_path, "%s/%s", pathname, dir_content->d_name);
    if (dir_content->d_type == DT_LNK) {
        lstat(file_path, &file_stat);
    } else {
        stat(file_path, &file_stat);
    }
    gmtime_r(&file_stat.st_mtime, &file_time);

    items[index].mode = file_stat.st_mode;
    items[index].m_time = file_time;
    items[index].link = file_stat.st_nlink;
    items[index].size = file_stat.st_size;
    strcpy(items[index].file_name, dir_content->d_name);
    strcpy(items[index].user_name, (getpwuid(file_stat.st_uid))->pw_name);
    strcpy(items[index].group_name, (getgrgid(file_stat.st_gid))->gr_name);

    return ;
}

/* STRATEGT : use the least row to put items */
unsigned int calc_col_count(unsigned int win_width, OUTPUT_ITEM *items, int count, int *each_col_length) {
    unsigned int col_count = 0;
    int row = 1;
    int max_line_length = 0;
    int file_name_length = 0;
    int max_file_name_length = 0;

    /* run util find appropriate row */
    while (1) {
        col_count = count / row;
        max_line_length = 0;
        for (int i = 0; i < col_count && i < count; ++i) {
            max_file_name_length = 0;
            /* find max length of each col */
            for (int j = i; j < count; j += col_count) {
                file_name_length = strlen(items[j].file_name) + SPACE_BETWEEN_NAMES;  /* add 2 space */
                if (file_name_length > max_file_name_length) {
                    max_file_name_length = file_name_length;
                    each_col_length[i] = max_file_name_length;
                }
            }
            max_line_length += max_file_name_length;
        }
        if (max_line_length < win_width){
            break;
        }
        ++row;
    }

    return col_count;
}

unsigned int numlen(unsigned long num) {
    if (0 == num) {
        return 1;
    }

    int n = 0;
    while (num) {
        num /= 10;
        ++n;
    }
    return n;
}