#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>


#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define LOCAL_SEM (0)

#define LOCAL_SEM (0)
#define PROC_SEM (!LOCAL_SEM)

typedef struct {
	sem_t ready;
	sem_t sorted;
	double array[MAX_SIZE];
	unsigned n;
} shmType;

void* getSharedBlock(char* path, unsigned* size);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	unsigned size = 0;
	shmType* data = getSharedBlock(argv[1], &size);

	//check_error(sem_init(&(data->ready), PROC_SEM, 1) == -1, "sem_init() failure");
	//check_error(sem_init(&(data->sorted), PROC_SEM, 0) == -1, "sem_init() failure");

	check_error(sem_wait(&(data->ready)) == -1, "sem_wait() failure");
	

	int tmp;
    for(int i = 0; i < data->n; i++){
		for(int j = 0; j < data->n; j++){
			if(data->array[i] < data->array[j]){
				tmp = data->array[j];
				data->array[j] = data->array[i];
				data->array[i] = tmp;
			}
		}
	}

	check_error(sem_post(&(data->sorted)) == -1, "sem_wait() failure");

	check_error(munmap(data, size) == -1, "munmap() failure");

	exit(EXIT_SUCCESS);
}


void* getSharedBlock(char* path, unsigned* size){

	int fd = shm_open(path, O_RDWR, 0);
	check_error(fd == -1, "shm_open() failure");
	
	struct stat fInfo;
	check_error(fstat(fd, &fInfo) == -1, "fstat() failure");
	*size = fInfo.st_size;

	void* addr;
	check_error(mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0) == MAP_FAILED, "mmap() failure");

	close(fd);
	return addr;
}