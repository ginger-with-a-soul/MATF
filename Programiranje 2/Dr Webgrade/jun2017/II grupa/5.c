#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"


void error();

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int br)
{
	Cvor* n = malloc(sizeof(Cvor));
	
	if (n == NULL)
		error();
	
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

int odd_son(Cvor* koren);

int odd_son(Cvor* koren){
	if(koren == NULL){
		return 0;
	}

	int count = 0;
	if(koren->levo != NULL && koren->levo->vrednost % 2 == 1){
		if(koren->desno != NULL){
			if(koren->desno->vrednost % 2 == 1){
				count = 0 + odd_son(koren->levo);
			}
			else{
				count = 1 + odd_son(koren->levo);
			}
		}
		else{
			count = 1 + odd_son(koren->levo);
		}
		return count;
	}
	if(koren->desno != NULL && koren->desno->vrednost % 2 == 1){
		if(koren->levo != NULL){
			if(koren->levo->vrednost % 2 == 1){
				count = 0 + odd_son(koren->desno);
			}
			else{
				count = 1 + odd_son(koren->desno);
			}
		}
		else{
			count = 1 + odd_son(koren->desno);
		}
		return count;
	}
	else return odd_son(koren->levo) + odd_son(koren->desno);

}

int main(){

	FILE *input;
	Cvor *koren = NULL;

	input = fopen("stablo.txt", "r");
	if(input == NULL){
		error();
	}

	koren = napravi_stablo_iz_fajla(input);

	printf("%i\n", odd_son(koren));

	oslobodi(koren);
	fclose(input);
	return 0;
}