#define XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#define check_error(exp, userMsg)\
	do{\
		if(exp){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){
	check_error(argc != 3, "Invalid arg count!\n");

	if(argv[1][1] == 'f'){
		check_error(unlink(argv[2]) == -1, "unlink() failure!\n");
	}
	else if(argv[1][1] == 'd'){
		check_error(rmdir(argv[2]) == -1, "rmdir() failure!\n");
	}
	else{
		check_error(1, "Invalid file type!\n");
	}

	exit(EXIT_SUCCESS);
}