#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_REC 256

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	FILE *ulaz, *izlaz;
	char rec[MAX_REC], c;
	int suma = 0, i = 0;

	ulaz = fopen("ulaz.txt", "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen("izlaz.txt", "w+");
	if(izlaz == NULL){
		greska();
	}

	do{
		c = fgetc(ulaz);
		if(c != ' ' && c != '\n'){
			suma += c;
			rec[i++] = c;
		}
		else if(suma>1000){
			rec[i] = '\t';
			for(int j = 0;rec[j] != '\t';j++){
				fputc(rec[j], izlaz);
			}
			fputc(' ', izlaz);
			i = 0;
			suma = 0;
		}
		else{
			i = 0;
			suma = 0;
		}

	}while(c != EOF);

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}