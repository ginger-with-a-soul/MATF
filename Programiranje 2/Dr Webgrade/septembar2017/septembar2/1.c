#include <stdio.h>
#include <stdlib.h>

void error();

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	int strogo_rastuci = 1, strogo_opadajuci = 1, svi_jednaki = 1, sum = 0, mul = 1;

	if(argc == 1){
		error();
	}

	int *niz = (int*)calloc(argc-1, sizeof(int));
	if(niz == NULL){
		error();
	}

	for(int i = 0, j = 1; i < argc - 2; i++, j++){
		niz[i] = atoi(argv[i + 1]);
		niz[j] = atoi(argv[j + 1]);

		if(!(niz[i] < niz[j])){
			strogo_rastuci = 0;
		}
		if(!(niz[i] == niz[j])){
			svi_jednaki = 0;
		}
		if(!(niz[i] > niz[j])){
			strogo_opadajuci = 0;
		}
		if(i == 0){
			sum += niz[i] + niz[j];
			mul *= niz[i] * niz[j];
			continue;
		}
		sum += niz[j];
		mul *= niz[j];
	}

	if(strogo_rastuci){
		fprintf(stdout, "%i\n", sum);
	}
	else if(strogo_opadajuci){
		fprintf(stdout, "%i\n", mul);
	}
	else if(svi_jednaki){
		fprintf(stdout, "0\n");
	}
	else{
		fprintf(stdout, "-\n");
	}

	free(niz);
	return 0;
}