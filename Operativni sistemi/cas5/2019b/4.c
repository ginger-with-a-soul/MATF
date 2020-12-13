#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

int main(int argc, char** argv){

	check_error(argc != 3, "Invalid arg count");

	struct stat finfo1;
	struct stat finfo2;
	check_error(lstat(argv[1], &finfo1) == -1, "lstat() failure");
	check_error(lstat(argv[2], &finfo2) == -1, "lstat() failure");

	mode_t mode = finfo1.st_mode;

	unsigned gr1 = mode & S_IRWXG, ot1 = mode & S_IRWXO, ow1 = mode & S_IRWXU;

	mode = 0;
	mode |= (gr1 << 3) | (ot1 << 3) | (ow1 >> 6);

	check_error(chmod(argv[2], mode) == -1, "chmod failure");

	exit(EXIT_SUCCESS);
}
