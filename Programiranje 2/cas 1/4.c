#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz;
	int matrica[MAX][MAX];
	unsigned i, j, m, n, br = 0;

	ulaz = fopen("//home//dimitrije//Desktop/cas 1//matrica.txt", "a+");
	if(ulaz == NULL){
		greska();
	}

	fscanf(ulaz, "%u %u", &n, &m);
	if(n<1 || m<1 || n>MAX ||m>MAX){
		greska();
	}

	
	for(i = 0;i<n;i++){
		for(j = 0;j<m;j++){
			fscanf(ulaz, "%i", &matrica[i][j]);
		}
	}
	int suma = 0, k, l;

	for(k = i;i<n;i++){
		for(j = 0;j<m;j++){
			if(matrica[i][j] == matrica[i-1][j-1] + matrica[i-1][j] + matrica[i-1][j+1] + matrica[i][j-1] + matrica[i][j+1] + matrica[i+1][j-1] + matrica[i+1][j] + matrica[i+1][j+1]){
				fprintf(stdout, "(%i, %i, %i)", i, j, matrica[i][j]);
			}
		}
	}

	fclose(ulaz);

	return 0;
}