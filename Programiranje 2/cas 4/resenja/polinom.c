#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

void greska()
{
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void unos_polinoma(int a[], int n)
{
   int i;
      printf("Ucitaj polinom:\n");
      for(i=0; i<=n; i++)
	 scanf("%d", &a[i]);
}

void ispis_polinoma(int a[], int n)
{
  int i;
    for(i=0; i<=n; i++)
    {
      if (i==0) printf("%d ", a[i]);
      else if (i==1) printf("%d*x ", a[i]);
	else printf("%d*x^%d ", a[i], i);
      if (i!=n) printf("+");
    }
    printf("\n");
}

int suma_polinoma(int a[], int n, int b[], int m, int c[])
{
  int i=0;
  
  
  while(i<=n && i<=m)
  {
    c[i] = a[i] + b[i];
    i++;
  }
  
  while(i<=n)
  {
    c[i] = a[i];
    i++;
  }
  
  while(i<=m)
  {
    c[i]=b[i];
    i++;
  } 
    
  if (n > m) return n;
  else return m;
}

void mnoz_skalarom(int a[], int n, int c)
{
  int i;
  for(i=0; i<=n; i++)
    a[i] = c*a[i];
}

int vr_poly(int a[], int n, int x)
{
  int s=0, i;
  
    for(i=n; i>=0; i--)
      s = s*x + a[i];
    
    return s;
 
}

int mul_poly(int a[], int n, int b[], int m, int c[])
{
  int i,j;
    for(i=0; i<=m+n; i++)
      c[i] = 0;
  
    for(i=0; i<=n; i++)
      for(j=0; j<=m; j++)
				c[i+j] += a[i]*b[j];
      
    return m+n;
}









