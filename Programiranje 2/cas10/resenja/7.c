#include<stdio.h>
#include<stdlib.h>

#include"liste.h"

void izbaci_susedne(Cvor** lista, int k)
{
    if(*lista == NULL || (*lista)->sledeci == NULL)
        return;

    Cvor* tr = *lista;
    /*Ako je zbir trenutnog i sledeceg jednak k,
    treba izbaciti oba elementa, ali vodeci racuna o tome 
    da sledeci moze da ucestvuje u zbiru sa svojim sledecim.
    Iz tog razloga radimo sledece:
    1. U pomocnu promenljivu zapamtimo sledeci cvor
    2. Pozovemo rekurzivno funkciju za ostatak liste
    3. Po povratku iz rekurzije:
            -ako je sledeci cvor i dalje jednak
            zapamcenom cvoru, znaci da on nije izbacen u toku rekuzije,
            i da treba izbaciti i njega i trenutni cvor
            -ako nije, znaci da je u toku rekurzije izbacen i da je
            potrebno izbaciti samo trenutni
        Primer:
        1 4 5 4 6 3   k=9
        f(1 4 5 4 6 3) 
            f(1| 4 5 4 6 3)
                f(1 4 |5 4 6 3)
                    f(1 4 5 |4 6 3)
                        f(1 4 5 4 | 6 3)
                            f(1 4 5 4 6 |3) -->sledeci je NULL, izlazimo
                        trenutni = 6, sledeci=3 i sledeci se nije promenio, brisu se oba: (1 4 5 4)
                    trenutni = 4 (uslo se u else granu, nema nikakvog izracunavanja nakon rek poziva)
                trenutni = 5 sledeci =4 i sledeci se nije promenio, brisemo i 5 i 4 (1 4)
            trenutni = 4, sledeci = NULL i sledeci se promenio (zapamceni sledeci je 5), brisemo samo 4 (1)
        trenutni = 1 (uslo se u else granu, nema izracunavanja) 
    */
    if(tr->vrednost + tr->sledeci->vrednost == k)
    {
        Cvor* sledeci_cvor = tr->sledeci;
        izbaci_susedne(&tr->sledeci, k);
        
        if(tr->sledeci == sledeci_cvor)
        {
            *lista = tr->sledeci->sledeci;
            free(tr->sledeci);
            free(tr);
        }
        else{
            *lista = (*lista)->sledeci;
            free(tr);
        }
    }
    else
        izbaci_susedne(&tr->sledeci, k);
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

    //Ucitavanje broja k
    int k;
    scanf("%d", &k);

    //Poziv funkcije
    izbaci_susedne(&lista, k);
    
    //Ispis rezultata
    ispisi_listu(lista);
    
    //Oslobadjanje memorije
    oslobodi_listu(lista);
    return 0;
}