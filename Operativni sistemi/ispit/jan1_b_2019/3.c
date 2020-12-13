#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

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

int m, n, k;
float** matrix;
void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc != 1, "invalid arg count");

	scanf("%d %d %d", &m, &n, &k);
	matrix = malloc(sizeof(float*) * (m + 1));
	check_error(matrix == NULL, "malloc() failure");

	float globalMax = 0;
	int threadID = 0;

	for(int i = 0; i < m + 1; i++){
		matrix[i] = malloc(sizeof(float) * n);
		check_error(matrix[i] == NULL, "malloc() failure");
		for(int j = 0; j < n; j++){
			scanf("%f", &matrix[i][j]);
		}
	}

	pthread_t* tids = malloc(sizeof(pthread_t) * k);
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < k; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t) i), "pthread_create() failure");
	}

	float* ret;

	for(int i = 0; i < k; i++){
		check_error(pthread_join(tids[i], (void**)&ret), "pthread_join() failure");
		
		if(!i){
			globalMax = *ret;
			threadID = i + 1;
		}
		else{
			if(globalMax < *ret){
				globalMax = *ret;
				threadID = i + 1;
			}
		}
		
		free(ret);
	}

	printf("%d %f\n", threadID, globalMax);

	for(int i = 0; i < m + 1; i++){
		free(matrix[i]);
	}
	free(matrix);
	free(tids);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	int argument = (int)(intptr_t) arg;
	float currentMax = 0;
	float *localMax = malloc(sizeof(float));
	check_error(localMax == NULL, "malloc() failure");

	int pos = argument * (m/k);

	for(int i = pos, z = 0; z < m / k ; i++, z++){
		currentMax = 0;
		for(int j = 0; j < n; j++){
			currentMax += matrix[i][j] * matrix[m][j];
		}
		if(!z){
			*localMax = currentMax;
		}
		else{
			*localMax = *localMax < currentMax? currentMax : *localMax;
		}
	}
	
	return localMax;
}