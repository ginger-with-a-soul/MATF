#include <stdio.h>
#include <stdlib.h>

#include "polinom.h"

int main()
{
  int*a, *b, *c;
  int m, n, k, x, s;
  
    printf("Unesi dimenziju niza a: ");
    scanf("%d", &n);
	a = malloc(n*sizeof(int));
	if(a == NULL)
		greska();
		
    unos_polinoma(a, n);
    ispis_polinoma(a, n);
    
    printf("Unesi dimenziju niza b: ");
    scanf("%d", &m);
	b = malloc(m*sizeof(int));
	if(b == NULL)
		greska();
	
    unos_polinoma(b, m);
    
	k = n+m; //Jer cemo c koristiti i za smestanje proizvoda
	c = malloc(k*sizeof(int));
	if(c == NULL)
		greska();
		
    k = suma_polinoma(a, n, b, m, c);
    ispis_polinoma(c, k);

    printf("Unesi skalar:\n");
    scanf("%d", &s);
    mnoz_skalarom(a, n, s);
    ispis_polinoma(a,n);

    printf("Unesi x: ");
    scanf("%d", &x);
    printf("Vrednost polinoma je %d\n", vr_poly(a, n, x));

    k = mul_poly(a, n, b, m, c);
    ispis_polinoma(c, k);
  
	free(a);
	free(b);
	free(c);
  
    return 0;
}