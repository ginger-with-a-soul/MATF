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

    check_error(argc != 4, "bar arg count");
    check_error(strcmp(argv[1], "-d") && strcmp(argv[1], "-f"), "bad 1st arg");

    char* fullPath;
    free(fullPath);

    int open_file;
    int mode = strtol(argv[3], NULL, 8);
    mode_t newUmask = umask(0);
    
    if(strcmp(argv[1], "-d")){
        check_error((open_file = open(argv[2], O_RDWR | O_CREAT | O_EXCL, mode)) < 0 && (errno == EEXIST), "file already exists");
    }
    else{
        check_error((open_file = mkdir(argv[2], mode)) == -1, "mkdir failure");
    }

    umask(newUmask);

    exit(EXIT_SUCCESS);
}