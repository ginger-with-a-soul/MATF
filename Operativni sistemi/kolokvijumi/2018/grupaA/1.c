#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <utime.h>
#include <time.h>
#include <limits.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 3, "bad arg count");
    int diff;
    check_error((diff = atoi(argv[2])) < 0, "bad 2nd arg");
    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    struct utimbuf times;
    times.actime = (time_t)diff;
    times.modtime = (time_t)diff;

    check_error(utime(argv[1], &times) == -1, "utime failure");

    exit(EXIT_SUCCESS);
}