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

	#define check_pThreadErr(pthreadErr, usrMsg)\
		do {\
			int _pthreadErr = pthreadErr;\
			if(_pthreadErr){\
				errno = _pthreadErr;\
				check_error(1, usrMsg);\
			}\
		} while(0)\

typedef struct {
	unsigned index;
	char* filename;
} inThread_t;

typedef struct {
	unsigned index;
	int score;

} outThread_t;

atomic_int globalScore;

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc < 2, "Invalid arg count");

	int threadNum = argc - 1;
	inThread_t* args = malloc(threadNum * sizeof(inThread_t));
	check_error(args == NULL, "malloc() failure");

	pthread_t* tids = malloc(threadNum * sizeof(pthread_t));
	check_error(tids == NULL, "malloc() failure");

	outThread_t* retVal;
	atomic_init(&globalScore, 0);

	for(int i = 0; i < threadNum; i++){
		args[i].index = i;
		args[i].filename = argv[i+1];
		check_error(pthread_create(&tids[i], NULL, thread_func, (void*)&args[i]) != 0, "pthread_create() failure");
	}

	for(int i = 0; i < threadNum; i++){
		check_error(pthread_join(tids[i], (void**)&retVal) != 0, "pthread_join() failure");
		printf("TID: %i %i\n", retVal->index, retVal->score);
		free(retVal);
	}

	printf("Global score: %i\n", atomic_load(&globalScore));

	free(tids);
	free(args);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	inThread_t* args = (inThread_t*) arg;
	outThread_t* out = malloc(sizeof(outThread_t));
	check_error(out == NULL, "malloc() failure");

	out->index = args->index;
	out->score = 0;

	int fd = open(args->filename, O_RDONLY);
	check_error(fd == -1, "open() failure");

	int readBytes = 0;
	char buffer[MAX_SIZE];

	unsigned plus = 0, minus = 0;

	while((readBytes = read(fd, buffer, MAX_SIZE)) > 0){

		for(int i = 0; i < readBytes; i++){
			switch(buffer[i]){
				case '+': plus++; break;
				case '-': minus++; break;
				default: break;
			}
		}

	}

	check_error(readBytes == -1, "read() failure");

	out->score = plus - minus;

	atomic_fetch_add(&globalScore, out->score);

	close(fd);

	pthread_exit((void*) out);
}