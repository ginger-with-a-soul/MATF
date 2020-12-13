#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_REC 128

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	FILE *ulaz, *izlaz;
	char rec[MAX_REC], c;
	int i = 0, duzina = 0, j = 0, br = 0;;

	ulaz = fopen("razno.txt", "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen("palindromi.txt", "w");
	if(izlaz == NULL){
		greska();
	}

	do{
		c = fgetc(ulaz);
		if(c != ' ' && c != '\n'){
			rec[i++] = c;
			duzina = i;
		}
		else{
			if(duzina == 1){
				fputc(rec[0], izlaz);
				fputc(' ', izlaz);
				i = 0;
				continue;
			}
			rec[i] = '\t';
			j = duzina - 1;
			for(i = 1;duzina/i >= 2;i++, j--){
				if(tolower(rec[i-1]) == tolower(rec[j])){
					br++;
				}
			}
			if(br != 0 && duzina/br >= 1 && duzina/br <= 3){
				i = 0;
				while(rec[i] != '\t'){
					fputc(rec[i], izlaz);
					i++;
				}
				fputc(' ', izlaz);
			}
			br = 0;
			i = 0;
		}

	}while(c != EOF);

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}