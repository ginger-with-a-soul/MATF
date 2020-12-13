#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greska();
void ucitaj(int *niz, int n);
void ispisi(int *niz, int n);
void selection_sort(int *niz, int n);
void selection_sort_r(int *niz, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void ucitaj(int *niz, int n){
	for(int i = 0;i<n;i++){
		fscanf(stdin, "%i", &niz[i]);
	}
}

void ispisi(int *niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%i ", niz[i]);
	}
	fprintf(stdout, "\n");
}

void selection_sort(int *niz, int n){
	int tmp, poz_min;
	for(int i = 0;i<n-1;i++){
		poz_min = i;
		for(int j = i+1;j<n;j++){
			if(niz[j] < niz[poz_min]){
				poz_min = j;
			}
		}
		tmp = niz[poz_min];
		niz[poz_min] = niz[i];
		niz[i] = tmp;
	}
}

void selection_sort_r(int *niz, int n){
	int poz_max, tmp;
	for(int i = 0;i<n-1;i++){
		poz_max = i;
		for(int j = i+1;j<n;j++){
			if(niz[j] > niz[poz_max]){
				poz_max = j;
			}
		}
		tmp = niz[poz_max];
		niz[poz_max] = niz[i];
		niz[i] = tmp;
	}
}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}

	int *niz, n;

	fscanf(stdin, "%i", &n);
	if(n<1){
		greska();
	}

	niz = (int*)calloc(n, sizeof(int));
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

	free(niz);

	return 0;
}