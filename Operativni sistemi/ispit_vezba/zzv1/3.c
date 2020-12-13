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

#include <wait.h>


#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
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

	int pip[2];
	check_error(pipe(pip) == -1, "pipe() failure");

	pid_t pid = fork();

	if(pid > 0){

		check_error(close(pip[WR_END]) == -1, "close() failure");
		FILE* f = fdopen(pip[RD_END], "r");
		check_error(f == NULL, "fdopen() failure");

		char* linePtr = NULL;
		size_t size = 0;
		unsigned lineNum = 0;

		while(getline(&linePtr, &size, f) >= 0){

			if(lineNum){
				char rights[MAX_SIZE];
				int num;
				char usrName[MAX_SIZE];
				char grpName[MAX_SIZE];
				int size;

				sscanf(linePtr, "%s %i %s %s %i", rights, &num, usrName, grpName, &size);

				printf("Size: %i\n", size);
			}

			lineNum++;
		}

		free(linePtr);
		fclose(f);
		//check_error(close(pip[RD_END]) == -1, "close() failure");
	}
	else{

		check_error(close(pip[RD_END]) == -1, "close() failure");

		check_error(dup2(pip[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
		check_error(execlp("ls", "ls", "-l", NULL) == -1, "execlp() failure");

		check_error(close(pip[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}

	int status;
	check_error(wait(&status) == -1, "wait() failure");

	if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS){
		printf("All good\n");
	}
	else{
		printf("Smth's not right\n");
	}

	exit(EXIT_SUCCESS);
}