#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE (1024)
#define DAY (25*60*60)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

unsigned osNumOfDaysFileModified(const char *fpath);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	unsigned val = osNumOfDaysFileModified(argv[1]);

	printf("%i\n", val);

	exit(EXIT_SUCCESS);
}

unsigned osNumOfDaysFileModified(const char *fpath){

	struct stat fInfo;
	check_error(stat(fpath, &fInfo) == -1, "stat() failure");

	struct timespec modTime = fInfo.st_mtim;

	time_t now = time(NULL);

	return (now - modTime.tv_sec) / DAY;

}
