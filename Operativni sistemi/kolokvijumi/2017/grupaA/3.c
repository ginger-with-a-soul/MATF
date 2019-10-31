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

    check_error(argc != 4, "bad arg count");
    check_error((strcmp(argv[1], "-d") && strcmp(argv[1], "-f")) != 0, "bad first arg");

    int mode = strtol(argv[3], NULL, 8);
    mode_t newUmask = umask(0);
    int open_file;

    if((realpath(argv[2], NULL)) == NULL){
        if(strcmp(argv[1], "-f") == 0){
            check_error((open_file = open(argv[2], O_RDWR | O_CREAT, mode)) == -1, "open file failure");
        }
        else{
            check_error((open_file = mkdir(argv[2], mode)) == -1, "open dir failure");
        }
    }
    else{
        check_error(chmod(argv[2], mode) == -1, "chmode failure");
    }

    close(open_file);
    umask(newUmask);

    exit(EXIT_SUCCESS);
}