#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define check_error(expr, usrMsg)\
	do{\
		if(expr){\
			perror(usrMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count\n");

	pid_t pid = fork();

	if(pid == 0){
		check_error(execle("gcc", "gcc", "-std=c99", argv[1], "-o", "child_gcc_result", NULL) == -1, "execle failure\n");
		exit(EXIT_SUCCESS);
	}

	int status;
	check_error(waitpid(pid, &status, 0) == -1, "waitpid failure\n");

	if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)){
		struct stat fstat;
		check_error(stat("child_gcc_result", &fstat) == -1, "fstat failure");
		printf("File size: %u\n", (unsigned) fstat.st_size);
	}
	else{
		printf("gcc failed\n");
		exit(WEXITSTATUS(status));
	}

	exit(EXIT_SUCCESS);
}