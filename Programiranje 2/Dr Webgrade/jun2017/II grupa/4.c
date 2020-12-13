#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void greska(){
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int broj)
{
  Cvor* novi = malloc(sizeof(Cvor*));
  if(novi == NULL)
    greska();
  
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

void error();
Cvor* ukloni(Cvor* lista);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

Cvor* ukloni(Cvor* lista){
	if(lista == NULL){
		return NULL;
	}
	if(lista->sledeci == NULL){
		return lista;
	}

	if(lista->vrednost + lista->sledeci->vrednost == 0){
		Cvor* tmp = lista;
		lista = lista->sledeci;
		free(tmp);
		lista = ukloni(lista);
	}
	else{
		lista->sledeci = ukloni(lista->sledeci);
	}
}

int main(){

	FILE *input;
	Cvor *lista = NULL;
	input = fopen("lista.txt", "r");
	if(input == NULL){
		error();
	}

	lista = napravi_listu_iz_fajla(input);

	lista = ukloni(lista);

	ispisi(lista);
	oslobodi(&lista);
	fclose(input);
	return 0;
}