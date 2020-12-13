#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/wait.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)

#define RD_END (0)
#define WR_END (1)		

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "./2 filePath");
	
	int pipeFds[2];
	osAssert(pipe(pipeFds) != -1, "pipe failed");
	
	pid_t childPid = fork();
	osAssert(childPid != -1, "fork failed");
	
	if (childPid > 0) { // parent
		
		close(pipeFds[WR_END]);
		
		size_t bufLen = 0;
		char* buf = NULL;
		
		FILE* stream = fdopen(pipeFds[RD_END], "r");
		osAssert(stream != NULL, "fdopen failed");
			
		while (getline(&buf, &bufLen, stream) != -1) {
			char privileges[11];
			sscanf(buf, "%s", privileges);
			printf("%s\n", privileges);
		}
		
		free(buf);
		fclose(stream);
	}
	else { // child
		
		close(pipeFds[RD_END]);
		
		osAssert(dup2(pipeFds[WR_END], STDOUT_FILENO) != -1, "dup2 failed");
		
		osAssert(execlp("ls", "ls", "-l", argv[1], NULL) !=- 1, "Exec failed");
		
		exit(EXIT_FAILURE);
	}
	
	int status;
	osAssert(wait(&status) != -1, "wait failed");
	
	if (!WIFEXITED(status) || !(WEXITSTATUS(status) == EXIT_SUCCESS)) {
		printf("Neuspeh\n");
	}
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}
