#include<stdio.h>
#include "liste.h"

int veci_od(Cvor* lista, int x)
{
    if(lista == NULL)
        return 0;
    
    if(lista->vrednost > x)
        return 1 + veci_od(lista->sledeci, x);
    else
        return veci_od(lista->sledeci, x);
    
}

int main(int argc, char* argv[])
{
    if(argc != 2)
        greska();
    
    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL)
        greska();
    
    //Inicijalizujemo praznu listu
    Cvor* l = NULL;
    
    //Ucitavamo listu iz fajla
    ucitaj_listu(&l, ulaz);
    
    //Ucitavamo broj x
    int x;
    scanf("%d", &x);
    
    //Ispisujemo koliko clanova liste je vece od x
    printf("%d\n", veci_od(l, x));
    
    //Oslobadjamo listu
    oslobodi_listu(l);
    
    return 0;
}