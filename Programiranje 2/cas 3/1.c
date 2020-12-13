#include <stdio.h>
#include <stdlib.h>

#define MAX_DUZINA 51

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz;

	ulaz = fopen("imena.txt", "r+");

	char *ime, *prezime;

	ime = (char*)calloc(MAX_DUZINA, sizeof(char));
	if(ime == NULL){
		greska();
	}

	prezime = (char*)calloc(MAX_DUZINA, sizeof(char));
	if(prezime == NULL){
		greska();
	}

	while(1){
		if(feof(ulaz)){
			break;
		}
		fscanf(ulaz, "%*i. %s %s %*f", ime, prezime);
		printf("%s %s\n", ime, prezime);
	}




	fclose(ulaz);
	free(ime);
	free(prezime);

	return 0;
}