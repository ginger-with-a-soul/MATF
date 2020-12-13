#ifndef _STABLA_H_
#define _STABLA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cvor
{
	int vrednost;
	struct Cvor* levo;
	struct Cvor* desno;
}Cvor;

void greska();
Cvor* napravi_cvor(int br);
void dodaj_u_stablo(Cvor** koren, int br);
Cvor* dodaj_u_stablo_v2(Cvor* koren, int br);
void ispisi_u_fajl(Cvor* koren, FILE* f);
void oslobodi(Cvor* koren);
Cvor* napravi_stablo_iz_fajla(FILE* f);

#endif


