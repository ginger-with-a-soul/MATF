#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

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

bool flag = false;

bool walk(char* path);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISDIR(fInfo.st_mode), "Not a dir");
	if(!strncmp(argv[1], "dir_", strlen("dir_"))){
		flag = true;
	}

	check_error(!walk(argv[1]), "walk() failure");

	exit(EXIT_SUCCESS);
}

bool walk(char* path){

	struct stat fInfo;
	if(lstat(path, &fInfo) == -1){
		return false;
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
		strcat(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, cd->d_name);

		if(stat(newPath, &fInfo) == -1){
			free(newPath);
			return false;
		}

		if(!strcmp(cd->d_name, ".") || !strcmp(cd->d_name, "..")){
			free(newPath);
			continue;
		}

		if(S_ISREG(fInfo.st_mode)){
			char* copy = malloc(strlen(newPath));
			check_error(copy == NULL, "malloc() failure");
			if(!flag && ((copy = strstr(newPath, "dir_")) != NULL)){
				if(copy - 1 == "/"){
					printf("%s\n", cd->d_name);
				}
			}else if(flag){
				printf("%s\n", cd->d_name);
			}

			//free(copy);
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
