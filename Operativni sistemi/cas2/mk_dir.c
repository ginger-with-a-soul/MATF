#define XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#define MAX_SIZE (1024)

#define check_error(exp, userMsg)\
	do{\
		if(exp){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){
	check_error(argc != 3, "Invalid arg count!\n");

	long mode = strtol(argv[2], NULL, 8);
	check_error(mkdir(argv[1], mode) == -1, "mkdir() failure!\n");

	exit(EXIT_SUCCESS);
}