#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

Cvor* objedini(Cvor* lista1, Cvor* lista2){
	if(lista1 == NULL){
		return lista2;
	}
	else if(lista2 == NULL){
		return lista1;
	}

	Cvor* nova_glava;
	if(lista1->vrednost <= lista2->vrednost){
		nova_glava = lista1;
		lista1 = lista1->sledeci;
	}
	else{
		nova_glava = lista2;
		lista2 = lista2->sledeci;
	}
	Cvor* tekuci = nova_glava;
	while(lista1 && lista2){
		if(lista1->vrednost <= lista2->vrednost){
			tekuci->sledeci = lista1;
			lista1 = lista1->sledeci;
		}
		else{
			tekuci->sledeci = lista2;
			lista2 = lista2->sledeci;
		}
		tekuci = tekuci->sledeci;
	}

	while(1){
		if(lista1){
			tekuci->sledeci = lista1;
			tekuci = tekuci->sledeci;
			lista1 = lista1->sledeci;
		}
		else if(lista2){
			tekuci->sledeci = lista2;
			tekuci = tekuci->sledeci;
			lista2 = lista2->sledeci;
		}
		else{
			break;
		}
	}

	return nova_glava;

}

int main(int argc, char *argv[]){
	if(argc != 3){
		greska();
	}
	FILE *ulaz1, *ulaz2;
	Cvor *lista1 = NULL, *lista2 = NULL, *lista;
	ulaz1 = fopen(argv[1], "r");
	if(ulaz1 == NULL){
		greska();
	}
	ulaz2 = fopen(argv[2], "r");
	if(ulaz2 == NULL){
		greska();
	}
	ucitaj_listu(&lista1, ulaz1);
	ucitaj_listu(&lista2, ulaz2);
	lista = objedini(lista1, lista2);
	ispisi_listu(lista);
	oslobodi_listu(lista);
	fclose(ulaz1);
	fclose(ulaz2);
	return 0;
}