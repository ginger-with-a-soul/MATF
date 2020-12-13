#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <errno.h>
#include <pthread.h>

#include <sys/mman.h>
#include <semaphore.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)

#define osPthreadCheck(pthreadErr, userMsg) \
	do { \
		int _pthreadErr = (pthreadErr); \
		if (_pthreadErr > 0) { \
			 errno = _pthreadErr; \
			 osAssert(false, userMsg); \
		 }\
	} while (0)

const char* osUsage = "./hello_thread numOfThreads";	

#define MAX_ARRAY 1024	
	
typedef struct {
	sem_t inDataReady;
	float array[MAX_ARRAY];
	unsigned arrayLen;
} OsInputData;
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum);

void* osGetMemoryBlock(char* filePath, int* size);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, osUsage);
	
	int size = 0;
	OsInputData* data = osGetMemoryBlock(argv[1], &size);
	
	osAssert(sem_wait(&(data->inDataReady))!=-1, "sem wait failed");
	
	int i, j;
	for (i = 0; i < data->arrayLen; i++) {
		for (j = i + 1; j < data->arrayLen; j++) {
			
			if (data->array[i] > data->array[j]) {
				
				float tmp = data->array[i];
				data->array[i] = data->array[j];
				data->array[j] = tmp;
			}
		}
	}
	
	printf("%f\n", data->array[data->arrayLen/2]);
	
	osAssert(munmap(data, size) != -1, "maunmap failed");
	
	exit(EXIT_SUCCESS);
}

void* osGetMemoryBlock(char* filePath, int* size) {
	
	int memFd = shm_open(filePath, O_RDWR, 0600);
	osAssert(memFd != -1, "shm_open faield");
	
	struct stat fInfo;
	osAssert(fstat(memFd, &fInfo) != -1, "fstat failed");
	*size = fInfo.st_size;
	
	void* addr;
	
	osAssert((addr = mmap(0, *size, PROT_READ|PROT_WRITE, MAP_SHARED, memFd, 0)) != MAP_FAILED, "mmap failed");
	
	close(memFd);
	
	return addr;
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}

