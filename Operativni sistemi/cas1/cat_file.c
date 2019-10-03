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
	check_error(argc != 2, "Invalid arg count!\n");

	int fd = open(argv[1], O_RDONLY);
	check_error(fd == -1, "open failure!\n");

	char* buffer = malloc(MAX_SIZE);
	check_error(buffer == NULL, "malloc failure!\n");

	int bytesRead = 0;

	while((bytesRead = read(fd, buffer, MAX_SIZE)) > 0){
		buffer[bytesRead] = 0;
		fprintf(stdout, "%s", buffer);
	}
	check_error(bytesRead == -1, "read() failure!\n");

	free(buffer);
	close(fd);	

	exit(EXIT_SUCCESS);
}