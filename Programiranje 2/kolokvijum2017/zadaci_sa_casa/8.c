#include <stdio.h>
#include <stdlib.h>

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz;
	int n, **matrica, max, k = 0;
	ulaz = fopen("matrica.txt", "r");
	if(ulaz == NULL){
		greska();
	}
	fscanf(ulaz, "%i", &n);
	if(n<0){
		greska();
	}
	matrica = (int**)calloc(n, sizeof(int*));
	if(matrica == NULL){
		greska();
	}


	for(int i = 0;i<n;i++){
		matrica[i] = (int*)calloc(n, sizeof(int));
		for(int j = 0;j<n;j++){
			fscanf(ulaz, "%i", &matrica[i][j]);
		}
	}

	for(int i = 0;i<n;i++){
		max = matrica[i][0];
		for(int j = 0;j<n;j++){
			if(max <= matrica[i][j]){
				max = matrica[i][j];
				k++;
			}
		}
		if(k == n){
			fprintf(stdout, "%i ", i);
		}
		k = 0;
	}
	printf("\n");

	for(int i = 0;i<n;i++){
		free(matrica[i]);
	}
	free(matrica);
	fclose(ulaz);
	return 0;
}