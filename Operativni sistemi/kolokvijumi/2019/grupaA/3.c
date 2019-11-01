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
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 5, "Invalid arg count");

	int a = atoi(argv[2]), b = atoi(argv[3]), n = atoi(argv[4]);
	check_error(a < 0 || b < 0 || n < 0, "Args 2, 3, 4 can't be < 0");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISREG(fInfo.st_mode), "Not a regular file");

	int fd = open(argv[1], O_RDWR);
	check_error(fd == -1, "open() failure");

	char* buffer1 = malloc(sizeof(char) * n);
	char* buffer2 = malloc(sizeof(char) * n);
	check_error(buffer1 == NULL || buffer2 == NULL, "malloc() failure");
	
	check_error(lseek(fd, a, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(read(fd, buffer1, n) <= 0, "read() failure");
	check_error(lseek(fd, b, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(read(fd, buffer2, n) <= 0, "read() failure");

	check_error(lseek(fd, a, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(write(fd, buffer2, n) <= 0, "write() failure");
	check_error(lseek(fd, b, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(write(fd, buffer1, n) <= 0, "write() failure");

	free(buffer1);
	free(buffer2);
	close(fd);

	exit(EXIT_SUCCESS);
}