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
    check_error((argv[2][0] != 'u' && argv[2][0] != 'g' && argv[2][0] != 'o') || (argv[2][1] != '+' && argv[2][1] != '-') || (argv[2][2] != 'r' && argv[2][2] != 'w' && argv[2][2] != 'x'), "bad 2nd arg");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    if(argv[2][0] == 'u'){
        if(argv[2][1] == '+'){
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IRUSR) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IWUSR) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode | S_IXUSR) == -1, "chmod failure");
            }
        }
        else{
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IRUSR) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IWUSR) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IXUSR) == -1, "chmod failure");
            }

        }
    }
    else if(argv[2][0] == 'g'){
        if(argv[2][1] == '+'){
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IRGRP) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IWGRP) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode | S_IXGRP) == -1, "chmod failure");
            }
        }
        else{
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IRGRP) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IWGRP) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IXGRP) == -1, "chmod failure");
            }

        }
    }
    else{
        if(argv[2][1] == '+'){
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IROTH) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode | S_IWOTH) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode | S_IXOTH) == -1, "chmod failure");
            }
        }
        else{
            if(argv[2][2] == 'r'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IROTH) == -1, "chmod failure");
            }
            else if(argv[2][2] == 'w'){
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IWOTH) == -1, "chmod failure");
            }
            else{
                check_error(chmod(argv[1], fileInfo.st_mode & ~S_IXOTH) == -1, "chmod failure");
            }

        }
    }
    exit(EXIT_SUCCESS);
}