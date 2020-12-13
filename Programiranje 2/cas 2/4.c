#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int sum_max(int **v, int n, int m);
int sum_max(int **v, int n, int m){
	int suma = 0, max = 0, i = 0, j = 0;
	for(i = 0;i<n;i++){
		for(j = 0;j<m;j++){
			if(v[i][j]>max){
				max = v[i][j];
			}
		}
		suma += max;
		max = 0;
	}

	return suma;
}

int main(){

	int **v, i = 0, j = 0, n, m, suma = 0;

	scanf("%i %i", &n, &m);
	if(m<1 || n<1){
		greska();
	}

	v =(int**)calloc(n, sizeof(int*));
	if(v == NULL){
		greska();
	}

	for(i = 0;i<n;i++){
		v[i] =(int*) calloc(m, sizeof(int));
		if(v[i] == NULL){
			greska();
		}
	}

	for(i = 0;i<n;i++){
		for(j = 0;j<m;j++){
			scanf("%i", &v[i][j]);
		}
	}

	for(i = 0;i<n;i++){
		for(j = 0;j<m;j++){
			printf("%i ", v[i][j]);
		}
		printf("\n");
	}

	suma = sum_max(v, n, m);

	printf("%i\n", suma);

	for(i = 0;i<n;i++){
		free(v[i]);
	}
	free(v);

	return 0;
}