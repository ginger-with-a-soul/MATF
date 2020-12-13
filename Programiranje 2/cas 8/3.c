#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 0.000001

void greska();
void ispisi(double *niz, int n);
void selection_sort(double *niz, int n);
void selection_sort_r(double *niz, int n);


void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void ispisi(double *niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%g ", niz[i]);
	}
	fprintf(stdout, "\n");
}

void selection_sort(double *niz, int n){
	int poz_min;
	double tmp;
	for(int i = 0;i<n-1;i++){
		poz_min = i;
		for(int j = i+1;j<n;j++){
			if((niz[j] < niz[poz_min]) && fabs(niz[j] - niz[poz_min]) > EPS){
				poz_min = j;
			}
		}
		tmp = niz[i];
		niz[i] = niz[poz_min];
		niz[poz_min] = tmp;
	}
}

void selection_sort_r(double *niz, int n){
	int poz_max;
	double tmp;
	for(int i = 0;i<n-1;i++){
		poz_max = i;
		for(int j = i+1;j<n;j++){	
			if(niz[j] > niz[poz_max]){
				poz_max = j;
			}
		}
		tmp = niz[i];
		niz[i] = niz[poz_max];
		niz[poz_max] = tmp;
	}

}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}	

	int n;
	double *niz;
	fscanf(stdin, "%i", &n);
	if(n < 1){
		greska();
	}

	niz = (double*)calloc(n, sizeof(double));
	if(niz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%lf", &niz[i]);
	}

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