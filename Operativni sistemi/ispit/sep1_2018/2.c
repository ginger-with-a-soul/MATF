#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

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

	check_error(argc < 2, "invalid arg count");
	
	char** arguments = malloc(sizeof(char*) * argc);
	check_error(arguments == NULL, "malloc() failure");
	for(int i = 0; i < argc - 1; i++){
		arguments[i] = malloc(sizeof(char) * MAX_SIZE);
	}

	for(int i = 1, j = 0; i < argc; i++, j++){
		strcpy(arguments[j], argv[i]);
	}
	
	arguments[argc - 1] = NULL;

	int tube[2];
	check_error(pipe(tube) == -1, "pipe() failure");

	int status, stdoutFD, lineNum = 0;
	char* lineptr = NULL;
	size_t *n;

	stdoutFD = dup(STDOUT_FILENO);
	check_error(stdoutFD == -1, "dup() failure");

	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");
	

	if(pid > 0){

		check_error(close(tube[WR_END]) == -1, "close() failure");

		check_error(wait(&status) == -1, "wait() failure");

		FILE* f = fdopen(tube[RD_END], "r");
		check_error(f == NULL, "fdopen() failure");

		if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
			check_error(1, "Neuspeh\n");
		}
		else{
			while(getline(&lineptr, n, f) != -1){
				lineNum += 1;
			}
		}

		check_error(close(tube[RD_END]) == -1, "close() failure");

	}
	else{

		check_error(close(tube[RD_END]) == -1, "close() failure");

		check_error(dup2(tube[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
		
		check_error(execvp(argv[1], arguments) == -1, "execvp() failure");

		check_error(close(tube[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}

	dprintf(stdoutFD, "%d\n", lineNum);
	check_error(close(stdoutFD) == -1, "close() failure");

	exit(EXIT_SUCCESS);
}