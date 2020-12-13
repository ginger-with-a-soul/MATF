#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int main(int argc, char** argv) {
	
	check_error(argc == 2, "invalid args");
	
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	if (pid == 0) { // child
		
		check_error(execlp("gcc", "gcc", "-std=c99", argv[1], "-o", "test", NULL) != -1, "exec failed");
		
		exit(EXIT_FAILURE);
	}
	
	int status;
	check_error(waitpid(pid, &status, 0) != -1, "waitpid failed");
	
	if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
		
		struct stat fInfo;
		check_error(stat("test", &fInfo) != -1, "stat failed");
		
		printf("File size: %u\n", (unsigned)fInfo.st_size);
	}
	else {
		printf("gcc failed\n");
		exit(WEXITSTATUS(status));
	}
	
	exit(EXIT_SUCCESS);
}
