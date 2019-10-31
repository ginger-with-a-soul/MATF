#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
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

bool walk(char* path, char* ext, unsigned* num);

int main(int argc, char** argv){
	check_error(argc != 3, "Invalid arg count!");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISDIR(fInfo.st_mode), "Not a dir");

	char* ext = malloc(strlen(argv[2]) + 1);
	check_error(ext == NULL, "malloc() failure");
	strcpy(ext, argv[2]);

	unsigned num = 0;

	check_error(!walk(argv[1], ext, &num), "walk() failure");

	printf("%u\n", num);

	free(ext);
	exit(EXIT_SUCCESS);
}

bool walk(char* path, char* ext, unsigned* num){

	struct stat fInfo;
	if(lstat(path, &fInfo) == -1){
		return false;
	}
	if(S_ISREG(fInfo.st_mode)){
		char* tmpStr = malloc(strlen(path));
		check_error(tmpStr == NULL, "malloc() failure");
		tmpStr = strrchr(path, '.');

		if(tmpStr != NULL){
			if(!strcmp(tmpStr, ext)){
				*num += 1;
			}
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

		bool state = walk(newPath, ext, num);
		if(!state){
			return false;
		}
	}

	//free(tmpStr);

	if(closedir(dir) == -1){
		return false;
	}

	return true;

}
