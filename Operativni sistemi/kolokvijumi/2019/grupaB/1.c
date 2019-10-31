#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

char name[PATH_MAX];

void func(char* arg);

int main(int argc, char** argv){

	check_error(argc != 3, "Invalid arg count");

	struct stat finfo1;
	struct stat finfo2;
	check_error(lstat(argv[1], &finfo1) == -1, "lstat() failure");
	check_error(lstat(argv[2], &finfo2) == -1, "lstat() failure");
	


	if(finfo1.st_mtim.tv_sec >= finfo2.st_mtim.tv_sec){
		func(argv[1]);
	}
	else{
		func(argv[2]);
	}


	exit(EXIT_SUCCESS);
}

void func(char* arg){
	check_error(realpath(arg, name) == NULL, "realpath() failure");
	char* pr = strrchr(name, '/');
	check_error(pr == NULL, "strrchr() failure");
	printf("%s\n", pr + 1);
}