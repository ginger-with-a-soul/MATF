#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <stdbool.h>
#include <dirent.h>
#include <time.h>

#define MAX_SIZE 1024
#define DAY (60*60*24)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

bool walk(char* path);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "lstat() failure");
	check_error(!S_ISDIR(fInfo.st_mode), "Not a dir");

	check_error(!walk(argv[1]), "walk() failure");

	exit(EXIT_SUCCESS);

}

bool walk(char* path){

	struct stat fInfo;
	if(lstat(path, &fInfo) == -1){
		return false;
	}

	if(S_ISREG(fInfo.st_mode)){
		time_t diff = time(NULL) - (time_t)fInfo.st_mtim.tv_sec;
		if(diff <= 5 * DAY){
			char* cp = malloc(strlen(path) + 1);
			cp = strrchr(path, '/');
			printf("%s\n", cp + 1);
		}
	}

	if(!S_ISDIR(fInfo.st_mode)){
		return true;
	}

	DIR* dir = opendir(path);
	if(dir == NULL){
		return false;
	}
	struct dirent* currDir;
	while((currDir = readdir(dir)) != NULL){
		char* newPath = malloc(strlen(path) + 1 + strlen(currDir->d_name) + 1);
		check_error(newPath == NULL, "malloc() failure");
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, currDir->d_name);

		if(!strcmp(currDir->d_name, ".") || !strcmp(currDir->d_name, "..")){
			if(stat(newPath, &fInfo) == -1){
				free(newPath);
			return false;
			}

			free(newPath);
			continue;
		}

		bool state = walk(newPath);
		free(newPath);
		if(state == false){
			return false;
		}

	}

	if(closedir(dir) == -1){
		return false;
	}
	return true;
}