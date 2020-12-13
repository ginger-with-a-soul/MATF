#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include <stdbool.h>

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

	check_error(argc != 2, "invalid arg count");

	FILE* f = fopen(argv[1], "r+");
	check_error(f == NULL, "fopen() failure");

	int fd = open(argv[1], O_RDWR);
	check_error(fd == -1, "open() failure");

	int x, i = 0;
	char buffer[MAX_SIZE];
	bool flag = false;

	struct flock lock;


	while(fscanf(f, "%s", buffer) == 1){

		check_error(strlen(buffer) > 256, "too long");

		flag = false;

		for(i = 0; i < 4; i++){
			if(!isdigit(buffer[i])){
				flag = true;
				break;
			}
		}

		if(flag || isdigit(buffer[i])){
			continue;
		}


		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_CUR;
		lock.l_start = ftell(f);
		lock.l_len = -4;

		check_error(fcntl(fd, F_GETLK, &lock) == -1, "fcntl() failure");

		if(lock.l_type == F_UNLCK){
			lock.l_type = F_WRLCK;
			check_error(fcntl(fd, F_SETLK, &lock) == -1, "fcntl() failure");
			check_error(fseek(f, -4, SEEK_CUR) == -1, "fseek() failure");
			fprintf(f, "####");
			//check_error(fcntl(fd, F_UNLCK, &lock) == -1, "fcntl() failure");
		}

	}


	fclose(f);
	close(fd);

	exit(EXIT_SUCCESS);
}