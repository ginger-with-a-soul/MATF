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

	FILE* f = fopen(argv[1], "r");
	check_error(f == NULL, "fopen() failure");

	int fd = open(argv[1], O_RDONLY);
	check_error(fd == -1, "open() failure");

	struct flock lock;
	char word[MAX_SIZE];
	int len = strlen(argv[2]);

	while(fscanf(f, "%s", word) == 1){

		check_error(strlen(word) > 255, "word too long");

		if(strcmp(word, argv[2])){
			continue;
		}

		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_CUR;
		lock.l_start = ftell(f);
		lock.l_len = -len;

		check_error(fcntl(fd, F_GETLK, &lock) == -1, "fcntl() failure");

		if(lock.l_type == F_WRLCK){
			printf("%i w\n", ftell(f) - len);
		}
		else if(lock.l_type == F_RDLCK){
			printf("%i r\n", ftell(f) - len);
		}
	}


	fclose(f);
	close(fd);

	exit(EXIT_SUCCESS);
}