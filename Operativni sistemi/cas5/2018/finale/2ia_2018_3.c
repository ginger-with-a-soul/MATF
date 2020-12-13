#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISREG(fileInfo.st_mode), "not a reg file");

    unsigned mask1 = 7, mask2 = 56;
    mask2 &= fileInfo.st_mode;
    mask2 >>= 3;
    mask1 &= fileInfo.st_mode;
    mask1 <<= 3;
    fileInfo.st_mode >>= 6;
    fileInfo.st_mode <<= 6;
    fileInfo.st_mode |= mask1 | mask2;

    check_error(chmod(argv[1], fileInfo.st_mode) == -1, "chmod failure");

    exit(EXIT_SUCCESS);
}