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
    
static const char *os_Usage = "./3 pathToFile";
    
void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum);

int state = 0;
int shouldTerminate = 0;

void sigHandler(int signum) {
	
	switch(signum) {
		case SIGUSR1:
			state = 1;
			break;
		case SIGUSR2:
			state = 2;
			break;
		case SIGINT:
			state = 3;
			break;
		case SIGQUIT:
			shouldTerminate = true;
			break;
	}
}

unsigned obrnut(unsigned x) {
	
	unsigned result = 0;
	
	while (x) {
		
		result = result*10 + x%10;
		x/=10;
	}
	
	return result;
}

int main(int argc, char** argv) {
	
	unsigned x, y;
	
	osAssert(signal(SIGUSR1, sigHandler) != SIG_ERR, "signal error");
	osAssert(signal(SIGUSR2, sigHandler) != SIG_ERR, "signal error");
	osAssert(signal(SIGINT, sigHandler) != SIG_ERR, "signal error");
	osAssert(signal(SIGQUIT, sigHandler) != SIG_ERR, "signal error");

	printf("%i\n", fork());
	
	do {
		
		scanf("%u", &x);
		
		pause();
		
		switch (state) {
			
			case 1:
				printf("%u\n", x*x);
				break;
			case 2:
				printf("%u\n", x*x*x);
				break;
			case 3:
				printf("%u\n", obrnut(x));
				break;
		}
		
		state = 0;
		
	} while (!shouldTerminate);
	
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char *userMsg, const char *fileName, 
                      const char *functionName, const int lineNum) {
    perror(userMsg);
    fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName, functionName, lineNum);
    exit(EXIT_FAILURE);
}
