#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void obrisi_cvor(Cvor** lista, int broj){
	if(*lista == NULL){
		return;
	}
	else if((*lista)->vrednost == broj){
		Cvor* tmp = *lista;
		*lista = (*lista)->sledeci;
		free(tmp);
		obrisi_cvor(lista, broj);
	}
	else{
		obrisi_cvor(&(*lista)->sledeci, broj);
	}

}

int main(){
	int x;
	Cvor* lista = NULL;

	while(1){
		scanf("%i", &x);
		if(x == 0){
			break;
		}
		dodaj_na_kraj(&lista, x);
	}
	scanf("%i", &x);
	obrisi_cvor(&lista, x);
	ispisi_listu(lista);
	oslobodi_listu(lista);
	return 0;
}