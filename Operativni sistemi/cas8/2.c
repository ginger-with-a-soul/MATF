#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

#include <sys/wait.h>


#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\


int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	FILE* f = fopen(argv[1], "r");
	check_error(f == NULL, "fopen() failure");

	double sum = 0, x;
	int n = 0;

	while(fscanf(f, "%lf", &x) == 1){
		sum += x;
		n++;
	}

	check_error(feof(f), "File content error");

	printf("%f", sum != 0? sum / n : 0);			

	fclose(f);

	exit(EXIT_SUCCESS);
}