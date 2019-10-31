#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <ftw.h>

#define MAX_SIZE 1024
#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define MAX_LEVEL 3
#define MIN_LEVEL 1
int func(const char* path, const struct stat* sb, int typeflag, struct FTW* ftwbuf);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	struct stat fInfo;
	check_error(lstat(argv[1], &fInfo) == -1, "lstat() failure");
	check_error(!S_ISDIR(fInfo.st_mode), "Not a dir");
	check_error(nftw(argv[1], func, 50, FTW_PHYS) == -1, "nftw() failure");
	
	exit(EXIT_SUCCESS);

}

int func(const char* path, const struct stat* sb, int typeflag, struct FTW* ftwbuf){

	if(ftwbuf->level > MAX_LEVEL || ftwbuf->level < MIN_LEVEL){
		return 0;
	}

	if(typeflag == FTW_D){
		if(strchr(path + ftwbuf->base, '.') != NULL){
			printf("%s\n", path + ftwbuf->base);
		}
	}

	return 0;

}