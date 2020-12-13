#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <dirent.h>

#include <string.h>

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

bool traverseDir(char* path, unsigned* size);

int main(int argc, char** argv) {

	check_error(argc != 2, "./sizeOfDir path");
	
	/* proveravamo da li je argument direktorijum */
	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat failed");
	check_error(!S_ISDIR(fInfo.st_mode), "not a dir");
	
	/* i ako jeste, obilazimo ga i racunamo njegovu velicinu */
	unsigned size = 0;
	check_error(!traverseDir(argv[1], &size), "dir traversal failed");
	
	/* stampamo velicinu koju smo izracunali */
	printf("Dir size: %u\n", size);
	
	/* zavrsavamo program sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}

bool traverseDir(char* path, unsigned* size){
	
	struct stat fInfo;
	if(lstat(path, &fInfo) == -1){
		return false;
	}

	*size += fInfo.st_size;

	if(!S_ISDIR(fInfo.st_mode)){
		return true;
	}

	DIR* dir = opendir(path);
	if(dir == NULL){
		return false;
	}

	struct dirent* dirInfo;

	while((dirInfo = readdir(dir)) != NULL){
		char* newPath = malloc(strlen(path) + 1 + strlen(dirInfo->d_name) + 1);
		check_error(newPath == NULL, "malloc() failure");
		strcat(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, dirInfo->d_name);

		if(!strcmp(dirInfo->d_name, ".") || !strcmp(dirInfo->d_name, "..")){
			if(stat(newPath, &fInfo) == -1){
				free(newPath);
				return false;
			}

			*size += fInfo.st_size;
			free(newPath);
			continue;
		}

		bool state = traverseDir(newPath, size);
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