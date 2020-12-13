#define _XOPEN_SOURCE 700
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include <pthread.h>
#include <errno.h>

#define osErrorFatal(userMsg)  osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
#define osCheckPThread(expr, userMsg) \
	do { \
		int _error = (expr); \
		if (_error) { \
			errno = _error; \
			osAssert(0, userMsg); \
		} \
	} while (0)

#define DEBUG 1

typedef struct {
	
	int colNum;
} osThreadFuncArgument;
	
static char* osUsage = "Usage: ./2 filePath";

int** matrix;
int m,n;

pthread_mutex_t osLock = PTHREAD_MUTEX_INITIALIZER;
int osMax = 0;
bool initialized = false;


void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

void* osThreadFunc(void* arg) {
	
	osThreadFuncArgument* args = (osThreadFuncArgument*)arg;
	
	int localSum = 0;
	int i = 0;
	
	for (i = 0; i < m; i++)
		localSum += matrix[i][args->colNum];
		
	osCheckPThread(pthread_mutex_lock(&osLock), "Mutex lock failed");
	if (initialized) {
		
		if (localSum > osMax)
			osMax = localSum;
	}
	else {
		initialized = true;
		osMax = localSum;
	}
	osCheckPThread(pthread_mutex_unlock(&osLock), "Mutex unlock failed");
#ifdef DEBUG
	printf("%d (%d)\n", localSum, args->colNum);
#endif
	return NULL;
}

int main(int argc, char** argv) {
	
	int i = 0, j = 0;
	osAssert(argc == 2, osUsage);
	
	FILE* f = fopen(argv[1], "r");
	fscanf(f, "%d%d", &m, &n);
	
	matrix = malloc(m*sizeof(int*));
	osAssert(matrix != NULL, "Pointer allocation failed");
	for (i = 0; i < m; i++) {
		
		matrix[i] = malloc(n*sizeof(int));
		osAssert(matrix[i] != NULL, "Row allocation failed");
	}
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			fscanf(f, "%d", &matrix[i][j]);
		}
	}
	
	fclose(f);
	
	pthread_t* tids = malloc(n*sizeof(pthread_t));
	osAssert(tids != NULL, "tid allocation failed");
	osThreadFuncArgument* args = malloc(n*sizeof(osThreadFuncArgument));
	osAssert(args != NULL, "args allocation failed");
	
	for (i = 0; i < n; i++) {
		args[i].colNum = i;
		osCheckPThread(pthread_create(&tids[i], NULL, osThreadFunc, &args[i]), "Thread creation failed");
	}
	
	for (i = 0; i < n; i++) {
		osCheckPThread(pthread_join(tids[i], NULL), "Thread joining failed");
	}
	
	osCheckPThread(pthread_mutex_destroy(&osLock), "Mutex destroy failed");

	printf("%d\n", osMax);
	
	for (i = 0; i < m; i++)
		free(matrix[i]);
	free(matrix);
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
