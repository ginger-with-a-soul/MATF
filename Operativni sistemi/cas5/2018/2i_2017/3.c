#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define SEC_IN_DAY (24*60*60)
#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

unsigned osNumOfDaysFileModified(const char *fpath);

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");

    unsigned delta = osNumOfDaysFileModified(argv[1]);

    fprintf(stdout, "%u\n", delta);

    exit(EXIT_SUCCESS);
}

unsigned osNumOfDaysFileModified(const char *fpath){

    struct stat fileInfo;
    check_error(stat(fpath, &fileInfo) == -1, "stat failure");

    time_t delta = time(NULL) - fileInfo.st_mtime;

    delta /= SEC_IN_DAY;

    return delta;
}