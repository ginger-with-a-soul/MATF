#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

void greska()
{
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int broj)
{
    Cvor* novi = malloc(sizeof(Cvor));
    if(novi == NULL)
            greska();
            
    novi->vrednost = broj;
    novi->levo = NULL;
    novi->desno = NULL;
    
    return novi;
}

void dodaj_u_stablo(Cvor** koren, int broj)
{
    if(*koren == NULL)
    {
            *koren = napravi_cvor(broj);
            return;
    }
    
    if(broj < (*koren)->vrednost)
            dodaj_u_stablo(&(*koren)->levo, broj);
    else
            dodaj_u_stablo(&(*koren)->desno, broj);
}

void ucitaj_stablo(Cvor** koren, FILE* ulaz)
{
    int broj;	
    while(fscanf(ulaz, "%d", &broj) != EOF)
            dodaj_u_stablo(koren, broj);
            
}

void ispisi_stablo(Cvor* koren, FILE* f)
{
    if(koren != NULL)
    {
            ispisi_stablo(koren->levo, f);
            printf("%d ", koren->vrednost);
            ispisi_stablo(koren->desno, f);
    }
}

void oslobodi_stablo(Cvor* koren){
    if(koren)
    {
            oslobodi_stablo(koren->levo);
            oslobodi_stablo(koren->desno);
            free(koren);
    }
}

int suma_poslednjih(Cvor* koren);

int suma_poslednjih(Cvor* koren){
	if(koren == NULL){
		return 0;
	}

	if(koren->levo == NULL && koren->desno == NULL){
		return koren->vrednost;
	}
	else{
		return suma_poslednjih(koren->levo) + suma_poslednjih(koren->desno);
	}
}

int main(){

	FILE *input;
	Cvor* koren = NULL;

	input = fopen("stablo.txt", "r");
	if(input == NULL){
		greska();
	}

	ucitaj_stablo(&koren, input);

	printf("%i\n", suma_poslednjih(koren));

	oslobodi_stablo(koren);
	fclose(input);
	return 0;
}