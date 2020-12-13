#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>

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

	check_error(argc != 2, "invalid arg count");

	FILE* f = fopen(argv[1], "r");
	check_error(f == NULL, "fopen() failure");

	int fd = open(argv[1], O_RDONLY);
	check_error(fd == -1, "open() failure");

	int fdErr = open("errors.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	check_error(fdErr == -1, "open() failure");

	char instruction[MAX_SIZE], argument[MAX_SIZE], buffer[MAX_SIZE * 5];
	int pajp[2], readBytes = 0;
	
	
	pid_t pid;

	while(fscanf(f, "%s %s", instruction, argument) == 2){

		check_error(pipe(pajp) == -1, "pipe() failure");
		
		check_error(strlen(instruction) + strlen(argument) > 255, "line too long");

		readBytes = 0;
		pid = fork();
		check_error(pid == -1, "fork() failure");

		if(pid > 0){
			check_error(close(pajp[WR_END]) == -1, "close() failure");
	
			int status;
			
			check_error(wait(&status) == -1, "wait() failure");

			if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
				while((readBytes = read(pajp[RD_END], buffer, MAX_SIZE)) > 0){
					check_error(write(fdErr, buffer, readBytes) == -1, "write() failure");
				}
			}
			check_error(readBytes == -1, "read() failure");
			check_error(close(pajp[RD_END]) == -1, "close() failure");

		}
		else{
			check_error(close(pajp[RD_END]) == -1, "close() failure");
			check_error(dup2(pajp[WR_END], STDERR_FILENO) == -1, "dup2() failure");

			check_error(execlp(instruction, instruction, argument, NULL) == -1, "execlp() failure");

			check_error(close(pajp[WR_END]) == -1, "close() failure");

			exit(EXIT_SUCCESS);
		}
	}

	close(fd);
	close(fdErr);
	fclose(f);

	exit(EXIT_SUCCESS);
}