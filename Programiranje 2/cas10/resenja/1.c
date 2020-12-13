#include <stdio.h>
#include "liste.h"

int main()
{
  int n;
  int x;

  //Ucitavamo broj elemenata liste
  scanf("%d", &n);
  if(n <= 0)
          greska();

  //Inicijalizujemo praznu listu (OVO NIJE OPCIONO!)
  Cvor* lista = NULL;

  //Dodajemo ucitane elemente na pocetak liste
  int i;
  for(i=0; i<n; i++)
  {
    scanf("%d", &x);
    dodaj_na_pocetak(&lista, x);
  }
  
  //Ispisujemo dobijenu listu
  ispisi_listu(lista);

  //Inicijalizujemo drugu praznu listu
  Cvor* lista2 = NULL;
  
  //Ucitavamo njene elemente sa standardnog ulaza
  ucitaj_listu(&lista2, stdin);
  
  //Ispisujemo sadrzaj liste
  ispisi_listu(lista2);
  
  //Oslobadjamo memoriju za obe liste
  oslobodi_listu(lista);
  oslobodi_listu(lista2);
  return 0;
}
