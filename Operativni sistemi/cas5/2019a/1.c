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
	check_error(lstat(argv[1], &fInfo) == -1, "stat() failure");

	if(fInfo.st_uid == fInfo.st_gid){
		printf("da\n");
	}
	else{
		printf("ne\n");
	}

	exit(EXIT_SUCCESS);
}