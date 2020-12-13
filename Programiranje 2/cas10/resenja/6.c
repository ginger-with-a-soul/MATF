#include<stdio.h>
#include<stdlib.h>

#include"liste.h"

void ubaci_minus_1(Cvor* lista, int k)
{
    if(lista == NULL || lista->sledeci==NULL)
        return;
        
    //Provera da li izmedju trenutnog i sledeceg treba ubaciti -1:
    if(lista->vrednost + lista->sledeci->vrednost == k || abs(lista->vrednost - lista->sledeci->vrednost) == k)
    {
        Cvor* novi = napravi_cvor(-1);
        novi->sledeci = lista->sledeci;
        lista->sledeci = novi;
        ubaci_minus_1(novi->sledeci, k);
    }
    else 
        ubaci_minus_1(lista->sledeci, k);
}

int main(int argc, char* argv[])
{
    int broj;
    //Obavezna inicijalizacija liste na NULL!
    Cvor* lista = NULL;

    //Ucitavanje elemenata
    while(1){
        scanf("%d", &broj);
        if(broj == 0)
            break;
            
        dodaj_na_kraj(&lista, broj);
    }

    //Ucitavanje broja k
    int k;
    scanf("%d", &k);

    //Poziv funkcije
    ubaci_minus_1(lista, k);
    
    //Ispis rezultata
    ispisi_listu(lista);
    
    //Oslobadjanje memorije
    oslobodi_listu(lista);
    
    return 0;
}