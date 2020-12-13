#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	if(argc != 3){
		greska();
	}

	int n, m, i = 0, j = 0, matrica[MAX][MAX], min1, max2, k = 0, signal = 0;

	n = atoi(argv[1]);
	m = atoi(argv[2]);
	if(n<1 || n>MAX || m<1 || m>MAX){
		greska();
	}

	for(i = 0;i<n;i++){
		for(j = 0;j<m;j++){
			fscanf(stdin, "%i", &matrica[i][j]);
		}
	}

	for(i = 0;i<n;i++){
		k = 0;
		min1 = matrica[i][0];
		for(j = 0;j<m;j++){
			if(min1>matrica[i][j]){
				min1 = matrica[i][j];
				k = j;
			}
		}
		max2 = matrica[i][k];
		for(int l = 0;l<n;l++){
			if(max2<matrica[l][k]){
				signal++;
			}
		}
		if(!signal){
			fprintf(stdout, "%i %i %i\n", i, k, matrica[i][k]);
		}
		signal = 0;
	}


	return 0;
}