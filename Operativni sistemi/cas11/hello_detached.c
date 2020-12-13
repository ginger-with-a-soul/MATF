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

void* thread_func(void* arg);

int main(int argc, char** argv){

	check_error(argc != 1, "Invalid arg count");

	pthread_t tid;
	check_pthreadErr(pthread_create(&tid, NULL, thread_func, NULL) != 0, "pthread() create failure");

	check_pthreadErr(pthread_detach(tid) != 0, "pthread_detach() failure");
	printf("Detached thread initialized\n");
	sleep(3);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){

	sleep(2);
	printf("I'm in!\n");

	return NULL;

}