#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void error();
Cvor* izbaci_fibonacija(Cvor *lista);
int fib(Cvor *lista);

Cvor* napravi_cvor(int broj)
{
  Cvor* novi = malloc(sizeof(Cvor*));
  if(novi == NULL)
    error();
  
  novi->vrednost = broj;
  novi->sledeci = NULL;
 
  return novi;
}

void dodaj_na_pocetak(Cvor** lista, int broj)
{
    Cvor* novi = napravi_cvor(broj);    
    novi->sledeci = *lista;
    *lista = novi;
}

Cvor* dodaj_na_pocetak_v2(Cvor* lista, int broj)
{
    Cvor* novi = napravi_cvor(broj);
    novi->sledeci = lista;
    return novi;
}

void ispisi(Cvor* lista)
{
  printf("[");
  while(lista != NULL)
  {
    printf("%d", lista->vrednost);
    if(lista->sledeci)
      printf(", ");
    lista = lista->sledeci;
  }
  printf("]\n");
}

void dodaj_na_kraj(Cvor** lista, int broj)
{
  if(*lista == NULL)
  {
    Cvor* novi = napravi_cvor(broj);
    *lista = novi;
    return;
  }
  
  dodaj_na_kraj(&(*lista)->sledeci, broj);
}

Cvor* dodaj_na_kraj_v2(Cvor* lista, int broj)
{
    if(lista == NULL)
        return napravi_cvor(broj);
    
    lista->sledeci = dodaj_na_kraj_v2(lista->sledeci, broj);
    return lista;
}

Cvor* napravi_listu_iz_fajla(FILE* f)
{
	Cvor* lista = NULL;
    int broj;
    while(fscanf(f,"%d",&broj) == 1)
    {        
        dodaj_na_kraj(&lista, broj);
    }
	return lista;
}

void oslobodi(Cvor** lista)
{
  if(*lista)
  {
    oslobodi(&(*lista)->sledeci);
    free(*lista);
    *lista = NULL;
  }
}



void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int fib(Cvor *lista){
	int fib1 = 1, fib2 = 1, nova = 0, vrednost = lista->vrednost;
	if(fib2 == vrednost){
		return 1;
	}
	if(!vrednost){
		return 0;
	}

	while(nova <= vrednost){
		nova = fib2 + fib1;
		fib1 = fib2;
		fib2 = nova;
	}

	if(nova == vrednost){
		return nova;
	}
	else{
		return nova;
	}
}

Cvor* izbaci_fibonacija(Cvor* lista){
	if(lista == NULL){
		return NULL;
	}

	while(lista != NULL){
		if(lista->vrednost == fib(lista)){
			Cvor* tmp = lista;
			lista = lista->sledeci;
			free(tmp);
			continue;
		}
		lista = lista->sledeci;
	}
}

int main(){

	Cvor *lista = NULL;

	lista = napravi_listu_iz_fajla(stdin);

	lista = izbaci_fibonacija(lista);

	ispisi(lista);

	oslobodi(&lista);
	return 0;
}