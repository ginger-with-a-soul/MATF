#include <stdio.h>
#include <stdlib.h>

#define MAX_IME 51

typedef struct artikal{
	unsigned long bar_kod;
	char ime_artikla[MAX_IME];
	char proizvodjac[MAX_IME];
	double cena;
}ARTIKAL;

void greska();
unsigned long poredi(const void*, const void*);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned long poredi(const void* ulazni_bar_kod, const void* niz){
	return *(unsigned long*)ulazni_bar_kod - *(unsigned long*)niz;
}

int main(){
	int velicina = 10, broj_linija = 0, i = 0, j = -1;
	double suma = 0;
	unsigned long ulazni_bar_kod;
	char imeUlaza[MAX_IME], *linija = NULL;
	size_t duzina_linije = 0;
	FILE *ulaz;
	ARTIKAL *niz, *binarna_pretraga;

	fscanf(stdin, "%s", imeUlaza);
	ulaz = fopen(imeUlaza, "r");
	if(ulaz == NULL){
		greska();
	}

	niz = (ARTIKAL*)calloc(velicina, sizeof(ARTIKAL));
	if(niz == NULL){
		greska();
	}

	while(getline(&linija, &duzina_linije, ulaz) != EOF){
		broj_linija++;
		if(broj_linija>velicina){
			velicina += 10;
			niz = (ARTIKAL*)realloc(niz, velicina);
			if(niz == NULL){
				greska();
			}
		}
		sscanf(linija, "%lu %s %s %lf", &niz[i].bar_kod, niz[i].ime_artikla, niz[i].proizvodjac, &niz[i].cena);
	}

	do{

		fscanf(stdin, "%lu", &ulazni_bar_kod);
		if(ulazni_bar_kod < 0){
			greska();
		}
		binarna_pretraga = bsearch(&ulazni_bar_kod, niz, broj_linija, sizeof(ARTIKAL), &poredi);
		if(binarna_pretraga == NULL){
			fprintf(stdout, "Nepostojeci bar kod\n");
		}
		else{
			suma += niz->cena;
		}


	}while(ulazni_bar_kod != 0);

	fprintf(stdout, "%g", suma);



	free(niz);
	fclose(ulaz);
	return 0;
}