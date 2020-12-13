#include <stdio.h>
#include <stdlib.h>

#define MAX_LINIJA 81

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz;

	ulaz = fopen("//home//dimitrije//Desktop//cas 1//knjiga.txt", "r");

	if(ulaz == NULL){
		greska();
	}

	char linija[MAX_LINIJA];

	unsigned brojac = 0;

	while(fgets(linija, MAX_LINIJA, ulaz) != NULL){
		brojac++;
	}

	fprintf(stdout, "%u\n", brojac);

	fclose(ulaz);

	return 0;
}