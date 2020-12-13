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

	check_error(argc != 2, "Invalid arg count");

	struct stat lInfo, sInfo;
	check_error(lstat(argv[1], &lInfo) == -1, "lstat() failure");

	if(!S_ISLNK(lInfo.st_mode)){
		check_error(1, "Not a link");
	}
	else{
		check_error(stat(argv[1], &sInfo) == -1, "stat() failure");
		long long size = sInfo.st_size - lInfo.st_size;
		printf("%lli\n", size);
	}

	exit(EXIT_SUCCESS);
}