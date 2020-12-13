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