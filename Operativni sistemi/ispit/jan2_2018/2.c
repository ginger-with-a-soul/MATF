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
#include <limits.h>

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

double* vector;
unsigned size = 0;
void* thread_func(void* arg);
double globalMin = MAXFLOAT;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv){

	check_error(argc != 1, "invalid arg count");

	vector = malloc(sizeof(double) * MAX_SIZE);
	check_error(vector == NULL, "malloc() failure");

	for(size = 0; scanf("%lf %lf", &vector[size], &vector[size + 1]) == 2; size += 2){}

	pthread_t* tids = malloc(sizeof(pthread_t) * (size / 2));
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < (size / 2); i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t)i),
		"pthread_create() failure");
	}

	for(int i = 0; i < (size / 2); i++){
		check_pthreadErr(pthread_join(tids[i], NULL), "pthread_join() failure");
	}
	
	printf("%lf\n", globalMin);

	free(vector);
	free(tids);

	check_pthreadErr(pthread_mutex_destroy(&globalLock), "pthread_mutex_destroy() failure");

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	int argument = (int)(intptr_t)arg;
	double localMin = MAXFLOAT, distance = 0;
	double localX = vector[argument * 2], localY = vector[argument * 2 + 1];

	for(int i = 0; i < argument; i++){
		distance = sqrt(pow(vector[2 * i] - localX, 2) + pow(vector[2 * i + 1] - localY, 2));
		if(!i){
			localMin = distance;
		}
		else{
			localMin = localMin > distance? distance : localMin;
		}
	}

	check_pthreadErr(pthread_mutex_lock(&globalLock) == -1, "pthread_mutex_lock() failure");
	globalMin = globalMin > localMin? localMin : globalMin;
	check_pthreadErr(pthread_mutex_unlock(&globalLock) == -1, "pthread_mutex_unlock() failure")

	return NULL;
}