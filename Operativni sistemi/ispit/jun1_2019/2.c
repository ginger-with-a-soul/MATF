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

	check_error(argc != 2, "invalid arg count");

	int pajp[2];
	check_error(pipe(pajp) == -1, "pipe() failure");

	int stdoutFD = dup(STDOUT_FILENO);
	check_error(stdoutFD == -1, "dup() failure");

	pid_t pid = fork();
	check_error(pid == -1, "fork() failure");

	int status, bytesRead = 0, pos;
	char buffer[MAX_SIZE*4], c;

	if(pid > 0){

		check_error(close(pajp[WR_END]) == -1, "close() failure");

		check_error(wait(&status) == -1, "wait() failure");

		if(!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS){
			dprintf(stdoutFD, "neuspeh\n");
		}
		else{
			while((bytesRead = read(pajp[RD_END], buffer, MAX_SIZE)) > 0){
			}

			pos = 0;
			c = 'x';
			while(c != '('){
				c = buffer[pos];
				pos++;
			}

			pos += 5;
			for(int i = 0; i < 10; i++, pos++){
				dprintf(stdoutFD, "%c", buffer[pos]);
			}
			dprintf(stdoutFD, "\n");

			check_error(bytesRead == -1, "read() failure");
		}


		check_error(close(pajp[RD_END]) == -1, "close() failure");

	}	
	else{

		check_error(close(pajp[RD_END]) == -1, "close() failure");
		
		check_error(dup2(pajp[WR_END], STDOUT_FILENO) == -1, "dup2() failure");
		check_error(execlp("stat", "stat", argv[1], NULL) == -1, "execlp() failure");


		check_error(close(pajp[WR_END]) == -1, "close() failure");

		exit(EXIT_SUCCESS);
	}



	close(stdoutFD);

	exit(EXIT_SUCCESS);
}