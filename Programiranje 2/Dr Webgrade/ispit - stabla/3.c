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

int proizvod_na_parnim(Cvor* koren, int nivo);

int proizvod_na_parnim(Cvor* koren, int nivo){
	if(koren == NULL){
		return 1;
	}
	if(nivo % 2 == 0){
		return koren->vrednost * proizvod_na_parnim(koren->levo, nivo + 1) * proizvod_na_parnim(koren->desno, nivo + 1);
	}
	else{
		return proizvod_na_parnim(koren->levo, nivo + 1) * proizvod_na_parnim(koren->desno, nivo + 1);
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
	if(koren == NULL){
		printf("0\n");
		return 0;
	}

	printf("%i\n", proizvod_na_parnim(koren, 0));

	oslobodi_stablo(koren);
	fclose(input);
	return 0;
}