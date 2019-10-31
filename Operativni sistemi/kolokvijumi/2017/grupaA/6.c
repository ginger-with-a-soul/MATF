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

    char* srcPath, *destPath;
    check_error((srcPath = realpath(argv[1], NULL)) == NULL, "src doesn't exist");
    destPath = realpath(argv[2], NULL);
    if(destPath != NULL){
        check_error(!strcmp(srcPath, destPath), "same paths");
        free(srcPath);
    }

    check_error(rename(argv[1], argv[2]) == -1, "rename failure");

    exit(EXIT_SUCCESS);
}