#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	} while(0);\

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv){

	check_error(argc < 2, "invalid arg count");

	int tube[2], status;
	size_t readBytes = 0;
	char buffer[MAX_SIZE], word[MAX_SIZE];
	unsigned num = argc - 1, currentArg = 0;
	pid_t pid;
	int stdoutFD = dup(STDOUT_FILENO);
	int stderrFD = dup(STDERR_FILENO);
	check_error(stdoutFD == -1, "dup() failure");
	check_error(close(STDERR_FILENO) == -1, "close() failure");

	while(num--){
		currentArg += 1;

		check_error(pipe(tube) == -1, "pipe() failure");

		pid = fork();
		check_error(pid == -1, "fork() failure");
		
		if(pid > 0){
			check_error(close(tube[WR_END]) == -1, "close() failure");

			check_error(wait(&status) == -1, "wait() failure");
			if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
				dprintf(stdoutFD, "neuspeh ");
			}
			else{
				check_error((readBytes = read(tube[RD_END], buffer, MAX_SIZE)) == -1, "read() failure");
				buffer[readBytes] = 0;
				sscanf(buffer, "%s", word);
				check_error(write(stdoutFD, word, strlen(word)) == -1, "write() failure");
				dprintf(stdoutFD, " ");
			}

			check_error(close(tube[RD_END]) == -1, "close() failure");
		}
		else{
			check_error(close(tube[RD_END]) == -1, "close() failure");

			check_error(dup2(tube[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
			
			check_error(execlp("du", "du", "-sch", argv[currentArg], NULL) == -1, "execlp() failure");

			check_error(close(tube[WR_END]) == -1, "close() failure");
			exit(EXIT_SUCCESS);
		}
	}

	close(stdoutFD);

	exit(EXIT_SUCCESS);
}