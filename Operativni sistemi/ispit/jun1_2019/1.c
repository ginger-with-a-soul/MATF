#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <signal.h>
#include <stdbool.h>


#define MAX_SIZE (1024)
#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\



int x, y, z;
bool shouldTerm = false;

void sigHandler(int signum);

int main(int argc, char** argv){

	check_error(argc != 1, "invalid arg count");

	check_error(signal(SIGUSR1, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGUSR2, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGINT, sigHandler) == SIG_ERR, "signal() failure");
	check_error(signal(SIGTERM, sigHandler) == SIG_ERR, "signal() failure");


	do {

		scanf("%i %i", &x, &y);
		pause();
		printf("%i\n", z);

	} while(!shouldTerm);

	
	exit(EXIT_SUCCESS);
}

void sigHandler(int signum){
	switch(signum){
		case SIGUSR1: z = x ^ y; break;
		case SIGUSR2: z = x & y; break;
		case SIGINT: z = x | y; break;
		case SIGTERM: shouldTerm = true; break;
		default: break;
	}
}