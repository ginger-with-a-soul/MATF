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
#include <time.h>
#include <math.h>

#define MAX_SIZE (1024)
#define DIS (24*60*60)

int days = 0;

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

int func(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf);

int main(int argc, char** argv){
	check_error(argc != 3, "Invalid arg count!");

	days = atoi(argv[2]);
	check_error(days < 0, "Invalid days arg!");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure!");
	check_error(!S_ISDIR(fInfo.st_mode), "It's not a directory!");

	check_error(nftw(argv[1], func, 50, 0) == -1, "nftw() failure!");

	exit(EXIT_SUCCESS);
}

int func(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf){

	time_t diff = time(NULL) - sb->st_mtime;

	if(ceil(diff / DIS) < days){
		printf("%-80s\n", fpath);
	}

	return 0;
}
