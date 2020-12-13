#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		greska();
	}

	int duzina = strlen(argv[1]);
	for(int i = 0;i<duzina;i++){
		for(int j = 0;j<=i;j++){
			fprintf(stdout, "%c", argv[1][i]);
		}
	}

	return 0;
}