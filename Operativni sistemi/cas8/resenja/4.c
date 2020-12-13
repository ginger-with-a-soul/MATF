#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <semaphore.h>

#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

#define MAX_SIZE (1024)

typedef struct {
	
	sem_t ready;
	sem_t sorted;
	double array[MAX_SIZE];
	unsigned n;
} shmType;

void* getMemoryBlock(const char* path, unsigned* size);

int main(int argc, char** argv) {
	
	check_error(argc == 2, "invalid args");
	
	unsigned size = 0;
	shmType* data = getMemoryBlock(argv[1], &size);
	
	check_error(sem_wait(&(data->ready)) != -1, "");
	
	int i,j;
	for (i = 0; i < data->n; i++){
		for (j = i+1; j < data->n; j++){
			if (data->array[j] < data->array[i]) {
				double tmp = data->array[j];
				data->array[j] = data->array[i];
				data->array[i] = tmp;
			}
		}
	}
	
	check_error(sem_post(&(data->sorted)) != -1, "");
	
	check_error(munmap(data, size) != -1, "unmap failed");

	exit(EXIT_SUCCESS);
}

void* getMemoryBlock(const char* path, unsigned* size) {
		
		int memFd = shm_open(path, O_RDWR, 0);
		check_error(memFd != -1, "shm_open failed");
		
		struct stat fInfo;
		check_error(fstat(memFd, &fInfo) != -1, "stat failed");
		*size = fInfo.st_size;
		
		void* addr;
		addr = mmap(NULL, *size, PROT_WRITE | PROT_READ, MAP_SHARED, memFd, 0);
		check_error(addr != MAP_FAILED, "mmap failed");
		
		close(memFd);
		
		return addr;
}
