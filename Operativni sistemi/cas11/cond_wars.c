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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int dataCount = 0;
int array[MAX_SIZE];

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	int threadNum = atoi(argv[1]);
	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t) i) != 0, "pthread_create() failure");
	}

	
	char* lineptr = NULL;
	size_t size = 0;

	while(getline(&lineptr, &size, stdin) != -1){
		
	}
	

	free(tids);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){

}