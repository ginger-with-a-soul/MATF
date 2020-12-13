#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int veci_od(Cvor* lista, int broj);

int veci_od(Cvor* lista, int broj){
	int counter = 0;
	while(lista){
		if(lista->vrednost > broj){
			counter++;
		}
		lista = lista->sledeci;
	}
	return counter;
}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}

	Cvor *lista = NULL;
	FILE *ulaz;
	int x;

	ulaz = fopen(argv[1], "r");
	if(ulaz == NULL){
		greska();
	}
	ucitaj_listu(&lista, ulaz);

	scanf("%i", &x);

	x = veci_od(lista, x);

	printf("%i\n", x);

	oslobodi_listu(lista);
	fclose(ulaz);
	return 0;
}