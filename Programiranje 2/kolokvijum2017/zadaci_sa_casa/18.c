#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 4){
		greska();
	}

	int n = atoi(argv[3]), duzina = strlen(argv[1]), count = 0, prvo_pojavljivanje = 0, drugo_pojavljivanje = 0;
	if(n<0){
		greska();
	}

	for(int i = 0;i<duzina;i++){
		if(argv[2][0] == argv[1][i]){
			count++;
			if(count == 1){
				prvo_pojavljivanje = i;
			}
			else if(count == 2){
				drugo_pojavljivanje = i;
			}
		}
	}

	if(count < 2){
		printf("%s\n", argv[1]);
		exit(EXIT_SUCCESS);
	}
	
	for(int i = prvo_pojavljivanje + 1;i<drugo_pojavljivanje;i++){
		char c = argv[1][i];
		argv[1][i] = c + n;
	}
	printf("%s\n", argv[1]);

	return 0;
}