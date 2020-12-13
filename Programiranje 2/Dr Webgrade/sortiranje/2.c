#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAZIV 21

typedef struct{
	char naziv[MAX_NAZIV];
	float cena;
	float kolicina;
	float ukupno;
}PROIZVOD;

void greska();
void ispis(PROIZVOD *niz, int n);
void selection_sort(PROIZVOD *niz, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void ispis(PROIZVOD *niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%s %.2f %.2f %.2f\n", niz[i].naziv, niz[i].cena, niz[i].kolicina, niz[i].ukupno);
	}
}

void selection_sort(PROIZVOD *niz, int n){
	float tmp;
	char ime[MAX_NAZIV];
	int poz_max;
	for(int i = 0;i<n-1;i++){
		poz_max = i;
		for(int j = i+1;j<n;j++){
			if(niz[j].ukupno > niz[poz_max].ukupno){
				poz_max = j;
			}
		}
		tmp = niz[i].ukupno;
		niz[i].ukupno = niz[poz_max].ukupno;
		niz[poz_max].ukupno = tmp;

		tmp = niz[i].cena;
		niz[i].cena = niz[poz_max].cena;
		niz[poz_max].cena = tmp;

		tmp = niz[i].kolicina;
		niz[i].kolicina = niz[poz_max].kolicina;
		niz[poz_max].kolicina = tmp;

		strcpy(ime, niz[i].naziv);
		strcpy(niz[i].naziv, niz[poz_max].naziv);
		strcpy(niz[poz_max].naziv, ime);
	}
}


int main(){

	FILE *ulaz;
	PROIZVOD *niz;
	int n;

	ulaz = fopen("proizvodi.txt", "r");
	if(ulaz == NULL){
		greska();
	}

	fscanf(ulaz, "%i", &n);
	if(n<1){
		greska();
	}

	niz = (PROIZVOD*)calloc(n, sizeof(PROIZVOD));
	if(niz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(ulaz, "%s %f %f", niz[i].naziv, &niz[i].cena, &niz[i].kolicina);
		if(niz[i].cena <= 0 || niz[i].kolicina <= 0){
			greska();
		}
		niz[i].ukupno = niz[i].cena * niz[i].kolicina;
	}

	selection_sort(niz, n);

	ispis(niz, n);

	free(niz);
	fclose(ulaz);

	return 0;
}