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
#include <math.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_SUCCESS);\
		}\
	} while(0)\

#define check_errorThread(pthreadErr, usrMsg)\
	do {\
		int _pthreadErr = pthreadErr;\
		if(_pthreadErr){\
			errno = _pthreadErr;\
			check_error(1, usrMsg);\
		}\
	} while(0)\

typedef struct {
	int threadNo;
} inputArg;

typedef struct {
	double res;
} outputArg;

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	int threadNum = atoi(argv[1]);
	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");

	inputArg* args = malloc(threadNum * sizeof(inputArg));
	check_error(args == NULL, "malloc() failure");

	for(int i = 0; i < threadNum; i++){
		args[i].threadNo = i;
		check_errorThread(pthread_create(&tids[i], NULL, thread_func, &args[i]), "pthread_create() failure");
	}

	for(int i = 0; i < threadNum; i++){
		outputArg* res = NULL;
		check_errorThread(pthread_join(tids[i], (void**)&res), "...");
		printf("Thread %i finished: %.2lf\n", i, res->res);

		free(res);
	}

	free(tids);
	free(args);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){

	inputArg* in = (inputArg*) arg;
	outputArg* out = malloc(sizeof(outputArg));
	check_error(out == NULL, "malloc() failure");
	printf("Thread num: %i\n", in->threadNo);

	out->res = sqrt(in->threadNo);

	return out;
}