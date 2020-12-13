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

#include <sys/wait.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv){

	check_error(argc != 3, "invalid arg count");

	int tube[2], status;
	char buffer[MAX_SIZE];
	size_t bytesRead = 0;

	check_error(pipe(tube) == -1, "pipe() failure");
	int stdoutFD = dup(STDOUT_FILENO);
	check_error(stdoutFD == -1, "dup() failure");
	
	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");

	if(pid > 0){
		check_error(close(tube[WR_END]) == -1, "close() failure");

		check_error(wait(&status) == -1, "wait() failure");
		if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
			dprintf(stdoutFD, "Neuspeh");
			exit(EXIT_SUCCESS);
		}

		while((bytesRead = read(tube[RD_END], buffer, MAX_SIZE)) > 0){
			check_error(write(stdoutFD, buffer, bytesRead) == -1, "write() failure");
		}

		check_error(bytesRead == -1, "read() failure");

		check_error(close(tube[RD_END]) == -1, "close() failure");
	}
	else{
		check_error(close(tube[RD_END]) == -1, "close() failure");

		check_error(dup2(tube[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
		check_error(execlp("tail", "tail", "-n", argv[2], argv[1], NULL) == -1, "execlp() failure");

		check_error(close(tube[WR_END]) == -1, "close() failure");
	}

	check_error(close(stdoutFD) == -1, "close() failure");

	exit(EXIT_SUCCESS);
}