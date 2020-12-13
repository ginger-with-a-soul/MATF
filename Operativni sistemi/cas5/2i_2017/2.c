#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

void osMkPublicDir(const char *dname);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	osMkPublicDir(argv[1]);

	exit(EXIT_SUCCESS);
}

void osMkPublicDir(const char *dname){

	mode_t oldUmask = umask(0);
	check_error(mkdir(dname, 0777) == -1, "mkdir() failure");
	umask(oldUmask);

}
