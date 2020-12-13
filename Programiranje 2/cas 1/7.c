#include <stdio.h>

int main(int argc, char *argv[]){

	int i = 0;

	fprintf(stdout, "%i", argc);

	for(i = 0;i<argc;i++){
		fprintf(stdout, "\n%i. %s", i+1, argv[i]);
	}

	fprintf(stdout, "\n");


	return 0;
}