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


void* thread_func(void* arg);
char* seq;
int K, fd, globalSum = 0;
FILE* f;
off_t N;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv){

	check_error(argc != 4, "invalid arg count");

	fd = open(argv[1], O_RDONLY);
	check_error(fd == -1, "open() failure");

	f = fopen(argv[1], "r");
	check_error(f == NULL, "fopen() failure");

	struct stat fInfo;
	check_error(fstat(fd, &fInfo) == -1, "fstat() failure");
	N = fInfo.st_size;

	K = atoi(argv[3]);
	seq = argv[2];

	pthread_t* tids = malloc(sizeof(pthread_t) * K);
	check_error(tids == NULL, "malloc() failure");

	for(int i = 0; i < K; i++){
		check_pthreadErr(pthread_create(&tids[i], NULL, thread_func, (void*)(intptr_t)i),
		"pthread_create() failure");
	}

	for(int i = 0; i < K; i++){
		check_pthreadErr(pthread_join(tids[i], NULL), "pthread_join() failure");
	}

	printf("%d\n", globalSum);

	free(tids);
	close(fd);
	fclose(f);
	check_pthreadErr(pthread_mutex_destroy(&globalLock), "pthread_mutex_destroy() failure");

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg){
	int argument = (int)(intptr_t)arg;

	check_error(fseek(f, argument * (N / K), SEEK_CUR) == -1, "lseek() failure");
	printf("%li\n", ftell(f));

	int size = N / K - 1, localSum = 0;
	char* buffer = malloc(sizeof(char) * (size + 1));
	check_error(buffer == NULL, "malloc() failure");
	ssize_t bytesRead = 0;

	while((bytesRead = read(fd, buffer, size)) > 0);
	check_error(bytesRead == -1, "read() failure");
	buffer[size + 1] = 0;

	while(strstr(buffer, seq) != NULL){
		localSum += 1;
		buffer += strlen(seq);
	}

	check_pthreadErr(pthread_mutex_lock(&globalLock), "pthread_mutex_lock() failure");
	globalSum += localSum;
	check_pthreadErr(pthread_mutex_unlock(&globalLock), "pthread_mutex_lock() failure");

	//free(tmp);
	
	return NULL;
}