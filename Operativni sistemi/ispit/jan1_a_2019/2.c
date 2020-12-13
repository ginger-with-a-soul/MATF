#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <signal.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

void sigHandler(int signum);

int shouldTerminate = 0;
int x;

int main(int argc, char** argv){


	check_error(signal(SIGUSR1, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGUSR2, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGTERM, sigHandler) == SIG_ERR, "signal() failure");

	do {
		pause();
	} while(!shouldTerminate);

	exit(EXIT_SUCCESS);
}

void sigHandler(int signum){
	scanf("%i", &x);
	switch(signum){
		case SIGUSR1: printf("%i\n", abs(x)); break;
		case SIGUSR2: printf("%i\n", x * x); break;
		case SIGTERM: shouldTerminate = 1; break;
		default: break;
	}
}