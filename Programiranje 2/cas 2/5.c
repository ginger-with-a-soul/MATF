#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA_RECI 21

void greska();
void greska(){
	printf("-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	char *uneta, *niz_reci;
	int n, i = 0, prvo_pojavljivanje = -1, poslenje_pojavljivanje = -1;

	uneta = (char*)calloc(MAX_DUZINA_RECI, sizeof(char));
	if(uneta == NULL){
		greska();
	}

	niz_reci = (char*)calloc(MAX_DUZINA_RECI, sizeof(char));
	if(niz_reci == NULL){
		greska();
	}

	scanf("%s %i", uneta, &n);
	if(n<1){
		greska();
	}

	for(i = 0;i<n;i++){
		scanf("%s", niz_reci);
		if(strcmp(uneta, niz_reci) == 0){
			if(prvo_pojavljivanje == -1){
				prvo_pojavljivanje = i;
			}
			poslenje_pojavljivanje = i;
		}
	}

	fprintf(stdout, "%i %i", prvo_pojavljivanje, poslenje_pojavljivanje);

	free(uneta);
	free(niz_reci);


	return 0;
}