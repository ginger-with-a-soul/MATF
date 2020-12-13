#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#define MAX_SIZE 1024
#define DAY (24*60*60)

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

	struct stat fInfo1, fInfo2;
	check_error(lstat(argv[1], &fInfo1) == -1, "lstat() failure");
	check_error(lstat(argv[2], &fInfo2) == -1, "lstat() failure");
	
	int difference = abs(ceil((double)(fInfo2.st_mtim.tv_sec - fInfo1.st_mtim.tv_sec) / (double)DAY));

	printf("%i\n", difference);

	exit(EXIT_SUCCESS);
}