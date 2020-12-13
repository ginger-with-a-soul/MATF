#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#define MAX_SIZE 1024

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 6, "Invalid arg count");

	char* path = argv[1];
	int start = atoi(argv[2]);
	int lenght = atoi(argv[3]);
	int sleepTime = atoi(argv[4]);
	int lockType = argv[5][0] == 'r' ? F_RDLCK : F_WRLCK;

	int fd = open(path, O_RDWR);
	check_error(fd == -1, "open() failure");

	FILE* f = fdopen(fd, "r+");
	check_error(f == NULL, "fdopen() failure");

	struct flock lock;
	lock.l_type = lockType;
	lock.l_whence = SEEK_SET;
	lock.l_start = start;
	lock.l_len = lenght;

	printf("Locking!\n");
	check_error(fcntl(fd, F_SETLK, &lock) == -1, "fcntl() failure");

	printf("Locked\n");

	sleep(sleepTime);

	printf("Unlocking\n");
	lock.l_type = F_UNLCK;
	check_error(fcntl(fd, F_SETLK, &lock) == -1, "fcntl() failure");

	printf("Unlocked\n");

	fclose(f);
	close(fd);

	exit(EXIT_SUCCESS);
}