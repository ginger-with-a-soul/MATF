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

	int srcFd = open(argv[1], O_RDONLY);
	int desFd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	check_error(srcFd == -1, "srcFd open() failure!\n");
	check_error(desFd == -1, "desFd open() failure!\n");

	int bytesRead = 0;
	char* buffer = malloc(MAX_SIZE);
	check_error(buffer == NULL, "malloc() failure!\n");

	while((bytesRead = read(srcFd, buffer, MAX_SIZE)) > 0){
		buffer[bytesRead] = 0;
		check_error(write(desFd, buffer, bytesRead) != bytesRead, "write() failure!\n");
	}

	check_error(bytesRead == -1, "read() failure!\n");

	free(buffer);
	close(srcFd);
	close(desFd);

	exit(EXIT_SUCCESS);
}