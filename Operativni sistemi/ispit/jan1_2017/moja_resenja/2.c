#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/wait.h>

#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

#define MAX_SIZE (1024)
#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count\n");

	int pipefd[2];
	check_error(pipe(pipefd) == -1, "pipe() failure\n");


	pid_t pid;
	check_error((pid = fork()) == -1, "fork() failure\n");

	if(pid == 0){
		check_error(close(pipefd[RD_END]) == -1, "close() failure\n");
		check_error(dup2(pipefd[WR_END], STDOUT_FILENO) == -1, "dup2() failure\n");
		check_error(execlp("stat", "stat", "--format=%s", argv[1], NULL) == -1, "execlp() failure\n");
	}

	char buffer[MAX_SIZE];

	check_error(close(pipefd[WR_END]) == -1, "close() failure\n");
	check_error(read(pipefd[RD_END], buffer, MAX_SIZE) == -1, "read() failure\n");
	check_error(close(pipefd[RD_END]) == -1, "close() failure\n");

	int status, x;
	check_error(waitpid(pid, &status, 0) == -1, "waitpid() failure\n");

	if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)){
		sscanf(buffer, "%i", &x);
		printf("%i", x);
	}
	else{
		printf("Neuspeh\n");
		exit(status);
	}

	exit(EXIT_SUCCESS);
}