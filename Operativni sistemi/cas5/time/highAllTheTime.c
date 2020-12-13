#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/time.h>

#define MAX_SIZE 1024
#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 1, "Invalid arg count");
	time_t now = time(NULL);
	char* cTime = malloc(MAX_SIZE);

	check_error(cTime == NULL, "malloc() failure");
	cTime = ctime(&now);
	printf("%s", cTime);

	char buffer[MAX_SIZE];
	struct tm* brokenTime = localtime(&now);
	check_error(brokenTime == NULL, "localtime() failure");

	int flag;
	check_error((flag = strftime(buffer, MAX_SIZE, "Day:%A Month:%B Day of year:%j\n", brokenTime)) == -1, "strftime() failure");
	printf("%s", buffer);

	exit(EXIT_SUCCESS);

}