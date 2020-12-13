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

    int offset = atoi(argv[2]);
    int len = atoi(argv[3]);
    check_error(offset < 0 || len < 1, "bad offset or len");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    check_error(!S_ISREG(fileInfo.st_mode), "not a regular file");

    int open_file;
    check_error((open_file = open(argv[1], O_RDONLY)) == -1, "open failure");

    check_error(lseek(open_file, offset, SEEK_SET) == -1, "lseek failure");

    int readBytes = 0;
    char* buffer = malloc(len + 2);
    check_error(buffer == NULL, "malloc failure");

    while(len > 0){
        check_error((readBytes = read(open_file, buffer, len)) == -1, "read failure");
        check_error(write(STDOUT_FILENO, buffer, readBytes) == -1, "write failure");
        len -= readBytes;
    }

    check_error(readBytes == -1, "write failure");
    free(buffer);
    close(open_file);
    exit(EXIT_SUCCESS);
}