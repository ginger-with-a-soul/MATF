#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <sys/wait.h>
#include <pthread.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define osCheckPthread(pthreadErr, userMsg) \
    do { \
      int __pthreadErr = (pthreadErr); \
      if (__pthreadErr) { \
        errno = __pthreadErr; \
        osAssert(false, userMsg); \
      } \
    } while (0)
    
static const char *os_Usage = "./3 pathToFile";
    
void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);

typedef struct {
	
	int row;
} osThreadFuncArgumentType;

void* osThreadFunc(void* arg);

double globalSum = 0;
pthread_mutex_t globalLock;

int N = 0;
double** matrixA;
double** matrixB;

int main(int argc, char** argv) {
	
	osAssert(argc == 2, os_Usage);
	
	FILE* f = fopen(argv[1],"r");
	osAssert(f != NULL, "file open failed");
	
	fscanf(f, "%d", &N);
	
	int i = 0, j = 0;
	matrixA = malloc(N * sizeof(double*));
	osAssert(matrixA != NULL, "allocation failed");
	matrixB = malloc(N * sizeof(double*));
	osAssert(matrixB != NULL, "allocation failed");
	for (i = 0; i < N; i++) {
		matrixA[i] = malloc(N*sizeof(double));
		osAssert(matrixA[i] != NULL, "allocation failed");
		matrixB[i] = malloc(N*sizeof(double));
		osAssert(matrixB[i] != NULL, "allocation failed");
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++){
			fscanf(f, "%lf", &matrixA[i][j]);
		}
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++){
			fscanf(f, "%lf", &matrixB[i][j]);
		}
	}
	
	fclose(f);
	
	pthread_t* tids = malloc(N*sizeof(pthread_t));
	osAssert(tids != NULL, "tids allocation failed");
	osThreadFuncArgumentType *args = malloc(N*sizeof(osThreadFuncArgumentType));
	osAssert(args != NULL, "args allocation failed");
	
	osCheckPthread(pthread_mutex_init(&globalLock, NULL), "mutex init failed");
	
	for (i = 0; i < N; i++) {
		args[i].row = i;
		osCheckPthread(pthread_create(&tids[i], NULL, osThreadFunc, (void*)&args[i]), "Thread creation failed");
	}
	
	for (i = 0; i < N; i++) {
		
		osCheckPthread(pthread_join(tids[i], NULL), "Thread joining failed");
	}
	
	osCheckPthread(pthread_mutex_destroy(&globalLock), "mutex lock destroy failed");
	
	printf("%lf\n", globalSum);
	
	for (i = 0; i < N; i++) {
		free(matrixA[i]);
		free(matrixB[i]);
	}
		
	free(matrixA);
	free(matrixB);
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}

void* osThreadFunc(void* arg) {
	
	osThreadFuncArgumentType* args = (osThreadFuncArgumentType*) arg;
	
	double localSum = 0;
	int i;
	
	for (i = 0; i < N; i++) {
		
		localSum += matrixA[args->row][i]*matrixB[args->row][i];
	}
	
	osCheckPthread(pthread_mutex_lock(&globalLock), "mutex lock failed");
	globalSum+=localSum;
	osCheckPthread(pthread_mutex_unlock(&globalLock),"mutex unlock failed");
	
	return NULL;
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
