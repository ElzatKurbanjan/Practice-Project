#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <test.h>

typedef enum _flags {
    LIST = 0,
    ALL
} FLAGS;

typedef enum _error {
    OK = 0,
    EARG
} ERRORS;

void usage() {
    printf("ls [-a] [-l] [dirname...]\n");
    return;
}

int resolve_cmdline_args(int argc, char * argv[], int *flags) {
    char opt = 0;

    while ((opt = getopt(argc, argv, "al"))  != -1) {
        switch (opt)
        {
        case 'a':
            (*flags) |= (1 << ALL);
            break;
        
        case 'l':
            (*flags) |= (1 << LIST);
            break;

        default:
            usage();
            return EARG;
        }
    }

    return OK;
}

int run(int flags) {
    printf("hello ls\n");

    return 0;
} 

int main(int argc, char * argv[]) {
    int flags = 0;
    int ret = 0;

    ret = resolve_cmdline_args(argc, argv, &flags);
    if (OK != ret) {
        return ret;
    }

    return run(flags);;
}