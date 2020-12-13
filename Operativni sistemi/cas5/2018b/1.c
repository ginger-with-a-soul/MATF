#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

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

    double diff = abs(fileInfo.st_atime - fileInfo.st_mtime)*1.0/(60*60);

    diff = ceil(diff);

    fprintf(stdout, "%d\n", (int)diff);

    exit(EXIT_SUCCESS);
}