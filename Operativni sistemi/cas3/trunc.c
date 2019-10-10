#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <time.h>
#include <utime.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count...\nTerminating!\n");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure...\nTerminating!\n");

	FILE *f = fopen(argv[1], "w");
	check_error(f == NULL, "fopen() failure...\nTerminating!\n");
	fclose(f);

	struct utimbuf time;
	
	time.actime = fInfo.st_atim.tv_sec;
	time.modtime = fInfo.st_mtim.tv_sec;

	check_error(utime(argv[1], &time) == -1, "utime() failure...\nTerminating!\n");

	exit(EXIT_SUCCESS);
}