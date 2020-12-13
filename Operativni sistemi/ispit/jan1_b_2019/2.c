#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	} while(0);\

int score = 0, shouldTerm = 0;

void sigHandler(int signum);

int main(int argc, char** argv){

	check_error(argc != 1, "invalid arg count");

	check_error(signal(SIGUSR1, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGUSR2, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGINT, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGTERM, sigHandler) == SIG_ERR, "signal() failure");


	do {
		pause();
	} while(!shouldTerm);

	printf("%d\n", score);

	exit(EXIT_SUCCESS);
}

void sigHandler(int signum){
	switch(signum){
		case SIGUSR1: score += 1; break;
		case SIGUSR2: score += 2; break;
		case SIGINT: score -= 4; break;
		case SIGTERM: shouldTerm = 1; break;
		default: break;
	}
}