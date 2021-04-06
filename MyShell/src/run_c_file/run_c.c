#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common_error.h"

int run(char *pathname) {
    pid_t pid = 0;

    /* file doesn't exists */
    if (access(pathname, F_OK) != 0) {
        if ((pid = fork()) < 0 ) {
            perror("fork()");
            return ESYSCALL;
        }
        if (pid == 0){
            execl("/usr/bin/vim", "vim", pathname, NULL);
        } else {
            wait(NULL);
        }
    }

    if ((pid = fork()) < 0) {
        perror("fork()");
        return ESYSCALL;
    }

    if (pid == 0) {
        execl("/usr/bin/gcc", "gcc", pathname, "-o", "a.out", NULL);
    } else {
        wait(NULL);
        if ((pid = fork()) < 0) {
            perror("fork()");
            return ESYSCALL;
        }
        if (pid == 0) {
            execl("./a.out", "a.out", NULL);
        } else {
            wait(NULL);
            execl("/bin/rm", "rm", "a.out", NULL);
        }
    }

    return OK;
}

int main(int argc, char *argv[]) {
    if (2 != argc) {
        fprintf(stderr, "Usage : %s path/x.c\n", argv[0]);
        return EARG;
    }

    return run(argv[1]);
}