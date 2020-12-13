#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
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

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISREG(fileInfo.st_mode), "not a reg file");

    off_t offset = atoi(argv[2]);
    int len = atoi(argv[3]);
    int fd;
    int readBytes = 0;
    char* buffer = calloc(sizeof(char), len + 1);
    check_error(buffer == NULL, "calloc failure");
    
    check_error((fd = open(argv[1], O_RDONLY)) == -1, "open failure");
    check_error(lseek(fd, offset, SEEK_SET) == -1, "lseek failure");

    while(len > 0){
        check_error((readBytes = read(fd, buffer, len)) == -1, "read failure");
        check_error(write(STDOUT_FILENO, buffer, readBytes) != readBytes, "writing failure");

        len -= readBytes;
    }
    
    free(buffer);
    close(fd);
    exit(EXIT_SUCCESS);
}