#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <sys/wait.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define osCheckPthread(pthreadErr, userMsg) \
    do { \
      int __pthreadErr = (pthreadErr); \
      if (__pthreadErr > 0) { \
        errno = __pthreadErr; \
        osAssert(false, userMsg); \
      } \
    } while (0)
    
static const char *os_Usage = "./2 pathToFile";
    
void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);

#define RD_END   (0)
#define WR_END 	 (1)
#define MAX_SIZE (8192)

int main(int argc, char** argv) {
	
	int pipeFds[2];
	
	osAssert(argc == 2, os_Usage);
	osAssert(pipe(pipeFds) != -1, "pipe failed");
	
	pid_t childPid = fork();
	osAssert(childPid != -1, "fork failed");
	
	if (childPid == 0) { // child
		
		close(pipeFds[RD_END]);
		
		dup2(pipeFds[WR_END], STDOUT_FILENO);
		
		osAssert(execlp("stat", "stat", "--format=%s", argv[1], NULL) != -1, "exec failed");
	}
	
	close(pipeFds[WR_END]);
	char buffer[MAX_SIZE];
	osAssert(read(pipeFds[RD_END], buffer, MAX_SIZE) != -1, "read failed");
	
	close(pipeFds[RD_END]);
	
	int status = 0;
	osAssert(waitpid(childPid, &status, 0) != -1, "wait failed");
	
	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) != EXIT_SUCCESS) {
			printf("Neuspeh\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		printf("Neuspeh\n");
		exit(EXIT_FAILURE);
	}
	
	int size;
	sscanf(buffer, "%d", &size);
	printf("%d\n", size);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
