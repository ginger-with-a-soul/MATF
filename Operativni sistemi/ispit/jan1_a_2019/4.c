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

#define MAX_SIZE (255)
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

	char program[MAX_SIZE], argument[MAX_SIZE], buffer[MAX_SIZE * 16], maxProgram[MAX_SIZE];
	pid_t pid;
	int status, c2p[2], readBytes = 0, max = 0, fd;
	check_error(pipe(c2p) == -1, "pipe() failure");
	check_error((fd = dup(STDOUT_FILENO)) == -1, "dup() failure");
	check_error(dup2(c2p[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
	

	while(!feof(f)){
		fscanf(f, "%s %s", program, argument);
		
		if(strlen(program) + strlen(argument) > 255){
			check_error(1, "line too long");
		}
		pid = fork();
		readBytes = 0;

		if(pid > 0){

			check_error((readBytes = read(c2p[RD_END], buffer, MAX_SIZE*16)) == -1, "read() failure");
			if(readBytes > max){
				max = readBytes;
				strcpy(maxProgram, program);
				strcat(maxProgram, " ");
				strcat(maxProgram, argument);
			}

		}
		else{

			check_error(close(c2p[RD_END]) == -1, "close() failure");
			check_error(execlp(program, program, argument, NULL) == -1, "execlp() failure");


			check_error(close(c2p[WR_END]) == -1, "close() failure");

			exit(EXIT_SUCCESS);
		}

		check_error(wait(&status) == -1, "wait() failure");

		if(WIFEXITED(status)){
			if(WEXITSTATUS(status) != EXIT_SUCCESS){
				check_error(1, "exit status != EXIT_SUCCESS");
			}
		}
		else{
			check_error(1, "child still alive");
		}
	}

	dprintf(fd, "%s\n", maxProgram);

	check_error(close(c2p[WR_END]) == -1, "close() failure");
	check_error(close(fd) == -1, "close() failure");
	check_error(close(c2p[RD_END]) == -1, "close() failure");
	fclose(f);

	exit(EXIT_SUCCESS);
}