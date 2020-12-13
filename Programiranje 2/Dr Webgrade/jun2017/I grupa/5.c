#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

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

int prebroj(Cvor* koren);

int prebroj(Cvor* koren){
	if(koren == NULL){
		return 0;
	}
	if(koren->vrednost < 0){
		greska();
	}

	if(koren->vrednost % 2 == 0){
		int count = 0;
		if(koren->levo != NULL){
			count = 1 + prebroj(koren->levo);
		}
		if(koren->desno != NULL){
			count = count + 1 + prebroj(koren->desno);
		}
		return count;
	}
	else{
		return prebroj(koren->levo) + prebroj(koren->desno);
	}
}

int main(){

	FILE *input;
	Cvor *koren = NULL;
	int count;

	input = fopen("stablo.txt", "r");
	if(input == NULL){
		greska();
	}

	koren = napravi_stablo_iz_fajla(input);

	printf("%i\n", prebroj(koren));

	oslobodi(koren);
	fclose(input);
	return 0;
}