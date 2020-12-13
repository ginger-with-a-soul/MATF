#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int main(){

	cvor *glava = NULL, *novi;
	FILE* izlaz;
	int vrednost;
	unsigned n;

	izlaz = fopen("izlaz.txt", "w");
	if(izlaz == NULL){
		error();
	}

	scanf("%u", &n);
	if(n < 1){
		error();
	}
	for(int i = 0; i < n; i++){
		scanf("%i", &vrednost);
		novi = napravi_cvor(vrednost);
		dodaj_na_pocetak(glava, novi);
	}

	ispisi_listu(glava, izlaz);

	return 0;
}