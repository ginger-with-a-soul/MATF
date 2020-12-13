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

#include <sys/wait.h>
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

#define RD_END (0)
#define WR_END (1)

pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv){

	check_error(argc != 2, "invalid arg count");

	FILE* f = fopen(argv[1], "r");
	check_error(f == NULL, "fopen() failure");

	int fd = open(argv[1], O_RDONLY);
	check_error(fd == -1, "open() failure");

	char *line = NULL, buffer[MAX_SIZE], bf2[MAX_SIZE];
	size_t size = 0;
	pid_t pid;
	int pajp[2], status, childNum = 0, total = 0;


	while(getline(&line, &size, f) != EOF){

		pid = fork();
		printf("da\n");
		childNum++;
		check_error(pipe(pajp) == -1, "pipe() failure");

		if(pid > 0){

			check_error(close(pajp[WR_END]) == -1, "close() failure");

			check_error(wait(&status) == -1, "wait() failure");

			if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
				check_error(1, "invalid child _exit()");
			}

			check_error(read(pajp[RD_END], bf2, sizeof(int)) == -1, "read() failure");

			check_pthreadErr(pthread_mutex_lock(&globalLock) != 0, "pthread_mutex_lock() failure");
			total += atoi(bf2);
			check_pthreadErr(pthread_mutex_unlock(&globalLock) != 0, "pthread_mutex_lock() failure");

			check_error(close(pajp[RD_END]) == -1, "close() failure");

		}
		else{

			check_error(close(pajp[RD_END]) == -1, "close() failure");

			int aNum = 0;

			for(int i = 0; i < size; i++){
				if(line[i] == 'a'){
					aNum++;
				}
			}
			sprintf(buffer, "%i", aNum);
			printf("%s\n", buffer);
			check_error(write(pajp[WR_END], buffer, sizeof(int)) == -1, "write() failure");

			check_error(close(pajp[WR_END]) == -1, "close() failure");

			_exit(EXIT_SUCCESS);
		}
	}

	printf("%i %i\n", total, childNum);

	check_pthreadErr(pthread_mutex_destroy(&globalLock) != 0, "pthread_mutex_destroy() failure");
	free(line);
	close(fd);
	fclose(f);

	exit(EXIT_SUCCESS);
}