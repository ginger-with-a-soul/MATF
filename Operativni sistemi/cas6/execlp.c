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
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\


int main(int argc, char** argv){

	check_error(argc != 3, "Invalid arg count");

	pid_t process = fork();
	check_error(process == -1, "fork() failure");

	if(process == 0){
		printf("Child:\n");
		printf("gcc %s -o %s\n", argv[1], argv[2]);
		check_error(execlp("gcc", "gcc", argv[1], "-o", argv[2], (char *) NULL) == -1, "execlp() failure");
		exit(EXIT_SUCCESS);
	}

	int status = 0;
	check_error(wait(&status) == -1, "wait() failure");

	if(WIFEXITED(status)){
		check_error(WEXITSTATUS(status) != EXIT_SUCCESS, "Program exit failure");
	}


	exit(EXIT_SUCCESS);
}