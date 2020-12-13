#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <time.h>
#define SEC_IN_DAY (60*60*24)

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

    time_t now = time(NULL);
    time_t aTime = now - fileInfo.st_atime;
    time_t mTime = now - fileInfo.st_mtime;

    fprintf(stdout, "%i\n", (abs(aTime - mTime))/SEC_IN_DAY);

    exit(EXIT_SUCCESS);
}