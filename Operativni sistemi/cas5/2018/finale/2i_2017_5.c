#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <ftw.h>
#include <libgen.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

unsigned mode = 6;
char* newPath;
char* src;
char* dest;
char* dest2;

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int main(int argc, char** argv){

    dest = argv[2];
    strcat(dest, "/");
    strcpy(dest2, dest);
    

    check_error(argc != 3, "bad arg count");
    check_error(realpath(argv[1], NULL) == NULL, "dir doesn't exist");

    struct stat fileInfo;
    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");
    check_error(!S_ISDIR(fileInfo.st_mode), "not a dir");

    mode_t newUmask = umask(0);
    check_error(nftw(argv[1], fn, 50, 0) == -1, "nftw failure");
    check_error(mkdir(argv[2], 0777) == -1, "mkdir failure");
    check_error(realpath(argv[2], NULL) == realpath(argv[1], NULL), "same paths");




    umask(newUmask);
    exit(EXIT_SUCCESS);
}

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){

    if(!S_ISREG(sb->st_mode)){
        return 0;
    }

    if((sb->st_mode & mode) == 6){
        if(sb->st_mtime/(60*60*24) < 31){
            strcpy(newPath, fpath);
            newPath = basename(newPath);
            strcat(dest, newPath);
            check_error(open(dest, O_RDONLY | O_CREAT, sb->st_mode) == -1, "open failure");
            check_error(unlink(fpath) == -1, "unlink failure");
            strcpy(dest, dest2);
        }
        else{
            check_error(unlink(fpath) == -1, "unlink failure");
        }
    }
    return 0;
}