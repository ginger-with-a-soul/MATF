#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

void osMkPublicDir(const char *dname);

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");

    osMkPublicDir(argv[1]);

    exit(EXIT_SUCCESS);
}

void osMkPublicDir(const char *dname){

    mode_t newUmask = umask(0);

    int mode = 0777;

    check_error(mkdir(dname, mode) == -1, "mkdir failure");

    umask(newUmask);

}