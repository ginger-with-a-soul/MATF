#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){
	check_error(argc != , "Invalid arg count\n");

	exit(EXIT_SUCCESS);
}