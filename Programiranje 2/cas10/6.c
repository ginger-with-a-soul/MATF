#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void umetni(Cvor** lista, int k);

void umetni(Cvor** lista, int k){
	if(*lista == NULL || (*lista)->sledeci == NULL){
		return;
	}
	if((*lista)->vrednost + (*lista)->sledeci->vrednost == k || abs((*lista)->vrednost - (*lista)->sledeci->vrednost) == k){
			Cvor* novi = napravi_cvor(-1);
			novi->sledeci = (*lista)->sledeci;
			(*lista)->sledeci = novi;
			umetni(&(novi)->sledeci, k);
	}
	else{
		umetni(&(*lista)->sledeci, k);
	}

}


int main(){

	int x, k;
	Cvor* lista = NULL;

	while(1){
		scanf("%i", &x);
		if(!x){
			break;
		}
		dodaj_na_kraj(&lista, x);
	}

	scanf("%i", &k);

	umetni(&lista, k);
	ispisi_listu(lista);
	oslobodi_listu(lista);

	return 0;
}