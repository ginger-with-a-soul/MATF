#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

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
	check_error(lstat(argv[1], &fInfo) == -1, "lstat() failure");

	if(S_ISLNK(fInfo.st_mode)){
		printf("%lli\n", (long long) fInfo.st_mtime);
	}
	else{
		check_error(1, "Not a sym link");
	}
	

	exit(EXIT_SUCCESS);
}