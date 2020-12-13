#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.0000001

typedef struct{
	float a1;
	float b1;
	float a2;
	float b2;
	float duzina;
}DUZ;

void greska();
void selection_sort(DUZ *niz, int n);
void ispis(DUZ *niz, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void ispis(DUZ *niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%.2f %.2f %.2f %.2f %.2f\n", niz[i].a1, niz[i].b1, niz[i].a2, niz[i].b2, niz[i].duzina);
	}
}

void selection_sort(DUZ *niz, int n){
	float tmp;
	int poz_max;
	for(int i = 0;i<n-1;i++){
		poz_max = i;
		for(int j = i+1;j<n;j++){
			if(niz[j].duzina >= niz[poz_max].duzina && niz[j].a1 > niz[poz_max].a1 && fabs(niz[j].duzina - niz[poz_max].duzina) > EPS){
				poz_max = j;
			}
		}
		tmp = niz[poz_max].duzina;
		niz[poz_max].duzina = niz[i].duzina;
		niz[i].duzina = tmp;

		tmp = niz[poz_max].a1;
		niz[poz_max].a1 = niz[i].a1;
		niz[i].a1 = tmp;

		tmp = niz[poz_max].b1;
		niz[poz_max].b1 = niz[i].b1;
		niz[i].b1 = tmp;

		tmp = niz[poz_max].duzina;
		niz[poz_max].a2 = niz[i].a2;
		niz[i].a2 = tmp;

		tmp = niz[poz_max].b2;
		niz[poz_max].b2 = niz[i].b2;
		niz[i].b2 = tmp;
	}
}

int main(){

	FILE *ulaz;
	int n;
	DUZ *niz;

	ulaz = fopen("duzi.txt", "r");
	if(ulaz == NULL){
		greska();
	}

	fscanf(ulaz, "%i", &n);
	if(n < 1){
		greska();
	}

	niz = (DUZ*)calloc(n, sizeof(DUZ));
	if(niz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(ulaz, "%f %f %f %f", &niz[i].a1, &niz[i].b1, &niz[i].a2, &niz[i].b2);
		if(niz[i].a1 < 0 || niz[i].b1 < 0 || niz[i].a2 < 0 || niz[i].b2 < 0){
			greska();
		}
		niz[i].duzina = sqrtf(powf((niz[i].a1-niz[i].a2), 2) + powf((niz[i].b1-niz[i].b2), 2));
	}

	selection_sort(niz, n);

	ispis(niz, n);

	free(niz);
	fclose(ulaz);

	return 0;
}