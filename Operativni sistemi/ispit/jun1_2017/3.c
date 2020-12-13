#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <pthread.h>
#include <errno.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
		
#define osCheckPThread(pthread_error, userMsg) \
	do{ \
		int pthreadErr = pthread_error; \
		if (pthreadErr > 0) { \
			errno = pthreadErr; \
			osErrorFatal(userMsg);\
		} \
	} while( 0)

typedef struct 
{
		int row;
		int col;
} OsThreadFunctionInputType;

int** matrixA;
int** matrixB;
int** matrixC;
int maximum;
int n,m,k;
int initialized = 0;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum);

void* osThreadFunction(void* arg) {
	
	OsThreadFunctionInputType* args = (OsThreadFunctionInputType*)arg;
	int result = 0;
	int i = 0;
	
	// calculate element
	for (i = 0; i < m; i++) {
		result += matrixA[args->row][i]*matrixB[i][args->col];
	}
	
	// acquire mutex
	osCheckPThread(pthread_mutex_lock(&globalLock), "mutex lock failed");
	
	// store result and check max
	matrixC[args->row][args->col] = result;
	if (!initialized) {
		maximum = result;
		initialized = 1;
	}
	else {
			if (result > maximum) {
				maximum = result;
			}
	}
	
	// release mutex
	osCheckPThread(pthread_mutex_unlock(&globalLock), "mutex unlock failed");
}

int main(int argc, char** argv) {
	
	int i,j;
	
	// read data
	scanf("%d%d", &n, &m);
	
	matrixA = malloc(n*sizeof(int*));
	osAssert(matrixA != NULL, "malloc failed");
	for (i = 0; i < n; i++) {
		matrixA[i] = malloc(m*sizeof(int));
		osAssert(matrixA[i] != NULL, "malloc failed");
	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", &matrixA[i][j]);			
		}
	}
	
	scanf("%d%d", &m, &k);
	
	matrixB = malloc(m*sizeof(int*));
	osAssert(matrixB != NULL, "malloc failed");
	for (i = 0; i < m; i++) {
		matrixB[i] = malloc(k*sizeof(int));
		osAssert(matrixB[i] != NULL, "malloc failed");
	}
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < k; j++) {
			scanf("%d", &matrixB[i][j]);			
		}
	}
	
	matrixC = malloc(n*sizeof(int*));
	osAssert(matrixC != NULL, "malloc failed");
	for (i = 0; i < n; i++) {
		matrixC[i] = malloc(k*sizeof(int));
		osAssert(matrixC[i] != NULL, "malloc failed");
	}
	
	// init threads
	pthread_t* tids = malloc(n*k*sizeof(pthread_t));
	osAssert(tids != NULL, "malloc failed");
	
	OsThreadFunctionInputType* args = malloc(n*k*sizeof(OsThreadFunctionInputType));
	osAssert(args != NULL, "malloc failed");
	
	// start threads
	for (i = 0; i < n; i++) {
		for (j = 0; j < k; j++) {
			args[i*k + j].row = i;
			args[i*k + j].col = j;
			
			osCheckPThread(pthread_create(&tids[i*k + j], NULL, osThreadFunction, &args[i*k + j]), "pthread_create failed");
		}
	}
	
	// join threads
	for (i = 0; i < n*k; i++) {
		osCheckPThread(pthread_join(tids[i], NULL), "pthread_join failed");
	}
	
	// destory mutex
	osCheckPThread(pthread_mutex_destroy(&globalLock), "mutex destroy failed");
	
	// print matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < k; j++) {
			printf("%d ", matrixC[i][j]);
		}
		printf("\n");
	}
	// print max
	printf("%d\n", maximum);
	
	// free resources
	for (i = 0; i < m; i++) {
		free(matrixB[i]);
	}
	free(matrixB);
	
	for (i = 0; i < n; i++) {
		free(matrixA[i]);
	}
	free(matrixA);
	
	for (i = 0; i < n; i++) {
		free(matrixC[i]);
	}
	free(matrixC);
	
	free(tids);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}
