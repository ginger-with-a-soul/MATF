#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

int main(int argc, char** argv){

	check_error(argc != 2, "invalid arg count");

	time_t now = atoi(argv[1]);

	struct tm* tajm = localtime(&now);

	if(tajm->tm_hour >= 0 && tajm->tm_hour < 7){
		printf("noc\n");
	}
	else if(tajm->tm_hour >= 7 && tajm->tm_hour < 9){
		printf("jutro\n");
	}
	else if(tajm->tm_hour >= 9 && tajm->tm_hour < 12){
		printf("prepodne\n");
	}
	else if(tajm->tm_hour >= 12 && tajm->tm_hour < 19){
		printf("popodne\n");
	}
	else if(tajm->tm_hour >= 19 && tajm->tm_hour < 24){
		printf("vece\n");
	}

	exit(EXIT_SUCCESS);
}