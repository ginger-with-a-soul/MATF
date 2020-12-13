#include <stdio.h>
#include <stdlib.h>

void greska();
int pretraga(const void* x, const void* niz);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int pretraga(const void* x, const void* niz){
	return *(int*)x - *(int*)niz;
}

int main(){
	int x, n, *niz, max = 0, *binarno;
	scanf("%i %i", &x, &n);
	if(n<1){
		greska();
	}

	niz = (int*)calloc(n, sizeof(int));
	if(niz == NULL){
		greska();
	}
	for(int i = 0;i<n;i++){
		scanf("%i", &niz[i]);
		if(max<=niz[i]){
			max = niz[i];
		}
		else{
			greska();
		}
	}
	binarno = bsearch(&x, niz, n, sizeof(int), &pretraga);
	if(bsearch == NULL){
		printf("Nema tog broja!\n");
	}
	else{
		fprintf(stdout, "%ld\n", binarno - niz);
	}

	free(niz);
	return 0;
}