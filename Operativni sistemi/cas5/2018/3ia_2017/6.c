#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>
#include <limits.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 3, "bar arg count");

    char* fullSrcPath;
    char* fullDestPath;

    check_error((fullSrcPath = realpath(argv[1], NULL)) == NULL, "src file doesn't exist");

    check_error((fullDestPath = realpath(argv[2], NULL)) == NULL, "dest file error");

    check_error(!strcmp(fullSrcPath, fullDestPath), "src and dest can't be the same");

    free(fullSrcPath);
    free(fullDestPath);
    mode_t newUmask = umask(0);
    struct stat fileInfo;
    int readBytes = 0;
    char* buffer = malloc(MAX_SIZE);
    check_error(buffer == NULL, "buffer malloc failure");

    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    int read_from;
    int write_to;
    check_error((read_from = open(argv[1], O_RDONLY)) == -1, "open (r) failure");
    check_error((write_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, fileInfo.st_mode)) == -1, "open (w) failure");

    while((readBytes = read(read_from, buffer, MAX_SIZE)) > 0){
        check_error(write(write_to, buffer, readBytes) != readBytes, "writing failure");
    }
    umask(newUmask);
    check_error(readBytes == -1, "reading failure");
    free(buffer);
    close(read_from);
    close(write_to);
    check_error(unlink(argv[1]) == -1, "unlink failure");
    exit(EXIT_SUCCESS);
}