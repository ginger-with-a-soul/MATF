#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA_LINIJE 201
#define MAX_IME_DATOTEKE 51

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc!=3){
		greska();
	}

	char dat1[MAX_IME_DATOTEKE], dat2[MAX_IME_DATOTEKE], linija1[MAX_DUZINA_LINIJE], linija2[MAX_DUZINA_LINIJE];
	int i = 0;
	strcpy(dat1, argv[1]);
	strcpy(dat2, argv[2]);

	FILE *ulaz, *izlaz;

	ulaz = fopen(dat1, "r");
	if(ulaz == NULL){
		greska();
	}

	izlaz = fopen(dat2, "r");
	if(izlaz == NULL){
		greska();
	}


	while(fgets(linija1, MAX_DUZINA_LINIJE, ulaz) != NULL && fgets(linija2, MAX_DUZINA_LINIJE, izlaz) != NULL){
		i++;
		if(strcmp(linija1, linija2) != 0){
			fprintf(stdout, "%i\n", i);
		}

	}




	fclose(ulaz);
	fclose(izlaz);

	return 0;
}