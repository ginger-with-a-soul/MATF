#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int* unos(int* n){
	printf("Unesi najveci stepen polinoma: ");
	scanf("%i", n);
	if(*n<1){
		greska();
	}

	int i = 0, *a;
	a = (int*)calloc((*n)+1, sizeof(int));
	if(a == NULL){
		greska();
	}
	printf("Ucitaj koeficijente polinoma: ");
	for(i = 0;i<=*n;i++){
		scanf("%i", &a[i]);
	}

	return a;
}

void ispis_polinoma(int* a, int n){

	for(int i = 0;i<=n;i++){
		if(i == 0 && a[0] != 0){
			printf("%i ", a[0]);
		}
		else if(i>1 && a[i] != 0){
			printf("%i*x^%i ", a[i], i);
		}
		else if(i == 1 && a[1] != 0){
			printf("%i*x ", a[1]);
		}
		if(i<n && a[i+1]>0){
			printf("+ ");
		}

	}
	printf("\n");

}

int* suma_polinoma(int* a, int n, int* b, int m, int* k){
	int* c;
	(*k) = n;
	if(m>n){
		(*k) = m;
	}
	c = (int*)calloc((*k)+1, sizeof(int));
	if(c == NULL){
		greska();
	}

	for(int i = 0;i<=*k;i++){
		if(i<=n && i<=m){
			c[i] = a[i] + b[i];
		}
		else if(i<=n){
			c[i] = a[i];
		}
		else{
			c[i] = b[i];
		}
	}

	return c;
}

void mnoz_skalarom(int *a, int n, int s){

	printf("Unesi skalar za mnozenje: ");
	scanf("%i", &s);

	for(int i = 0;i<=n;i++){
		a[i] *= s;
	}
	if(s == 0){
		printf("0");
	}
}

int vr_poly(int* a, int n, int x){

	printf("Unesi vrednost za neku tacku: ");
	scanf("%i", &x);
	int s = 0;

	for(int i = n;i>=0;i--){
		s = s*x + a[i];
	}

	printf("%i\n", s);

	return s;
}

int* mul_poly(int *a, int n, int* b, int m, int* k){
	int *c;
	c = (int*)calloc((*k)+1, sizeof(int));
	if(c == NULL){
		greska();
	}

	for(int i = 0;i<=n;i++){
		for(int j = 0;j<=m;j++){
			c[i+j] += a[i] * b[j];
		}
	}

	printf("Proizvod polinoma:\n");

	return c;
}