#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc < 2   , "bad arg count");

    int i = 1;

    while(argc - 1 > 0){
        char* fullPath = calloc(sizeof(char), MAX_SIZE);
        check_error(fullPath == NULL, "calloc failure");
        check_error((fullPath = realpath(argv[i], NULL)) == NULL, "dir doesn't exist");

        struct stat fileInfo;
        check_error(stat(argv[i], &fileInfo) == -1, "stat failure");
        check_error(!S_ISDIR(fileInfo.st_mode), "file not a dir");

        unsigned mask = 7;
        mask &= fileInfo.st_mode;

        if(!mask){
            int j = strlen(fullPath);
            fprintf(stdout, "%i\n", j);
        }

        free(fullPath);
        i++;
        argc--;
    }

    exit(EXIT_SUCCESS);
}