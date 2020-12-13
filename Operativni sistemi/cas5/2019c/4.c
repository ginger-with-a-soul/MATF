#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#define MAX_SIZE 1024

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

int main(int argc, char** argv){

	check_error(argc != 4, "Invalid arg count");

	struct stat info1, info2;
	check_error(lstat(argv[1], &info1) == -1, "lstat() failure");
	check_error(lstat(argv[2], &info2) == -1, "lstat() failure");

	mode_t mode = info1.st_mode & info2.st_mode;

	mode_t oldUmask = umask(0);

	int c = creat(argv[3], mode);
	check_error(c == -1, "creat() failure");

	close(c);
	
	umask(oldUmask);

	exit(EXIT_SUCCESS);
}