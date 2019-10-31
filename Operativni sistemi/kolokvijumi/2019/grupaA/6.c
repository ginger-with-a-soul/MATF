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

	struct stat finfo;
	check_error(lstat(argv[1], &finfo) == -1, "lstat() failure");

	if(S_ISLNK(finfo.st_mode)){
		char* buffer = malloc(MAX_SIZE);
		int readBytes = 0;
		readlink(argv[1], buffer, MAX_SIZE);
		printf("%s\n", buffer);
		free(buffer);
	}
	else{
		check_error(1, "Not a symbolic link");
	}



	exit(EXIT_SUCCESS);
}