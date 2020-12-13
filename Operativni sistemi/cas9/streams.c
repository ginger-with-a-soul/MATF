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

#define WR_END (1)
#define RD_END (0)
int par2cld[2];

int main(int argc, char** argv){

	check_error(argc != 1, "Invalid arg count");

	

	check_error(pipe(par2cld) == -1, "pipe() failed");
	
	pid_t pid = fork();

	check_error(pid == -1, "fork() failure");


	if(pid > 0){

		close(par2cld[RD_END]);

		FILE* f = fdopen(par2cld[WR_END], "w");
		check_error(f == NULL, "fdopen() failure");

		char* msg = "Some message";
		int num = 1234;

		fprintf(f, "%s %i\n", msg, num);


		fclose(f);

	}
	else{

		check_error(close(par2cld[WR_END]) == -1, "close() failure");

		FILE* fd = fdopen(par2cld[RD_END], "r");
		check_error(fd == NULL, "fdopen() failure");

		char buffer[MAX_SIZE];

		check_error(fgets(buffer, MAX_SIZE, fd) == NULL, "fgets() failure");

		printf("Child: %s\n", buffer);

		check_error(fclose(fd) == EOF, "fclose() failure");

		exit(EXIT_SUCCESS);
	}

	int status;
	check_error(waitpid(pid, &status, 0) == -1, "waitpid() failure");

	exit(EXIT_SUCCESS);
}