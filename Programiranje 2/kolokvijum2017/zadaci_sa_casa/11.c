#include <stdio.h>
#include <stdlib.h>

void greska();
void f11(int* a, int n, int x);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE	);
}

void f11(int* a, int n, int x){
	if(n <= 1){
		return;
	}

	int a0, a1;
	a0 = a[0];
	a1 = a[1];

	f11(a+1, n-1, x);

	if(a0 + a1 == x){
		a[0] = 0;
		a[1] = 0;
	}

}

int main(){
	int x, n, *niz, *a;

	fscanf(stdin, "%i %i", &x, &n);
	if(n<1){
		greska();
	}

	niz = (int*)calloc(n, sizeof(int));
	if(niz == NULL){
		greska();
	}
	a = (int*)calloc(n, sizeof(int));
	if(a == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%i", &niz[i]);
	}
	for(int i = 0;i<n;i++){
		a[i] = niz[i];
	}

	f11(a, n, x);
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%i ", a[i]);
	}
	fprintf(stdout, "\n");
	free(niz);
	free(a);
	return 0;
}