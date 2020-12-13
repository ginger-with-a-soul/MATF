#include<stdio.h>
#include<stdlib.h>

typedef struct {
  int br;
  int im;
} RAZLOMAK;

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}


int main(){

  int i, n;
  RAZLOMAK* niz;

  //Ucitavamo dimenziju niza
  scanf("%d", &n);
  if(n <= 0)
    greska();
  
  //Alociramo prostor za n razlomaka
  niz = malloc(n*sizeof(RAZLOMAK));
  if(niz == NULL)
    greska();
  
  //Ucitavamo elemente i racunamo prosecnu vrednost
  float suma = 0;
  for(i=0; i<n; i++)
  {
    scanf("%d%d", &niz[i].br, &niz[i].im);
    if(niz[i].im == 0)
      greska();
    
    suma += (float)niz[i].br/niz[i].im;
  }
  float prosek = suma/n;
  
  //Ispisujemo rezultat
  for(i=0; i<n; i++)
    if((float)niz[i].br/niz[i].im > prosek)
      printf("%d/%d ", niz[i].br, niz[i].im);
  printf("\n");
  
  //Oslobadjamo prethodno alocirani niz
  free(niz);
  
  return 0;

}
