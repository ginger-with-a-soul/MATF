#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <semaphore.h>
#include <sys/mman.h>

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
	int array[ARRAY_MAX];
	unsigned arrayLen;
} OsData;

void* getShmData(char* path, unsigned* size);
void* createShmData(char* path, unsigned size);
int bin_one(int x);

int main(int argc, char** argv){

	check_error(argc != 3, "invalid arg count");

	unsigned size1 = 0, size2 = 0;
	OsData* dataIn = getShmData(argv[1], &size1);
	OsData* dataOut = getShmData(argv[2], &size2);

	dataOut->arrayLen = 0;


	check_error(sem_wait(&(dataIn->inDataReady)) == -1, "sem_post() failure");
	for(int i = 0; i < dataIn->arrayLen; i++){
		//check_error(sem_wait(&(dataIn->inDataReady)) == -1, "sem_wait() failure");
		if(bin_one(dataIn->array[i]) > 3){
			dataOut->array[dataOut->arrayLen++] = dataIn->array[i];
		}
	}
	check_error(sem_post(&(dataOut->inDataReady)) == -1, "sem_post() failure");

	check_error(munmap(dataIn, size1) == -1, "munmap() failure");
	check_error(munmap(dataOut, size2) == -1, "munmap() failure");

	exit(EXIT_SUCCESS);
}

void* getShmData(char* path, unsigned* size){
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

void* createShmData(char* path, unsigned size){
	int memFD = shm_open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	check_error(memFD == -1, "shm_open() failure");

	check_error(ftruncate(memFD, size) == -1, "ftruncate() failure");

	void* addr;
	check_error((addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memFD, 0))
	== MAP_FAILED, "mmap() failure");

	return addr;
}

int bin_one(int x){
	int num = 0;
	while(x){
		if(x & 1){
			num++;
		}
		x <<= 1;
	}
	return num;
}