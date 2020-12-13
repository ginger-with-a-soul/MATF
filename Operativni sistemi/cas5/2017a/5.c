#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <ftw.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int reg = 0, dir = 0, chr = 0, blk = 0, lnk = 0, fifo = 0, sck = 0, total = 0;
int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){

    switch(sb->st_mode & S_IFMT){
        case S_IFREG: reg++; break;
        case S_IFDIR: dir++; break;
        case S_IFCHR: chr++; break;
        case S_IFBLK: blk++; break;
        case S_IFIFO: fifo++; break;
        case S_IFSOCK: sck++; break;
        case S_IFLNK: lnk++; break;
        default: break;
    }

    total++;

    return 0;

}

int main(int argc, char** argv){

    check_error(argc != 2, "bad arg count");

    check_error(nftw(argv[1], fn, 50, FTW_PHYS) == -1, "NFTW failure");

    fprintf(stdout, "%i %i %i %i %i %i %i %i\n", reg, dir, chr, blk, lnk, fifo, sck, total);

    exit(EXIT_SUCCESS);
}