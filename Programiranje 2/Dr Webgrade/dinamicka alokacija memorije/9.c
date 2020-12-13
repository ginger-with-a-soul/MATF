#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

	FILE *ulaz;
	char c;
	int zagrada = 0;

	ulaz = fopen(argv[1], "r");
	if(ulaz == NULL){
		greska();
	}

	while((c = fgetc(ulaz)) != EOF){
		if(c == ')' && zagrada == 0){
			fprintf(stdout, "nisu\n");
			return 1;
		}
		else if(c == '('){
			zagrada++;
		}
		else if(c == ')'){
			zagrada--;
		}
	}

	if(!zagrada){
		fprintf(stdout, "jesu\n");
	}
	else{
		fprintf(stdout, "nisu\n");
	}

	fclose(ulaz);
	return 0;
}