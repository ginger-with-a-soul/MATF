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

#include <stdatomic.h>

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

atomic_int global;

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc < 2 , "Invalid arg count");

	atomic_init(&global, 0);

	int threadNum = argc - 1;

	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, argv[i+1]) != 0, "pthread_create() failure");
	}

	for(int i = 0; i < threadNum; i++){
		check_pthreadErr(pthread_join(tids[i], NULL) != 0, "pthread_join() failure");
	}

	printf("Total: %i\n", atomic_load(&global));

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

	check_error(feof(f) == 0, "EOF failure");
	fclose(f);

	atomic_fetch_add(&global, localSum);

	return NULL;

}