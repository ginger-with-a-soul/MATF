#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/resource.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define check_pthreadErr(errPthread, userMsg)\
	do {\
		int _errPthread = errPthread;\
		if(_errPthread){\
			errno = _errPthread;\
			check_error(1, userMsg);\
		}\
	} while(0)\

pthread_mutex_t mutex;
double globalMin = 0;
double** matrix;
int rows, cols;

typedef struct {
	int rows;
	int cols;
} myStruct_t;

void* threadRoutine(void* args);

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count\n");

	FILE* f;
	check_error((f = fopen(argv[1], "r")) == NULL, "fopen() failure\n");

	fscanf(f, "%i %i", &rows, &cols);

	pthread_t* tids;
	check_error((tids = malloc(sizeof(pthread_t) * rows)) == NULL, "malloc() failure\n");
	check_pthreadErr(pthread_mutex_init(&mutex, NULL), "pthread_mutex_init() failure\n");

	check_error((matrix = malloc(sizeof(double*) * rows)) == NULL, "malloc() failure\n");
	for(int i = 0; i < rows; i++){
		check_error((matrix[i] = malloc(sizeof(double) * cols)) == NULL, "malloc() failure\n");
	} 

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fscanf(f, "%lf", &matrix[i][j]);
		}
	}

	myStruct_t argumenti;
	argumenti.cols = cols;

	for(int i = 0; i < rows; i++){
		argumenti.rows = i;
		check_pthreadErr(pthread_create(&tids[i], NULL, threadRoutine, (void*) &argumenti), "pthread_create() failure\n");
	}

	for(int i = 0; i < rows; i++){
		check_pthreadErr(pthread_join(tids[i], NULL), "pthread_join() failure\n");
	}

	printf("%lf\n", globalMin);
	
	check_pthreadErr(pthread_mutex_destroy(&mutex), "pthread_mutex_destroy() failure\n");
	for(int i = 0; i < rows; i++){
		free(matrix[i]);
	}
	free(matrix);
	fclose(f);
	free(tids);
	exit(EXIT_SUCCESS);
}

void* threadRoutine(void* args){
	myStruct_t* arg = (myStruct_t*) args;
	double localMin = matrix[arg->rows][0];
	for(int i = 1; i < arg->cols; i++){
		if(localMin > matrix[arg->rows][i]){
			localMin = matrix[arg->rows][i];
		}
	}

	check_pthreadErr(pthread_mutex_lock(&mutex), "pthread_mutex_lock() failure\n");
	if(globalMin > localMin){
		globalMin = localMin;
	}
	check_pthreadErr(pthread_mutex_unlock(&mutex), "pthread_mutex_unlock() failure\n");

	return NULL;
}