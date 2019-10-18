#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ftw.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

char* ext = NULL;

int func(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf);

int main(int argc, char** argv){

	check_error(argc != 3, "Invalid arg count!");

	ext = argv[2];

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure!");
	check_error(nftw(argv[1], func, 50, 0) == -1, "nftw() failure");

	exit(EXIT_SUCCESS);
}

int func(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf){

	if(typeflag == FTW_F){
		char *toExten = strrchr(fpath + ftwbuf->base, '.');
		if(toExten != NULL && !strcmp(toExten, ext)){
			printf("%-80s\n", fpath);
		}
	}
	return 0;
}
