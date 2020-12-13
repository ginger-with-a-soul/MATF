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
			fprintf(stderr, "\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 4, "Invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISREG(fInfo.st_mode), "Not a regular file");

	int p = atoi(argv[2]);
	int n = atoi(argv[3]);
	int rb = 0;

	int fd = open(argv[1], O_RDWR);
	check_error(fd == -1, "open() failure");

	char* buffer = malloc(sizeof(char) * n);
	check_error(buffer == NULL, "malloc() failure");
	char* tmp = malloc(sizeof(char) * n);
	check_error(tmp == NULL, "malloc() failure");

	check_error(lseek(fd, p, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(read(fd, buffer, n) <= 0, "read() failure");

	for(int i = 0, j = n - 1; i < n; i++, j--){
		tmp[i] = buffer[j];
	}

	check_error(lseek(fd, p, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(write(fd, tmp, n) <= 0, "write() failure");


	free(buffer);
	free(tmp);
	close(fd);

	exit(EXIT_SUCCESS);

}