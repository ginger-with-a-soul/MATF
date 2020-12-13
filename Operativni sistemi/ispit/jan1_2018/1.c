#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

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

	time_t now = (time_t) atoi(argv[1]);

	struct tm* timeStruct = localtime(&now);

	switch(timeStruct->tm_mon){
		case 0: printf("januar\n"); break;
		case 1: printf("februar\n"); break;
		case 2: printf("mart\n"); break;
		case 3: printf("april\n"); break;
		case 4: printf("maj\n"); break;
		case 5: printf("jun\n"); break;
		case 6: printf("jul\n"); break;
		case 7: printf("avgust\n"); break;
		case 8: printf("septembar\n"); break;
		case 9: printf("oktobar\n"); break;
		case 10: printf("novembar\n"); break;
		case 11: printf("decembar\n"); break;
		default: break;
	}

	exit(EXIT_SUCCESS);
}