#include <stdio.h>
#include <stdlib.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int main(int argc, char** argv){
	
	check_error(argc == 2, "invalid arg");
	
	FILE* f = fopen(argv[1], "r");
	check_error(f != NULL, "fopen failed");
	
	double sum = 0;
	int n = 0;
	double x;
	while (fscanf(f, "%lf", &x) == 1){
		
		sum += x;
		n++;
	}
		
	check_error(feof(f), "format error");
	
	printf("%lf\n", n != 0 ? sum/n : 0);
	
	exit(EXIT_SUCCESS);
}
