#include <stdio.h>
#include <stdlib.h>

void greska();
int linearno(int *niz, int n, int x);
int moj_nacin_poredjenja(const void* x, const void* niz);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int linearno(int *niz, int n, int x){
	for(int i = 0;i<n;i++){
		if(x == niz[i]){
			return i;
		}
	}
	return -1;
}

int moj_nacin_poredjenja(const void* x, const void* niz){
	return *(int*)x - *(int*)niz;
}

int main(){
	int n, *niz, max, x, *binarno;
	scanf("%i", &n);
	if(n<1){
		greska();
	}
	niz = (int*)calloc(n, sizeof(int));
	if(niz == NULL){
		greska();
	}
	scanf("%i", &niz[0]);
	max = niz[0];
	for(int i = 1;i<n;i++){
		scanf("%i", &niz[i]);
		if(niz[i]<=max){
			greska();
		}
		max = niz[i];
	}

	scanf("%i", &x);

	printf("%i\n", linearno(niz, n, x));
	binarno = bsearch(&x, niz, n, sizeof(int), &moj_nacin_poredjenja);
	if(binarno == NULL){
		printf("-1\n");
	}
	else{
		printf("%ld\n", binarno - niz);
	}

	free(niz);
	return 0;
}