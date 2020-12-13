#define _XOPEN_SOURCE 700

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
	check_error(argc != 4, "Invalid arg count\n");
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	check_error(a < 0 || b < 0, "Invalid arg a or b\n");

	int fd;
	check_error((fd = open(argv[1], O_RDONLY)) == -1, "open() failure\n");

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = a;
	lock.l_len = b;

	check_error(fcntl(fd, F_GETLK, &lock) == -1, "fcntl() failure\n");

	switch(lock.l_type){
		case F_UNLCK: printf("nlocked\n"); break;
		case F_RDLCK: printf("shared lock\n"); break;
		case F_WRLCK: printf("exclusive lock\n"); break;
		default: break;
	}

	close(fd);
	exit(EXIT_SUCCESS);
}