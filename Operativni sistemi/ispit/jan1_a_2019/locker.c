#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>


#define MAX_SIZE (1024)
#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\



int main(int argc, char** argv){

	check_error(argc != 3, "invalid arg count");

	int fd = open(argv[1], O_RDWR);
	check_error(fd == -1, "open() failure");

	FILE* f = fopen(argv[2], "r+");
	check_error(f == NULL, "fopen() failure");

	struct flock lock;

	int a, b, c;

	while(fscanf(f, "%i %i %i", &a, &b, &c) == 2){
		lock.l_type = c == 1? F_WRLCK : F_RDLCK;
		lock.l_whence = SEEK_CUR;
		lock.l_start = a;
		lock.l_len = b;

		check_error(fcntl(fd, F_SETLK, &lock ) == -1, "fcntl() failure");

	}

	char cr;
	do {
		cr = getchar();
	} while(cr != 'n');

	close(fd);
	fclose(f);

	exit(EXIT_SUCCESS);
}