#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ftw.h>
#include <libgen.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)


char* ext = NULL;

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int main(int argc, char** argv){

    ext = argv[2];

    check_error(argc != 3, "bad arg count");
    check_error(realpath(argv[1], NULL) == NULL, "file doesn't exist");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISDIR(fileInfo.st_mode), "arg not a dir");
    check_error(argv[2][0] != '.', "bad 2nd arg");

    

    check_error(nftw(argv[1], fn, 50, 0) == -1, "nftw failure");

    exit(EXIT_SUCCESS);
}

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){

    if(ftwbuf->level < 2 || ftwbuf->level > 5){
        return 0;
    }
    char* toPrint = strrchr(fpath, '/');
    if(S_ISREG(sb->st_mode) && (strstr(fpath, ext) != NULL)){
        printf("%s\n", toPrint + 1);
    }

    return 0;
}