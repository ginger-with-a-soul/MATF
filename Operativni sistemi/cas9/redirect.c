#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <sys/wait.h>

#define MAX_SIZE 1024

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv){

	check_error(argc != 1, "Invalid arg count");

	int p2c[2];
	check_error(pipe(p2c) == -1, "pipe() failure");

	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");

	if(pid > 0){

		check_error(close(p2c[WR_END]) == -1, "close() failure");

		FILE* fd = fdopen(p2c[RD_END], "r");
		check_error(fd == NULL, "fdopen() failure");

		char* lineptr = NULL;
		size_t size = 0;
		unsigned num = 0;

		while(getline(&lineptr, &size, fd) != -1){
			printf("%u: %s", num, lineptr);
			num++;
		}

		free(lineptr);
		check_error(fclose(fd) == EOF, "fclose() failure");

	}
	else{

		check_error(close(p2c[RD_END]) == -1, "close() failure");

		check_error(dup2(p2c[WR_END], STDOUT_FILENO) == -1, "dup2() failure");

		check_error(execlp("ls", "ls", "-l", NULL) == -1, "execlp() failure");

		check_error(close(p2c[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}

	int status;
	check_error(waitpid(pid, &status, 0) == -1, "waitpid() failure");

	if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS){
		printf("All good\n");
	}
	else{
		printf("Whoops, there was an error\n");
	}


	exit(EXIT_SUCCESS);
}