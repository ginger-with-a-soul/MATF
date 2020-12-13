#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <signal.h>

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
    
static const char *os_Usage = "";
    
void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);
                  
int sigusr1Count = 0;
int sigusr2Count = 0;
bool shouldTerminate = false;
                      
void signalHandler(int signum) {
	
	switch (signum) {
		
		case SIGUSR1:
			sigusr1Count++;
			break;
		case SIGUSR2:
			sigusr2Count++;
			break;
		case SIGTERM:
			shouldTerminate = true;
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	
	osAssert(signal(SIGUSR1, signalHandler) != SIG_ERR, "signal handler setuo failed");
	osAssert(signal(SIGUSR2, signalHandler) != SIG_ERR, "signal handler setuo failed");
	osAssert(signal(SIGTERM, signalHandler) != SIG_ERR, "signal handler setuo failed");
	
	//fprintf(stderr, "PID: %jd\n", (intmax_t)getpid());
	
	do {
		pause();
	} while(!shouldTerminate);
	
	printf("%d %d\n", sigusr1Count, sigusr2Count);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
