#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
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


void month_printer(int month);
int main(int argc, char** argv){

	check_error(argc != 3, "invalid arg count");

	time_t now = atoi(argv[1]);

	struct tm* tajm = localtime(&now);

	month_printer(tajm->tm_wday);

	tajm->tm_year += atoi(argv[2]);

	time_t sec = mktime(tajm);

	tajm = localtime(&sec);

	month_printer(tajm->tm_wday);
	printf("\n");


	exit(EXIT_SUCCESS);
}

void month_printer(int month){
	switch(month){
		case 0: printf("nedelja "); break;
		case 1: printf("ponedeljak "); break;
		case 2: printf("utorak "); break;
		case 3: printf("sreda "); break;
		case 4: printf("cetvrtak "); break;
		case 5: printf("petak "); break;
		case 6: printf("subota "); break;
		default: break;
	}
}