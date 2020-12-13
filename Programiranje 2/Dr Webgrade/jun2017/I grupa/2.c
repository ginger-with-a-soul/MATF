#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error();
int poredi(const void *a, const void *b);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

typedef struct{
	char domacin[21];
	char gost[21];
	unsigned gd;
	unsigned gg;
}DUEL;

int poredi(const void *a, const void *b){
	DUEL *prvi = (DUEL*)a;
	DUEL *drugi = (DUEL*)b;

	int golRazlikaPrvog = abs(prvi->gd - prvi->gg);
	int goldRazlikaDrugog = abs(drugi->gd - drugi->gg);

	if(golRazlikaPrvog - goldRazlikaDrugog < 0){
		return -1;
	}
	else if(golRazlikaPrvog - goldRazlikaDrugog > 0){
		return 1;
	}
	else{
		int domacin_ime = strcmp(prvi->domacin, drugi->domacin);
		if(domacin_ime < 0){
			return 1;
		}
		else if(domacin_ime > 0)
			return -1;
		else{
			return strcmp(prvi->gost, drugi->gost);
		}
	}
}

int main(){

	int broj_duela;

	scanf("%i", &broj_duela);
	if(broj_duela < 1){
		error();
	}

	DUEL *niz;

	niz = (DUEL*)calloc(broj_duela, sizeof(DUEL));
	if(niz == NULL){
		error();
	}

	for(int i = 0; i < broj_duela; i++){
		scanf("%s %s %u %u", niz[i].domacin, niz[i].gost, &niz[i].gd, &niz[i].gg);
		if(niz[i].gd < 0 || niz[i].gg < 0){
			error();
		}
	}

	qsort(niz, broj_duela, sizeof(DUEL), poredi);

	for(int i = 0; i < broj_duela; i++){
		fprintf(stdout, "%s %s\n", niz[i].domacin, niz[i].gost);
	}

	free(niz);
	return 0;
}