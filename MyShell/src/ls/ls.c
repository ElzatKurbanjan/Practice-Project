#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "common_error.h"
#include "ls.h"
#include "tool_func.h"

static void usage() {
    printf("ls [-a] [-l] [dirname...]\n");
    return;
}

static int resolve_cmdline_args(int argc, char * argv[], int *flags) {
    char opt = 0;

    if (argc < 0 || argv == NULL || flags == NULL) {
        return EARG;
    }

    while ((opt = getopt(argc, argv, "al"))  != -1) {
        switch (opt)
        {
            case 'a':
                (*flags) |= (1 << LS_ALL);
                break;
        
            case 'l':
                (*flags) |= (1 << LS_LIST);
                break;

            default:
                usage();
                return EARG;
        }
    }

    return OK;
}

static void layout_items(OUTPUT_ITEM *items, int count) {
    unsigned int win_width = get_win_width();
    int col = 0;
    int each_col_length[MAX_COL_COUNT] = {0};

    col = calc_col_count(win_width, items, count, each_col_length);

    for (int i = 0; i < count;) {
        for (int j = 0; j < col && i < count; ++j, ++i) {
            print_file(items[i], each_col_length[j]);
        }
        printf("\n");
    }

    return;
}

static void list_items(OUTPUT_ITEM *items, int count) {
    char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char mode_str[MODE_STR_LENGTH] = {0};
    int max_mode_length = 0;
    int max_link_length = 0;
    int max_usr_name_length = 0;
    int max_grp_name_length = 0;
    int max_size_length = 0;
    int max_day_length = 0;
    int max_time_str_length = 0;
    int tmp = 0;
    struct tm current_time = {0};
    time_t current_time_t = 0;
    char **time_strs = NULL;

    if ((time_strs = (char **)malloc(sizeof(char *) * count)) == NULL) {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < count; ++i) {
        if ((time_strs[i] = (char *)malloc(sizeof(char) * 6)) == NULL) {
            perror("malloc");
            exit(1);
        }
    }

    time(&current_time_t);
    gmtime_r(&current_time_t, &current_time);

    for (int i = 0; i < count; ++i) {
        convert_mode2str(items[i].mode, mode_str);
        tmp = strlen(mode_str);
        max_mode_length = tmp > max_mode_length ? tmp : max_mode_length;
        tmp = numlen(items[i].link);
        max_link_length = tmp > max_link_length ? tmp : max_link_length;
        tmp = strlen(items[i].user_name);
        max_usr_name_length = tmp > max_usr_name_length ? tmp : max_usr_name_length;
        tmp = strlen(items[i].group_name);
        max_grp_name_length = tmp > max_grp_name_length ? tmp : max_grp_name_length;
        tmp = numlen(items[i].size);
        max_size_length = tmp > max_size_length ? tmp : max_size_length;
        tmp = numlen(items[i].m_time.tm_mday);
        max_day_length = tmp > max_day_length ? tmp : max_day_length;
        if (current_time.tm_year == items[i].m_time.tm_year) {
            sprintf(time_strs[i], "%02d:%02d", items[i].m_time.tm_hour, items[i].m_time.tm_sec);
            max_time_str_length = 5;
        } else {
            sprintf(time_strs[i], "%d", (items[i].m_time.tm_year + 1900));
            max_time_str_length = (max_time_str_length == 5) ? 5 : 4;
        }

    }

    for (int i = 0; i < count; ++i) {
        convert_mode2str(items[i].mode, mode_str);
        printf("%-*s %*lu %-*s %-*s %*ld %s %*u %*s ", max_mode_length, mode_str, \
                max_link_length, items[i].link, \
                max_usr_name_length, items[i].user_name, \
                max_grp_name_length, items[i].group_name, \
                max_size_length, items[i].size, \
                months[items[i].m_time.tm_mon], \
                max_day_length, items[i].m_time.tm_mday, \
                max_time_str_length, time_strs[i]);
        print_file(items[i], 0);
        printf("\n");
    }

    for (int i = 0; i < count; ++i) {
        if (time_strs[i] != NULL) {
            free(time_strs[i]);
            time_strs[i] = NULL;
        }
    }
    free(time_strs);
    return;
}

static int handle_single_dir(char *pathname, int flags) {
    DIR * dir = NULL;
    struct dirent *dir_content = NULL;
    OUTPUT_ITEM *items = (OUTPUT_ITEM *)malloc(sizeof(OUTPUT_ITEM) * MAX_ITEM_COUNT);
    int item_count = 0;
    int ret = OK;

    if (pathname == NULL) {
        ret = EARG;
        goto out;
    }

    if ((dir = opendir(pathname)) == NULL) {
        perror("opendir");
        ret = ESYSCALL;
        goto out;
    }

    while ((dir_content = readdir(dir)) != NULL) {
        if ((dir_content->d_name[0] != '.') || (flags & (1 << LS_ALL))) {
            construct_an_output_item(pathname, dir_content, items, item_count++);
        }
    }

    if (flags & (1 << LS_LIST)) {
        /* TODO : link file add linkage to original file */
        list_items(items, item_count);
    } else {
        layout_items(items, item_count);
    }
    
out:
    if (NULL != items) {
        free(items);
        items = NULL;
    }
    return ret;
}

static int run_ls(int argc, char *argv[], int flags) {
    int ret = OK;

    if (argc < 0 || argv == NULL) {
        return EARG;
    }

    if (1 == argc || (2 == argc && flags != 0)) {
        /* without args, add manually */
        ret = handle_single_dir(".", flags);
    } else {
        for (int i = optind; i < argc; ++i) {
            ret = handle_single_dir(argv[i], flags);
        }
    }

    return ret;
}

int main(int argc, char * argv[]) {
    int flags = 0;
    int ret = 0;

    ret = resolve_cmdline_args(argc, argv, &flags);
    if (OK != ret) {
        return ret;
    }

    return run_ls(argc, argv, flags);
}