#ifndef _LISTE_H_
#define _LISTE_H_

#include<stdio.h>

typedef struct _cvor
{
  int vrednost;
  struct _cvor* sledeci;
}Cvor;

Cvor* napravi_cvor(int broj);

void greska();

void dodaj_na_pocetak(Cvor** lista, int broj);

Cvor* dodaj_na_pocetak_v2(Cvor* lista, int broj);

void ispisi(Cvor* lista);

void dodaj_na_kraj(Cvor** lista, int broj);

Cvor* dodaj_na_kraj_v2(Cvor* lista, int broj);

Cvor* napravi_listu_iz_fajla(FILE* f);

void oslobodi(Cvor** lista);

#endif
