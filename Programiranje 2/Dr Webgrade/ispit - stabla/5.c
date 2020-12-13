#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

int parno_podstablo(Cvor* koren);

int parno_podstablo(Cvor* koren){
	
}

int main(){
	
	Cvor* koren = NULL;

	ucitaj_stablo(&koren, stdin);

	printf("%i\n", parno_podstablo(koren));

	oslobodi_stablo(koren);
	return 0;
}