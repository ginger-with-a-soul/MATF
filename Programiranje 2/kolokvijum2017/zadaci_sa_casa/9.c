#include <stdio.h>
#include <stdlib.h>

#define MAX_IME 21

typedef struct{
	char ime[MAX_IME];
	int novac;
	int zaduzen;
}KORISNIK;

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz;
	KORISNIK *niz;
	int velicina = 40, i = 0, broj_zaduzenih = 0, suma = 0;
	double prosecno_zaduzenje;
	char *linija = NULL;
	size_t duzina_linije = 0;

	niz = (KORISNIK*)calloc(velicina, sizeof(KORISNIK));
	if(niz == NULL){
		greska();
	}

	ulaz = fopen("saldo.txt", "r");
	if(ulaz == NULL){
		greska();
	}

	while(getline(&linija, &duzina_linije, ulaz) != -1){
		sscanf(linija, "%s %i", niz[i].ime, &niz[i].novac);
		if(i == (velicina-2)){
			velicina += velicina;
			niz = (KORISNIK*)realloc(niz, velicina);
			if(niz == NULL){
				greska();
			}
		}
		if(niz[i].novac < 0){
			niz[i].zaduzen = 1;
			suma += niz[i].novac;
			broj_zaduzenih++;
			prosecno_zaduzenje = (double)suma/broj_zaduzenih;
		}
		i++;
	}

	for(int j = 0;j<i;j++){
		if(niz[j].novac < prosecno_zaduzenje){
			fprintf(stdout, "%s\n", niz[j].ime);
		}
	}
	free(niz);
	fclose(ulaz);
	return 0;
}