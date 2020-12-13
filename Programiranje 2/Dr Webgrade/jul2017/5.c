#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int br)
{
	Cvor* n = malloc(sizeof(Cvor));
	
	if (n == NULL)
		greska();
	
	n->vrednost = br;
	n->levo = NULL;
	n->desno = NULL;
	
	return n;
}

void dodaj_u_stablo(Cvor** koren, int br)
{
	if (*koren == NULL){
		*koren = napravi_cvor(br);
		return;
	}
	if (br > (*koren)->vrednost)
		dodaj_u_stablo(&(*koren)->desno, br);
	else
		dodaj_u_stablo(&(*koren)->levo, br);
}

Cvor* dodaj_u_stablo_v2(Cvor* koren, int br)
{
	if (koren == NULL)
		return napravi_cvor(br);
	
	if (br > koren->vrednost)
		koren->desno = dodaj_u_stablo_v2(koren->desno, br);
	else
		koren->levo = dodaj_u_stablo_v2(koren->levo, br);
	
	return koren;
}

void ispisi_u_fajl(Cvor* koren, FILE* f)
{
	if (koren != NULL)
	{
		ispisi_u_fajl(koren->levo, f);
		fprintf(f, "%d ", koren->vrednost);
		ispisi_u_fajl(koren->desno, f);
	}
}

void oslobodi(Cvor* koren)
{
	if (koren != NULL)
	{
		oslobodi(koren->levo);
		oslobodi(koren->desno);
		free(koren);
	}
}

Cvor* napravi_stablo_iz_fajla(FILE* f)
{
	Cvor* koren = NULL;
	int br;
	
	while(fscanf(f, "%d", &br) != EOF)
	{
		dodaj_u_stablo(&koren, br);
	}
	
	return koren;
}

int even_level_multiplied(Cvor *koren, unsigned level);

int even_level_multiplied(Cvor *koren, unsigned level){
	if(koren == NULL){
		return 1;
	}

	if(level % 2 == 0){
		return koren->vrednost * even_level_multiplied(koren->levo, level + 1) * even_level_multiplied(koren->desno, level + 1);
	}
	else{
		return even_level_multiplied(koren->levo, level + 1) * even_level_multiplied(koren->desno, level + 1);
	}
}

int main(){

	FILE *input;
	Cvor *koren = NULL;
	unsigned level = 0;

	input = fopen("stablo.txt", "r");
	if(input == NULL){
		greska();
	}

	koren = napravi_stablo_iz_fajla(input);

	if(koren == NULL){
		fprintf(stdout, "0\n");
	}
	else{
		fprintf(stdout, "%i\n", even_level_multiplied(koren, level));
	}

	oslobodi(koren);
	fclose(input);
	return 0;
}