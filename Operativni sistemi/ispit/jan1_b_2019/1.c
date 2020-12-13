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
#include <sys/time.h>

#define MAX_SIZE (1024)
#define SEC (24 * 60 * 60)

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

	time_t arg1 = atoi(argv[1]);

	struct tm* time_struct = localtime(&arg1);
	int month = time_struct->tm_mon + 1;
	
	month_printer(month);

	time_t new = arg1 + SEC * atoi(argv[2]);
	time_struct = localtime(&new);

	month = time_struct->tm_mon + 1;
	month_printer(month);
	printf("\n");

	exit(EXIT_SUCCESS);
}

void month_printer(int month){
	switch(month){
		case 1: printf("januar "); break;
		case 2: printf("februar "); break;
		case 3: printf("mart "); break;
		case 4: printf("april "); break;
		case 5: printf("maj "); break;
		case 6: printf("jun "); break;
		case 7: printf("jul "); break;
		case 8: printf("avgust "); break;
		case 9: printf("septembar "); break;
		case 10: printf("oktobar "); break;
		case 11: printf("novembar "); break;
		case 12: printf("decembar "); break;
		default: break;
	}
}