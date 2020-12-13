#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error();

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 3){
		error();
	}

	FILE *output;

	output = fopen("podniske.txt", "w");
	if(output == NULL){
		error();
	}

	int size = atoi(argv[1]), string = strlen(argv[2]);
	if(size < 1 || size > string){
		error();
	}

	for(int i = 0; i + size <= string; i++){
		for(int j = i, k = 0; k < size; j++, k++){
			fprintf(output, "%c", argv[2][j]);
		}
		fprintf(output, " ");
	}

	fclose(output);
	return 0;
}