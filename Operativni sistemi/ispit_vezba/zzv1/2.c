#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <pthread.h>
#include <ctype.h>

#define MAX_SIZE (127)

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


pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t globalSignaler = PTHREAD_COND_INITIALIZER;

int globalSync = 0;
char buffer[MAX_SIZE];

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	int threadNum = atoi(argv[1]);

	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");


	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t)i+1), "pthread_create() failure");
	}

	while(1){
		check_pthreadErr(pthread_mutex_lock(&globalLock), "pthread_mutex_lock() failure");

		if(globalSync != 0){
			check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
			continue;
		}

		scanf("%i", &globalSync);

		if(globalSync == -1){
			check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
			check_pthreadErr(pthread_cond_broadcast(&globalSignaler), "pthread_cond_broadcast() failure");
			break;
		}

		scanf("%s", buffer);

		check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
		check_pthreadErr(pthread_cond_broadcast(&globalSignaler), "pthread_cond_broadcast() failure");
	}

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_join(tids[i], NULL), "pthread_join() failure");
	}

	free(tids);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){

	int index = (int)(intptr_t) arg;

	while(1){
		check_pthreadErr(pthread_mutex_lock(&globalLock), "pthread_mutex_lock() failure");
		while(globalSync == 0){
			check_pthreadErr(pthread_cond_wait(&globalSignaler, &globalLock), "pthread_cont_wait() failure");
		}

		if(globalSync == -1){
			check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
			break;
		}
		
		if(globalSync != index){
			check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
			continue;
		}

		int lowerChars = 0;

		for(int i = 0; buffer[i] != 0; i++){
			if(islower(buffer[i])){
				lowerChars++;
			}
		}

		printf("%i %i\n", index, lowerChars);

		globalSync = 0;

		check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_unlock() failure");
	}

	return NULL;
}