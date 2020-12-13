#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 64

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	char ime1[MAX], ime2[MAX], c;
	FILE *ulaz, *izlaz;

	fscanf(stdin, "%s %s", ime1, ime2);
	ulaz = fopen(ime1, "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen(ime2, "w");
	if(izlaz == NULL){
		greska();
	}

	while((c = fgetc(ulaz)) != EOF){
		if(isdigit(c)){
			fputc('0', izlaz);
		}
		else if(isalpha(c)){
			fputc('1', izlaz);
		}
		else if(c == '\n'){
			continue;
		}
		else{
			fputc('2', izlaz);
		}
	}

	fclose(ulaz);
	fclose(izlaz);

	return 0;
}