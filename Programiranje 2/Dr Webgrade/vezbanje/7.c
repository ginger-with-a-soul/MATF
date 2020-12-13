#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MODEL_I_MARKA 31
#define MAX_NAZIV_DATOTEKE 21

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}
typedef struct{
		char marka[MAX_MODEL_I_MARKA];
		char model[MAX_MODEL_I_MARKA];
		int cena;
}KARAKTERISTIKE;

int main(int argc, char *argv[]){
	if(argc != 2){
		greska();
	}

	FILE *ulaz;
	int n, pare;
	char imeDatoteke[MAX_NAZIV_DATOTEKE], *linija = NULL, *nizModela[];
	size_t duzina_linije = 0;

	pare = atoi(argv[1]);

	fscanf(stdin, "%s", imeDatoteke);

	ulaz = fopen(imeDatoteke, "r");
	if(ulaz == NULL){
		greska();
	}

	fscanf(ulaz, "%i", &n);
	if(n<1){
		greska();
	}

	KARAKTERISTIKE niz[n];
	int nizProseka[n];

	for(int i = 0;i<n;i++){
		nizProseka[i] = 0;
	}

	for(int i = -1;i<n;i++){
		if(i == -1){
			getline(&linija, &duzina_linije, ulaz);
			continue;
		}
		else{
			getline(&linija, &duzina_linije, ulaz);
			sscanf(linija, "%s %s %i", niz[i].marka, niz[i].model, &niz[i].cena);
			for(int j = 0;j<n;j++){
				int k = 0;
				if(strcmp(niz[i].model, nizModela[j]) == 0){
					nizCena[i]++;
				}
			}
			if(niz[i-1].cena<1){
				greska();
			}
		}
	}


	for(int i = 0;i<n;i++){
		if(pare >= niz[i].cena){
			fprintf(stdout, "%s %s %i [Prosek za %s: ]\n", niz[i].marka, niz[i].model, niz[i].cena, niz[i].marka);
		}
	}

	free(linija);
	fclose(ulaz);
	return 0;
}