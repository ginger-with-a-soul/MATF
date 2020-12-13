#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <errno.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define check_pthreadErr(pthreadErr, usrMsg)\
	do {\
		int _pthreadErr = pthreadErr;\
		if(_pthreadErr){\
			errno = _pthreadErr;\
			check_error(1, usrMsg);\
		}\
	} while(0)\

pthread_mutex_t mutex;
int globalSum = 0;

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc < 2, "Invalid arg count");

	int threadNum = argc - 1;
	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");

	check_pthreadErr(pthread_mutex_init(&mutex, NULL), "pthread_mutex_init() failure");

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, argv[i + 1]) != 0, "pthread_create() failure");
	}

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_join(tids[i], NULL) != 0, "pthread_join() failure");
	}

	printf("Total: %i\n", globalSum);
	check_pthreadErr(pthread_mutex_destroy(&mutex) != 0, "pthread_mutex_destroy() failure");
	
	free(tids);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	char* path = (char*) arg;

	FILE* f = fopen(path, "r");
	check_error(f == NULL, "fopen() failure");

	int localSum = 0, x;
	while(fscanf(f, "%i", &x) == 1){
		localSum += x;
	}

	check_error(feof(f) == 0, "feof() failure");
	fclose(f);

	check_pthreadErr(pthread_mutex_lock(&mutex) != 0, "pthread_mutex_lock() failure");
	globalSum += localSum;
	check_pthreadErr(pthread_mutex_unlock(&mutex) != 0, "pthread_mutex_unlock() failure");

	return NULL;

}