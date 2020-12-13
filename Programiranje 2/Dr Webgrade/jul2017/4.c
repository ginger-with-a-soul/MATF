#include <stdio.h>
#include <stdlib.h>

typedef struct _cvor
{
  int vrednost;
  struct _cvor* sledeci;
}Cvor;

void error();
void suma(Cvor *lista, int sum);
Cvor* izmeni(Cvor *lista, int sum);

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

void suma(Cvor *lista, int sum){
	while(lista){
		sum += lista->vrednost;
		suma(lista->sledeci, sum);
	}
}

Cvor* izmeni(Cvor *lista, int sum){
	if(lista == NULL){
		return NULL;
	}
	sum -= lista->vrednost;
	if(lista->sledeci != NULL && lista->vrednost > sum){
		Cvor *tmp = lista;
		lista = lista->sledeci;
		free(tmp);
		return izmeni(lista, sum);
	}
	else{
		lista->sledeci = izmeni(lista->sledeci, sum);
		return lista;
	}
}

int main(){

	Cvor *lista = NULL;
	int sum = 0;

	lista = napravi_listu_iz_fajla(stdin);

	suma(lista, sum);

	lista = izmeni(lista, sum);

	ispisi(lista);
	oslobodi(&lista);
	return 0;
}