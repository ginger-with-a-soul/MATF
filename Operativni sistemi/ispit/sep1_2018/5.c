#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>

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
	sem_t dataProcessingFinished;
	int array[ARRAY_MAX];
	unsigned arrayLen;
} OsInputData;

bool signChange = false, doubleChange = false;
void sigHandler(int signum);
void* getShmBlock(char* path, unsigned* size);

int main(int argc, char** argv){

	check_error(argc != 2, "invalid arg count");

	unsigned size = 0;

	OsInputData* data = getShmBlock(argv[1], &size);

	check_error(signal(SIGUSR1, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGUSR2, sigHandler) == SIG_ERR, "signal() failure");

	pause();

	if(signChange){
		//check_error(sem_wait(&(data->dataProcessingFinished)) != 0, "sem_wait() failure");
		for(int i = 0; i < data->arrayLen; i++){
			data->array[i] = -1 * data->array[i];
		}
		check_error(sem_post(&(data->dataProcessingFinished)) != 0, "sem_post() failure");
	}
	else if(doubleChange){
		//check_error(sem_wait(&(data->dataProcessingFinished)) != 0, "sem_wait() failure");
		for(int i = 0; i < data->arrayLen; i++){
			data->array[i] = 2 * data->array[i];
		}
		check_error(sem_post(&(data->dataProcessingFinished)) != 0, "sem_post() failure");
	}
	
	check_error(munmap(data, size) == -1, "munmap() failure");

	exit(EXIT_SUCCESS);
}

void* getShmBlock(char* path, unsigned* size){

	int memFD = shm_open(path, O_RDWR, 0600);
	check_error(memFD == -1, "shm_open() failure");

	struct stat fInfo;
	check_error(fstat(memFD, &fInfo) == -1, "fstat() failure");

	*size = fInfo.st_size;

	void* addr;
	check_error((addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, memFD, 0)) == MAP_FAILED,
	"mmap() failure");

	close(memFD);
	return addr;
}

void sigHandler(int signum){
	switch(signum){
		case SIGUSR1: signChange = true; break;
		case SIGUSR2: doubleChange = true; break;
		default: break;
	}
}