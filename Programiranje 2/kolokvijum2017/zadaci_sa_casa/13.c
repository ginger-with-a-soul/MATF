#include <stdio.h>
#include <stdlib.h>

void greska();
int pretraga(const void* x, const void* y);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int pretraga(const void* x, const void* y){
	int k, niz, count = 0, razlika;
	k = *(int*)x;
	niz = *(int*)y;
	while(niz){
		count++;
		niz /= 10;
	}
	razlika = k - count;
	count = 0;
	return razlika;
}

int main(){
	int k, n, *niz, *binarna_pretraga;

	fscanf(stdin, "%i %i", &k, &n);
	if(k<1 || n<1){
		greska();
	}

	niz = (int*)calloc(n, sizeof(int));
	if(niz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%i", &niz[i]);
	}

	binarna_pretraga = bsearch(&k, niz, n, sizeof(int), &pretraga);
	if(binarna_pretraga == NULL){
		exit(EXIT_SUCCESS);
	}
	else{
		fprintf(stdout, "%li\n", binarna_pretraga - niz);
	}

	free(niz);
	return 0;
}