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

#include <time.h>

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

void* osCreateMemoryBlock(char* filePath, unsigned size);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, osUsage);
	
	/* proces mora da kreira blok deljene memorije
	 * koji koristi Vas zadatak
	 */
	OsInputData* data = osCreateMemoryBlock(argv[1], sizeof(OsInputData));
	
	/* proces koji puni deljenu memoriju MORA da inicijalizuje
	 * semafor. 
	 * Proces koji koristi semafor, tj. vas zadatak, NE SME da inicijalizuje memoriju
	 * Visestruko inicijalizovanje semafora dovodi do nedefinisanog ponasanja
	 */
	 osAssert(sem_init(&data->inDataReady, 1, 0) != -1, "sem init failed"); 
	
	/* seme generatora brojeva */
	srand(time(NULL));
	
	/* slucajan broj inicijalizuje broj elemenata */
	data->arrayLen = rand() % MAX_ARRAY;
	
	
	int i, j;
	for (i = 0; i < data->arrayLen; i++) {
		data->array[i] = (float)(rand()/(float)RAND_MAX);
	}
	
	/* za debug naci medijanu ovde, pa odstampati i uporediti rezultate 
	 * sa rezultatima vaseg programa ...
	 */
	
	
	/* postovanjem na semaforu obavestava se Vas zadatak da su podaci spremni */
	osAssert(sem_post(&data->inDataReady) != -1, "sem post failed");
	
	osAssert(munmap(data, sizeof(OsInputData)) != -1, "munmap failed");
	
	exit(EXIT_SUCCESS);
}

void* osCreateMemoryBlock(char* filePath, unsigned size) {
	
	int memFd = shm_open(filePath, O_RDWR | O_CREAT, 0600);
	osAssert(memFd != -1, "shm_open faield");
	
	
	osAssert(ftruncate(memFd, size) != -1, "ftruncate failed");
	
	void* addr;
	
	osAssert((addr = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, memFd, 0)) != MAP_FAILED, "mmap failed");
	
	close(memFd);
	
	return addr;
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}

