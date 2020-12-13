#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

int main(){

	int n, m, k, s, x, hornerova_shema; 
	int *a, *b, *c;

	a = unos(&n);

	ispis_polinoma(a, n);

	b = unos(&m);

	c = suma_polinoma(a, n, b, m, &k);

	ispis_polinoma(c, k);

	mnoz_skalarom(a, n, s);

	ispis_polinoma(a, n);

	hornerova_shema = vr_poly(a, n, x);

	c = mul_poly(a, n, b, m, &k);

	ispis_polinoma(c, k);

	free(a);
	free(b);
	free(c);

	return 0;
}