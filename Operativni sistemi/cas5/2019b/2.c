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

	check_error(argc != 2, "Invalid arg count");

	struct stat linfo;
	struct stat sinfo;
	check_error(lstat(argv[1], &linfo) == -1, "lstat() failure");
	check_error(stat(argv[1], &sinfo) == -1, "stat() failure");
	if(S_ISLNK(linfo.st_mode)){
		if((linfo.st_uid == sinfo.st_uid) && (linfo.st_gid == sinfo.st_gid)){
			printf("da\n");
		}
		else{
			printf("ne\n");
		}
	}
	else{
		check_error(1, "Not a link");
	}

	exit(EXIT_SUCCESS);
}
