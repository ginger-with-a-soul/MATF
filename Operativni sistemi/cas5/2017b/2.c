#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <libgen.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 3, "bad arg count");

    check_error(realpath(argv[1], NULL) == NULL, "file doesn't exist");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    double size = 0;

    if(!strcmp(argv[2], "KB")){
        size = (double)(fileInfo.st_size*1.0/1024);
    }
    else if(!strcmp(argv[2], "MB")){
        size = (double)(fileInfo.st_size*1.0/(1024*1024));
    }
    else if(!strcmp(argv[2], "GB")){
        size = (double)(fileInfo.st_size*1.0/(1024*1024*1024));
    }
    else{
        check_error(1, "bad 2nd arg");
    }

    size = ceil(size);

    fprintf(stdout, "%s %i%s\n", basename(argv[1]), (int)size, argv[2]);

    exit(EXIT_SUCCESS);
}