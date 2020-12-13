#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <semaphore.h>

#include <math.h>

#define check_error(expr, userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)
	
#define MAX_SIZE (1024)

typedef struct {
	sem_t ready;
	sem_t done;
	double points[MAX_SIZE];
	int n;
} MemBlock_t;

void* getMemBlock(char* path, unsigned* size) {
	
	int memFd = shm_open(path, O_RDWR, 0600);
	check_error(memFd != -1, "...");
	
	struct stat fInfo;
	check_error(fstat(memFd, &fInfo) != -1, "...");
	*size = fInfo.st_size;
	
	void* addr;
	addr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	check_error(addr != MAP_FAILED, "...");
	
	close(memFd);
	
	return addr;
}


int main(int argc, char** argv) {
	
	check_error(argc == 2, "...");
	
	unsigned size = 0;
	MemBlock_t* block = getMemBlock(argv[1], &size);
	
	double distance = 0;
	check_error(sem_wait(&(block->ready)) != -1, "....");
	if (block->n > 1) {
			
		distance = (block->points[0] - block->points[2])*(block->points[0] - block->points[2]) + (block->points[1] - block->points[3])*(block->points[1] - block->points[3]);
		for (int i = 0; i < block->n; i++) {
			for (int j = i+1; j < block->n; j++) {
				
				double tmp = (block->points[i*2] - block->points[j*2])*(block->points[i*2] - block->points[j*2]) + (block->points[i*2+1] - block->points[j*2+1])*(block->points[i*2+1] - block->points[j*2+1]);
				if (tmp < distance) {
					
					distance = tmp;
				}
			}
		}
	}
	check_error(sem_post(&(block->done)) != -1, "...");
	
	printf("%lf\n", sqrt(distance));
	
	check_error(munmap((void*)block, size) != -1, "...");
	
	exit(EXIT_SUCCESS);
}
