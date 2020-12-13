#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <signal.h>

#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

#define RD_END (0)
#define WR_END (1)
#define MAX_SIZE (1024)

int main(int argc, char** argv) {
	
	int par2cld[2];
	int cld2par[2];
	
	check_error(pipe(par2cld) != -1, "pipe failed");
	check_error(pipe(cld2par) != -1, "pipe failed");
	
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	if (pid > 0) { // parent
		
		close(par2cld[RD_END]);
		close(cld2par[WR_END]);
		
		char* line = NULL;
		size_t lineLen  = 0;
		
		while (1){
			
			check_error(getline(&line, &lineLen, stdin) != -1, "getline failed");
			if (!strcmp(line, "quit\n")) {
				check_error(kill(pid, SIGKILL) != -1, "kill failed");
				printf("bye\n");
				break;
			}
			
			check_error(lineLen < 1024, "line too long");
			check_error(write(par2cld[WR_END], line, lineLen) != -1, "write failed");
			
			int status;
			check_error(read(cld2par[RD_END], &status, sizeof(int)) != -1, "read failed");
			
			if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)){
				printf("Success\n");
			}
			else {
				printf("Failure\n");
			}
		}
		
		free(line);
		
		close(cld2par[RD_END]);
		close(par2cld[WR_END]);
		
		int status;
		check_error(waitpid(pid, &status, 0) != -1, "waitpi failed");
	}
	else { // child
		
		close(par2cld[WR_END]);
		close(cld2par[RD_END]);
		
		char buffer[MAX_SIZE];
		while (1){
			int bytesRead = read(par2cld[RD_END], buffer, MAX_SIZE);
			
			check_error(bytesRead != -1, "read failed");
			buffer[bytesRead] = 0;
			
			int status = system(buffer);
			check_error(write(cld2par[WR_END], &status, sizeof(int)) != -1, "read failed");
		}
			
		exit(EXIT_SUCCESS);
	}
	
	exit(EXIT_SUCCESS);
}
