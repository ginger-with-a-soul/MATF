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


int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");

	if(pid == 0){

		check_error(execlp("gcc", "gcc", argv[1], "-o", "exec", NULL) == -1, "execlp() failure");

		exit(EXIT_SUCCESS);
	}

	int status;
	check_error(waitpid(pid, &status, 0) == -1, "waitpid() failure");

	if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS){
		int fd = open("exec", O_RDWR, 0644);
		struct stat fInfo;
		check_error(fstat(fd, &fInfo) == -1, "fstat() failure");
		printf("Size of the output file is: %i\n", (int)fInfo.st_size);
		close(fd);

	}
	else{
		printf("gcc unsuccessful\n");
		exit(status);
	}

	exit(EXIT_SUCCESS);
}