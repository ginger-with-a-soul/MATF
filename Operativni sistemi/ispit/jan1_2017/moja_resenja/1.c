#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int sigUsr1Counter = 0, sigUsr2Counter = 0;
bool shouldTerm = false;

void signalHandler(int signum);

int main(int argc, char** argv){
	check_error(argc != 1, "Invalid arg count\n");

	check_error(signal(SIGUSR1, signalHandler) == SIG_ERR, "signal() failure\n");
	check_error(signal(SIGUSR2, signalHandler) == SIG_ERR, "signal() failure\n");
	check_error(signal(SIGTERM, signalHandler) == SIG_ERR, "signal() failure\n");

	do {
		pause();
	} while(!shouldTerm);

	printf("%i %i\n", sigUsr1Counter, sigUsr2Counter);

	exit(EXIT_SUCCESS);
}

void signalHandler(int signum){
	switch(signum){
		case SIGUSR1: sigUsr1Counter++; break;
		case SIGUSR2: sigUsr2Counter++; break;
		case SIGTERM: shouldTerm = true;
		default: break;
	}
}