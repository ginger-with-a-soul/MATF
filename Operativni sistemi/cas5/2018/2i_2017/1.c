#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int osIsPublicFile(const char *fpath);

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");

    int a = osIsPublicFile(argv[1]);

    if(a){
        fprintf(stdout, "true\n");
    }
    else{
        fprintf(stdout, "false\n");
    }

    exit(EXIT_SUCCESS);
}

int osIsPublicFile(const char *fpath){
    
    struct stat fileInfo;
    check_error(stat(fpath, &fileInfo) == -1, "stat error");
    check_error(S_ISREG(fileInfo.st_mode) != 1, "not a reg file");
    if((fileInfo.st_mode & S_IROTH) && (fileInfo.st_mode & S_IWOTH)){
        return 1;
    }
    else{
        return 0;
    }
}