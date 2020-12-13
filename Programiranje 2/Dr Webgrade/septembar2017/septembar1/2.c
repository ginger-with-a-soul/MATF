#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 21

typedef struct{

	char naziv[MAX_NAZIV];
	float cena;
	int kolicina;
	float ukupno;

}PROIZVOD;

void error();
int poredi(const void *a, const void *b);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int poredi(const void *a, const void *b){
	PROIZVOD *prvi = (PROIZVOD*)a;
	PROIZVOD *drugi = (PROIZVOD*)b;

	if(prvi->ukupno < drugi->ukupno){
		return -1;
	}
	else if(prvi->ukupno > drugi->ukupno){
		return 1;
	}
	else{
		return strcmp(drugi->naziv, prvi->naziv);
	}
}

int main(){

	FILE *input;
	PROIZVOD *niz;
	int velicina = 100, i = 0;

	input = fopen("proizvodi.txt", "r");
	if(input == NULL){
		error();
	}

	niz = (PROIZVOD*)calloc(velicina, sizeof(PROIZVOD));
	if(niz == NULL){
		error();
	}

	while(fscanf(input, "%s %f %i", niz[i].naziv, &niz[i].cena, &niz[i].kolicina) != EOF){
		if(niz[i].cena < 0 || niz[i].kolicina < 1){
			error();
		}
		niz[i].ukupno = niz[i].cena * niz[i].kolicina;
		if(i + 10 == velicina){
			velicina += 100;
			niz = realloc(niz, velicina*sizeof(PROIZVOD));
			if(niz == NULL){
				error();
			}
		}
		i++;
	}

	qsort(niz, i, sizeof(PROIZVOD), poredi);

	for(int j = 0; j < i; j++){
		fprintf(stdout, "%s %.2f\n", niz[j].naziv, niz[j].ukupno);
	}

	free(niz);
	fclose(input);
	return 0;
}