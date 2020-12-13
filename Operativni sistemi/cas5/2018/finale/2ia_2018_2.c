#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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
    char* fullPath;
    check_error((fullPath = realpath(argv[1], NULL)) == NULL, "dir doesn't exist");
    free(fullPath);
    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISDIR(fileInfo.st_mode), "not a dir");

    if(strrchr(argv[1], '/') == NULL){
        check_error(rename(argv[1], argv[2]) == -1, "rename failure");
    }
    else{
        char* frank = calloc(sizeof(char), strlen(argv[1]) + strlen(argv[2]));
        check_error(frank == NULL, "frank wasn't born");
        strcpy(frank, argv[1]);
        frank = dirname(frank);
        strcat(frank, "/");
        strcat(frank, argv[2]);
        check_error(rename(argv[1], frank) == -1, "rename frank failure");
        free(frank);
    }
    
    exit(EXIT_SUCCESS);
}