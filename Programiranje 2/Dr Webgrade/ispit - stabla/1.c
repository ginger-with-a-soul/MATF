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

	input = fopen("stablo.txt", "r");
	if(input == NULL){
		greska();
	}

	ucitaj_stablo(&koren, input);

	printf("%i\n", prebroj(koren));


	oslobodi_stablo(koren);
	fclose(input);
	return 0;
}