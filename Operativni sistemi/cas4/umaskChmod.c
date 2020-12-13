#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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
	check_error(argc != 3, "Invalid arg count!");

	mode_t oldUmask = umask(0);

	long newUmask = strtol(argv[2], NULL, 8);
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, newUmask);
	if(fd == -1){
		if(errno == EEXIST){
			printf("The file that you're trying to set permissions already exists. Chmod() will be used!\n");
			check_error(chmod(argv[1], newUmask) == -1, "chmod() failure!");
		}
		else{
			check_error(fd == -1, "open() failure!");
		}
	}
	else{
		close(fd);
	}

	umask(oldUmask);

	exit(EXIT_SUCCESS);
}
