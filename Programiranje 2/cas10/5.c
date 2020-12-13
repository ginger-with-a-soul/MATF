#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void manji_od_sume_prethodnih(Cvor** lista, int suma);

void manji_od_sume_prethodnih(Cvor** lista, int suma){
	if(*lista == NULL){
		return;
	}
	Cvor *trenutni = *lista;
	if(trenutni->vrednost < suma){
		*lista = (*lista)->sledeci;
		suma += trenutni->vrednost;
		free(trenutni);
		manji_od_sume_prethodnih(lista, suma);
	}
	else{
		manji_od_sume_prethodnih(&(*lista)->sledeci, suma + (*lista)->vrednost);
	}

}
int main(){

	int x, suma = 0;
	Cvor *lista = NULL;

	while(1){
		scanf("%i", &x);
		if(!x){
			break;
		}
		dodaj_na_kraj(&lista, x);
	}

	manji_od_sume_prethodnih(&lista, suma);
	ispisi_listu(lista);
	oslobodi_listu(lista);

	return 0;
}