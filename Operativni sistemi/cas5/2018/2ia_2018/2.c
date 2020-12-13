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

    check_error(argc != 3, "bad arg count");

    char* fullPath;
    check_error((fullPath = realpath(argv[1], NULL)) == NULL, "dir doesn't exist");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISDIR(fileInfo.st_mode), "not a dir");

    if(strrchr(argv[1], '/') != NULL){
        strcpy(strrchr(argv[1], '/'), argv[2]);
    }
    else{
        rename(argv[1], argv[2]);
    }

    free(fullPath);
    exit(EXIT_SUCCESS);
}