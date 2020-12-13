#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)\

bool osIsPublicFile(const char *fpath);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	if(osIsPublicFile(argv[1])){
		printf("true");
	}
	else{
		printf("false");
	}

	exit(EXIT_SUCCESS);
}

bool osIsPublicFile(const char *fpath){

	struct stat fInfo;
	check_error(stat(fpath, &fInfo) == -1, "stat() failure");
	check_error(!S_ISREG(fInfo.st_mode), "Not a regular file");

	if((fInfo.st_mode & S_IROTH) && (fInfo.st_mode & S_IWOTH)){
		return true;
	}
	else{
		return false;
	}

}
