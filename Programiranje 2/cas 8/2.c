#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA 51

void greska();
void ucitaj(char **niz, int n);
void ispisi(char **niz, int n);
void selection_sort(char **niz, int n);
void selection_sort_r(char **niz, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void ucitaj(char **niz, int n){
	
	for(int i = 0;i<n;i++){
		niz[i] = (char*)calloc(MAX_DUZINA, sizeof(char));
		if(niz[i] == NULL){
			greska();
		}
		fscanf(stdin, "%s", niz[i]);
	}
}

void ispisi(char **niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%s\n", niz[i]);
	}
}

void selection_sort(char **niz, int n){
	char tmp[MAX_DUZINA];
	int poz_min;
	for(int i = 0;i<n-1;i++){
		poz_min = i;
		for(int j = i+1;j<n;j++){
			if(strcmp(niz[j], niz[poz_min]) < 0){
				poz_min = j;
			}
		}
		strcpy(tmp, niz[i]);
		strcpy(niz[i], niz[poz_min]);
		strcpy(niz[poz_min], tmp);
	}
}

void selection_sort_r(char **niz, int n){
	char tmp[MAX_DUZINA];
	int poz_max, duzina_i, duzina_j;
	for(int i = 0;i<n-1;i++){
		poz_max = i;
		duzina_i = strlen(niz[i]);
		for(int j = i+1;j<n;j++){
			duzina_j = strlen(niz[j]);
			if(duzina_j > duzina_i || (duzina_i == duzina_j && (strcmp(niz[j], niz[poz_max]) < 0))){
				poz_max = j;
				duzina_i = duzina_j;
			}
		}
		strcpy(tmp, niz[i]);
		strcpy(niz[i], niz[poz_max]);
		strcpy(niz[poz_max], tmp);
	}
}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}

	int n;

	fscanf(stdin, "%i", &n);
	if(n < 1){
		greska();
	}

	char **niz;
	niz = (char**)calloc(n, sizeof(char*));
	if(niz == NULL){
		greska();
	}

	ucitaj(niz, n);


	if(strcmp(argv[1], "-s") == 0){
		selection_sort(niz, n);
	}
	else if(strcmp(argv[1], "-sr") == 0){
		selection_sort_r(niz, n);
	}
	else if(strcmp(argv[1], "-i") == 0){

	}
	else if(strcmp(argv[1], "-ir") == 0){

	}
	else if(strcmp(argv[1], "-m") == 0){

	}
	else if(strcmp(argv[1], "-mr") == 0){

	}
	else if(strcmp(argv[1], "-qsort") == 0){

	}
	else if(strcmp(argv[1], "-qsortr") == 0){

	}
	else{
		greska();
	}


	ispisi(niz, n);

	for(int i =  0;i<n;i++){
		free(niz[i]);
	}
	free(niz);
	return 0;
}