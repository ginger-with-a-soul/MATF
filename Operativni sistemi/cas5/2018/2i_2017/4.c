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

void osMoveFile(const char *srcPath, const char *destPath);

int main(int argc, char** argv){

    check_error(argc != 3, "bad arg count");

    osMoveFile(argv[1], argv[2]);

    exit(EXIT_SUCCESS);
}

void osMoveFile(const char *srcPath, const char *destPath){

    char* fullSrcPath;
    char* fullDestPath;
    check_error((fullSrcPath = realpath(srcPath, NULL)) == NULL, "src file doesn't exist");
    fullDestPath = realpath(destPath, NULL);

    if(fullSrcPath != NULL && fullDestPath != NULL){
        check_error(strcmp(fullSrcPath, fullDestPath) == 0, "paths can't be the same");
    }
    free(fullSrcPath);
    free(fullDestPath);

    struct stat fileInfo;
    check_error(stat(srcPath, &fileInfo) == -1, "stat failed");

    mode_t newUmask = umask(0);

    int read_from = open(srcPath, O_RDONLY);
    check_error(read_from == -1, "open for read_from failed");

    int write_to = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, fileInfo.st_mode);
    check_error(write_to == -1, "open for write_to failed");
    umask(newUmask);

    char* buffer = malloc(MAX_SIZE);
    check_error(buffer == NULL, "malloc for buffer failed");

    int readBytes = 0;

    while((readBytes = read(read_from, buffer, MAX_SIZE)) > 0){
        check_error(write(write_to, buffer, readBytes) != readBytes, "write failed");
    }

    check_error(readBytes == -1, "read failed");

    check_error(unlink(srcPath) == -1, "unlink failed");

    free(buffer);
    close(read_from);
    close(write_to);
}