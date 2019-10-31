//#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	unsigned ow = 0, gr = 0, ot = 0;
	ow |= fInfo.st_mode & S_IRWXU;
	gr |= fInfo.st_mode & (S_IRGRP | S_IWGRP | S_IXGRP);
	ot |= fInfo.st_mode & (S_IROTH | S_IWOTH | S_IXOTH);
	mode_t mode = 0;
	gr <<= 3;
	ow >>= 6;
	ot <<= 3;
	mode |= gr | ow | ot;
	check_error(chmod(argv[1], mode) == -1, "chmod() failure");

	exit(EXIT_SUCCESS);
}