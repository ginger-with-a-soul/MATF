#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>

#include <pthread.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

#define check_pthreadErr(pthreadErr, usrMsg)\
	do {\
		int _pthreadErr = pthreadErr;\
		if(_pthreadErr){\
			errno = _pthreadErr;\
			check_error(1, usrMsg);\
		}\
	} while(0);\

double** matrix;
double p;
int m, n;
void* thread_func(void* arg);
double globalSum = 0;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv){

	check_error(argc != 1, "invalid arg count");
	scanf("%lf %d %d", &p, &m, &n);

	matrix = malloc(sizeof(double*) * m);
	check_error(matrix == NULL, "malloc() failure");
	for(int i = 0; i < m; i++){
		matrix[i] = malloc(sizeof(double) * n);
		check_error(matrix[i] == NULL, "malloc() failure");
		for(int j = 0; j < n; j++){
			scanf("%lf", &matrix[i][j]);
		}
	}

	pthread_t* tids = malloc(sizeof(pthread_t) * m);
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < m; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t)i),
		"pthread_create() failure");
	}

	for(int i = 0; i < m; i++){
		check_error(pthread_join(tids[i], NULL), "pthread_join() failure");
		free(matrix[i]);
	}

	printf("%lf\n", pow(globalSum, (1 / p)));

	free(matrix);
	free(tids);

	check_pthreadErr(pthread_mutex_destroy(&globalLock), "pthread_mutex_destroy() failure");

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	int argument = (int)(intptr_t)arg;
	double localSum = 0;

	for(int i = 0; i < n; i++){
		if(matrix[argument][i] < 0){
			localSum += pow(-1 * matrix[argument][i], p);
		}
		else{
			localSum += pow(matrix[argument][i], p);
		}
	}

	check_pthreadErr(pthread_mutex_lock(&globalLock), "pthread_mutex_lock() failure");
	globalSum += localSum;
	check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");

	return NULL;
}