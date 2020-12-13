#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <sys/mman.h>
#include <semaphore.h>

#define ARRAY_MAX (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

typedef struct {
	sem_t inDataReady;
	sem_t dataProcessed;
	char str[ARRAY_MAX];
} OsInputData;

void* getShmBlock(char* path, unsigned* size);

int main(int argc, char** argv){

	check_error(argc != 2, "invalid arg count");

	unsigned size = 0;
	OsInputData* data = getShmBlock(argv[1], &size);

	unsigned len = strlen(data->str);
	char word[ARRAY_MAX];

	check_error(sem_wait(&(data->inDataReady)) == -1, "sem_wait() failure");
	for(int i = 0, j = len - 1 ; i < len; i++, j--){
		word[i] = data->str[j];
	}
	word[len] = 0;
	strcpy(data->str, word);
	check_error(sem_post(&(data->dataProcessed)) == -1, "sem_post() failure");

	check_error(munmap(data, size) == -1, "munmap() failure");

	exit(EXIT_SUCCESS);
}

void* getShmBlock(char* path, unsigned* size){
	int memFD = shm_open(path, O_RDWR, 0644);
	check_error(memFD == -1, "shm_open() failure");

	struct stat fInfo;
	check_error(fstat(memFD, &fInfo) == -1, "fstat() failure");
	*size = fInfo.st_size;

	void* addr;
	check_error((addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, memFD, 0))
	== MAP_FAILED, "mmap() failure");

	close(memFD);
	return addr;
}