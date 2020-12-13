#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_REC 128
#define MAX_DAT 64

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	char imeDat[MAX_DAT], rec[MAX_REC], c;
	unsigned k, duzina;
	int i = 0;
	FILE *ulaz, *izlaz;

	fscanf(stdin, "%s %u", imeDat, &k);
	if(k<0){
		greska();
	}
	ulaz = fopen(imeDat, "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen("rotirano.txt", "w");
	if(izlaz == NULL){
		greska();
	}

	while((c = fgetc(ulaz)) != EOF){
		if(c != ' '){
			rec[i] = c;
			i++;
			duzina = i;
		}
		else{
			i = 0;
			for(int j = 0;j<abs(duzina-k);j++){
				fputc(rec[k+j], izlaz);
			}
			for(int j = 0;j<k;j++){
				fputc(rec[j], izlaz);
			}
			fputc(' ', izlaz);
		}
	}

	for(int j = 0;j<abs(duzina-k);j++){
		fputc(rec[k+j], izlaz);
	}
	for(int j = 0;j<k;j++){
		fputc(rec[j], izlaz);
	}

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}