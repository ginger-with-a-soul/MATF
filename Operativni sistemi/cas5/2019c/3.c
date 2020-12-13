#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

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

	check_error(argc != 4, "Invalid arg count");

	int p = atoi(argv[2]), n = atoi(argv[3]);

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISREG(fInfo.st_mode), "Not a regular file");

	int fd = open(argv[1], O_RDWR);

	char* buffer = malloc(sizeof(char) * n);
	check_error(buffer == NULL, "malloc() failure");
	check_error(lseek(fd, p, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(read(fd, buffer, n) <= 0, "read() failure");

	int len = strlen(buffer);
	for(int i = 0; i < len; i++){
		if(isalpha(buffer[i])){
			if(islower(buffer[i])){
				buffer[i] = toupper(buffer[i]);
			}
			else{
				buffer[i] = tolower(buffer[i]);
			}
		}
	}

	check_error(lseek(fd, p, SEEK_SET) == (off_t)-1, "lseek() failure");
	check_error(write(fd, buffer, n) <= 0, "write() failure");

	free(buffer);
	close(fd);

	exit(EXIT_SUCCESS);

}