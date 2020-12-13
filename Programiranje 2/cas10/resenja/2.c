#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void obrisi_cvor_iterativno(Cvor** lista, int broj)
{
  if(*lista == NULL)
    return;
  
  //Brisanje cvorova sa pocetka liste
  while(*lista != NULL && (*lista)->vrednost == broj)
  {
    Cvor* tmp = *lista;
    *lista = (*lista)->sledeci;
    free(tmp);
  }
  
  //Ako je lista postala prazna, izlazimo
  if(*lista == NULL)
	return;
  
  //Brisanje cvorova iz ostatka liste
  Cvor* tr = *lista;
  while(tr->sledeci)
  {
    //brise se sledeci element
    if(tr->sledeci->vrednost == broj)
    {
      Cvor* tmp = tr->sledeci;
      tr->sledeci = tr->sledeci->sledeci;
      free(tmp);
    }
    else
      tr = tr->sledeci;
  }
}

void obrisi_cvor(Cvor** lista, int broj)
{
  if(*lista == NULL)
    return;
  else if((*lista)->vrednost == broj)
  {
    Cvor* tmp = *lista;
    *lista = (*lista)->sledeci;
    free(tmp);
    obrisi_cvor(lista, broj);
  }
  else
    obrisi_cvor(&(*lista)->sledeci, broj);
}

int main()
{
  int x;

  //Inicijalizujemo praznu listu (OVO NIJE OPCIONO!)
  Cvor* lista = NULL;

  //Dodajemo ucitane elemente na pocetak liste
  int i;
  while(1)
  {
    scanf("%d", &x);
    if(x == 0)
      break;
    
    dodaj_na_kraj(&lista, x);
  }
  
  //Ucitavamo element koji se brise
  scanf("%d", &x);
  
  //Brisemo sve cvorove koji imaju tu vrednost
  obrisi_cvor(&lista, x);
  //obrisi_cvor_iterativno(&lista, x);

  //Ispisujemo rezultujucu listu
  ispisi_listu(lista);
  
  //Oslobadjamo memoriju
  oslobodi_listu(lista);
  return 0;
}