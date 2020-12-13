#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <sys/wait.h>


#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define WR_END (0)
#define RD_END (1)

int main(int argc, char** argv){

	check_error(argc != 1, "Invalid arg count");

	int p2c[2], c2p[2];
	check_error(pipe(p2c) == -1, "pipe() failure");
	check_error(pipe(c2p) == -1, "pipe() failure");

	pid_t pid = fork();

	if(pid > 0){

		check_error(close(p2c[RD_END]) == -1, "close() failure");
		check_error(close(c2p[WR_END]) == -1, "close() failure");

		char *lineptr = NULL;
		size_t size = 0;

		while(1){

			check_error(getline(&lineptr, &size, stdin) == -1, "getline() failure");

			check_error(size > 1024, "Line too long");

			if(!strcmp(lineptr, "quit\n")){
				check_error(kill(pid, SIGKILL) == -1, "kill() failure");
				printf("Bye\n");
				break;
			}

			check_error(write(p2c[WR_END], lineptr, size) == -1, "write() failure");

			int res;
			check_error(read(c2p[RD_END], &res, sizeof(int)) == -1, "read() failure");

			if(WIFEXITED(res) && WEXITSTATUS(res) == EXIT_SUCCESS){
				printf("Success\n");
			}
			else{
				printf("Failure\n");
			}

		}

		free(lineptr);
		check_error(close(p2c[WR_END]) == -1, "close() failure");
		check_error(close(c2p[RD_END]) == -1, "close() failure");

		int status;
		check_error(waitpid(pid, &status, 0) == -1, "waitpid() failure");
	}
	else{

		check_error(close(p2c[WR_END]) == -1, "close() failure");
		check_error(close(c2p[RD_END]) == -1, "close() failure");

		char buffer[MAX_SIZE];
		int readBytes = 0;
		int stat;
		while(1){
			check_error((readBytes = read(p2c[RD_END], buffer, MAX_SIZE)) == -1, "read() failure");
			buffer[readBytes] = 0;

			check_error((stat = system(buffer)) == -1, "system() failure");

			check_error(write(c2p[WR_END], &stat, sizeof(int)) == -1, "write() failure");
		}

		check_error(close(p2c[RD_END]) == -1, "close() failure");
		check_error(close(c2p[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}

	exit(EXIT_SUCCESS);
}