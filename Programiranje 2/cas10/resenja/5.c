#include<stdio.h>
#include<stdlib.h>

#include"liste.h"

void obrisi(Cvor** lista, int suma_prethodnih)
{
    if(*lista == NULL)
      return;
    
    //Pamtimo trenutni cvor
    Cvor* tr = *lista;

    /*
    Ako je njegova vrednost manja od sume prethodnih, 
    brisemo trenutni cvor i rekurzivno proveravamo ostatak
    Ako nije, samo rekurzivno proveravamo ostatak
    */
    if(tr->vrednost < suma_prethodnih)
    {
      *lista = (*lista)->sledeci;
      suma_prethodnih += tr->vrednost;
      free(tr);
      obrisi(lista, suma_prethodnih);
    }
    else obrisi(&tr->sledeci, suma_prethodnih + tr->vrednost);
}

int main(int argc, char* argv[])
{
    //Obavezna inicijalizacija liste na NULL!
    Cvor* lista = NULL;

    //Ucitavanje elemenata liste
    int broj;	
    while(1){
        scanf("%d", &broj);
        if(broj == 0)
            break;
            
        dodaj_na_kraj(&lista, broj);
    }

    //Poziv trazene funkcije
    obrisi(&lista, 0);
    
    //Ispis rezultata
    ispisi_listu(lista);
    
    //Osobadjanje memorije
    oslobodi_listu(lista);
    
    return 0;
}