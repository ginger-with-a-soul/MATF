#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void izbaci_susede(Cvor** lista, int k);

void izbaci_susede(Cvor** lista, int k){
	if(*lista == NULL || (*lista)->sledeci == NULL){
		return;
	}

	if((*lista)->vrednost + (*lista)->sledeci->vrednost == k){
		Cvor* tmp1, *tmp2;
		tmp1 = *lista;
		tmp2 = (*lista)->sledeci;
		(*lista)->sledeci = 
		izbaci_susede(&(*lista)->sledeci, k);
		free(tmp1);
		free(tmp2);
	}
	else{
		izbaci_susede(&(*lista)->sledeci, k);
	}

}

int main(){

	int x, k;
	Cvor* lista = NULL;

	while(1){
		fscanf(stdin, "%i", &x);
		if(!x){
			break;
		}
		dodaj_na_kraj(&lista, x);
	}

	fscanf(stdin, "%i", &k);

	izbaci_susede(&lista, k);
	ispisi_listu(lista);
	oslobodi_listu(lista);

	return 0;
}