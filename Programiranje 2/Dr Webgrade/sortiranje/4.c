#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greska();
void ispisi(double *nizX, double *nizY, int i);
void selection_sort(double *nizX, double *nizY, int i);

void ispisi(double *nizX, double *nizY, int i){
	for(int j = 0;j<i;j++){
		fprintf(stdout, "%.2lf %.2lf\n", nizX[j], nizY[j]);
	}
}

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void selection_sort(double *nizX, double *nizY, int i){
	double tmp;
	int poz_min;
	for(int k = 0;k<i-1;k++){
		poz_min = k;
		for(int j = k+1;j<i;j++){
			if((nizX[j] < nizX[poz_min]) || (nizX[j] == nizX[poz_min] && nizY[j] > nizY[poz_min])){
				poz_min = j;
			}
		}
		tmp = nizX[k];
		nizX[k] = nizX[poz_min];
		nizX[poz_min] = tmp;

		tmp = nizY[k];
		nizY[k] = nizY[poz_min];
		nizY[poz_min] = tmp;
	}
}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}

	FILE *ulaz;

	ulaz = fopen(argv[1], "r");
	if(ulaz == NULL){
		greska();
	}

	double *nizX, *nizY;
	int korak = 1, i = 0;

	nizX = (double*)calloc(korak, sizeof(double));
	if(nizX == NULL){
		greska();
	}
	nizY = (double*)calloc(korak, sizeof(double));
	if(nizY == NULL){
		greska();
	}

	while(fscanf(ulaz, "%lf %lf", &nizX[i], &nizY[i]) == 2){
		korak += 1;
		nizX = (double*)realloc(nizX, korak*sizeof(double));
		if(nizX == NULL){
			greska();
		}
		nizY = (double*)realloc(nizY, korak*sizeof(double));
		if(nizY == NULL){
			greska();
		}
		i++;
	}

	selection_sort(nizX, nizY, i);

	ispisi(nizX, nizY, i);


	free(nizX);
	free(nizY);
	fclose(ulaz);
	return 0;
}