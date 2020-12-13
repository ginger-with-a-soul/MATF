#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DUZINA_RECI 51
#define MAX_IME_DATOTEKE 21

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz, *izlaz;
	unsigned n, i = 0;
	char imeDatoteke[MAX_IME_DATOTEKE], prvaRec[MAX_DUZINA_RECI], donjaCrta[] = "_", rec[MAX_DUZINA_RECI];

	scanf("%s", imeDatoteke);

	if(strlen(imeDatoteke)>20){
		greska();
	}

	ulaz = fopen(imeDatoteke, "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen("//home//dimitrije//Desktop//cas 1//rezZa6.txt", "w");
	if(izlaz == NULL){
		greska();
	}

	fscanf(ulaz, "%u", &n);
	if(n<1){
		greska();
	}

	fscanf(ulaz, "%s", prvaRec);
	fprintf(stdout, "%s ", prvaRec);
	for(i = 1;i<n;i++){
		fscanf(ulaz, "%s", rec);
		fprintf(stdout, "%s ", rec);
		if(strstr(rec, prvaRec) != NULL && strstr(rec, donjaCrta) != NULL){
			fprintf(izlaz, "%s ", rec);
		}
	}

	printf("\n");


	fclose(ulaz);
	fclose(izlaz);

	return 0;
}
