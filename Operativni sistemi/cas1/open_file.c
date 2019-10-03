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

	int flags = 0;
	switch(argv[2][0]){
		case 'r': flags |= argv[2][1] == '+'? O_RDWR : O_RDONLY; break;
		case 'w': flags |= argv[2][1] == '+'? O_RDWR | O_TRUNC | O_CREAT : O_WRONLY | O_TRUNC | O_CREAT; break;
		case 'a': flags |= argv[2][1] == '+'? O_RDWR | O_APPEND | O_CREAT : O_WRONLY | O_APPEND | O_CREAT; break;
		default: check_error(1, "Invalid opening mode!\n"); break;
	}

	const mode_t mode = 0644;
	
	int fd = open(argv[1], flags, mode);
	check_error(fd == -1, "open() failure!\n");

	close(fd);

	exit(EXIT_SUCCESS);
}