#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <wait.h>

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
	check_error(pipe(tube) == -1, "pipe() failure");
	int stdoutFD = dup(STDOUT_FILENO);
	check_error(stdoutFD == -1, "dup() failure");
	char buffer[MAX_SIZE], first[MAX_SIZE];
	ssize_t bytesRead = 0;
	
	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");

	if(pid > 0){
		check_error(close(tube[WR_END]) == -1, "close() failure");

		check_error(wait(&status) == -1, "wait() failure");

		if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
			check_error(1, "Neuspeh\n");
		}

		//if(strcmp(argv[2], "-w") && strcmp(argv[2], "-w") && strcmp(argv[2], "-w")){
		//	check_error(1, "Neuspeh\n");
		//}

		check_error((bytesRead = read(tube[RD_END], buffer, MAX_SIZE)) == -1, "read() failure");
		buffer[bytesRead] = 0;
		sscanf(buffer, "%s", first);
		dprintf(stdoutFD, "%s\n", first);

		check_error(close(tube[RD_END]) == -1, "close() failure");
	}
	else{
		check_error(close(tube[RD_END]) == -1, "close() failure");

		check_error(dup2(tube[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
		check_error(execlp("wc", "wc", argv[2], argv[1], NULL) == -1, "execlp() failure");

		check_error(close(tube[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}
	
	close(stdoutFD);

	exit(EXIT_SUCCESS);
}