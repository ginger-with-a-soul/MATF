#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 1024

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

bool walk(char* path, unsigned* min, unsigned* max);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISDIR(fInfo.st_mode), "Not a dir");

	unsigned min = UINT_MAX, max = 0;
	check_error(!walk(argv[1], &min, &max), "walk() failure");

	printf("%u\n", max - min);

	exit(EXIT_SUCCESS);

}

bool walk(char* path, unsigned* min, unsigned* max){

	struct stat fInfo;
	if(lstat(path, &fInfo) == -1){
		return false;
	}

	if(S_ISREG(fInfo.st_mode)){
			if(fInfo.st_size > *max){
				*max = fInfo.st_size;
			}

			if(fInfo.st_size < *min){
				*min = fInfo.st_size;
			}
		}

	if(!S_ISDIR(fInfo.st_mode)){
		return true;
	}

	DIR* dir = opendir(path);
	if(dir == NULL){
		return false;
	}

	struct dirent* cd;
	while((cd = readdir(dir)) != NULL){
		char* newPath = malloc(strlen(path) + 1 + strlen(cd->d_name) + 1);
		check_error(newPath == NULL, "malloc() failure");
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, cd->d_name);


		if(!strcmp(cd->d_name, ".") || !strcmp(cd->d_name, "..")){
			if(stat(newPath, &fInfo) == -1){
				free(newPath);
			return false;
			}
			
			free(newPath);
			continue;
		}

		bool status = walk(newPath, min, max);
		free(newPath);
		if(status == false){
			return false;
		}
	}

	if(closedir(dir) == -1){
		return false;
	}

	return true;

}