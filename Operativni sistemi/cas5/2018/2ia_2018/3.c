#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");
    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    
    if((fileInfo.st_mode & S_IRGRP) && !(fileInfo.st_mode & S_IROTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IROTH) & (~S_IRGRP)) == -1, "chmod failure");
    }
    else if(!(fileInfo.st_mode & S_IRGRP) && (fileInfo.st_mode & S_IROTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IRGRP) & (~S_IROTH)) == -1, "chmod failure");
    }

    if((fileInfo.st_mode & S_IWGRP) && !(fileInfo.st_mode & S_IWOTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IWOTH) & (~S_IWGRP)) == -1, "chmod failure");
    }
    else if(!(fileInfo.st_mode & S_IWGRP) && (fileInfo.st_mode & S_IWOTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IWGRP) & (~S_IWOTH)) == -1, "chmod failure");
    }

    if((fileInfo.st_mode & S_IXGRP) && !(fileInfo.st_mode & S_IXOTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IXOTH) & (~S_IXGRP)) == -1, "chmod failure");
    }
    else if(!(fileInfo.st_mode & S_IXGRP) && (fileInfo.st_mode & S_IXOTH)){
        check_error(chmod(argv[1], (fileInfo.st_mode | S_IXGRP) & (~S_IXOTH)) == -1, "chmod failure");
    }

    exit(EXIT_SUCCESS);
}