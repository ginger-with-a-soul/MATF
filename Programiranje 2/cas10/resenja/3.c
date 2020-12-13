#include<stdio.h>

#include"liste.h"

Cvor* spoji_liste(Cvor* l1, Cvor* l2)
{
	/*
	Ako je neka od listi prazna, rezultat je ona druga lista
	(ako su obe prazne, rezultat je NULL)
	*/
	if(l1 == NULL)
		return l2;
	if(l2 == NULL)
		return l1;
		
	/*
	Glava rezultujuce liste odgovara:
	-glavi l1, ako je l1->vrednost < l2->vrednost
	-glavi l2 u suprotnom
	*/
	Cvor* nova_glava;	
	if(l1->vrednost < l2->vrednost)
	{
		nova_glava = l1;
		l1 = l1->sledeci;
	}
	else
	{
		nova_glava = l2;
		l2 = l2->sledeci;
	}
	/*
	Promenljiva nova_glava, nam treba da bismo je vratili kao povratnu vrednost, 
	iz tog razloga deklarisemo jedan pomocni cvor koji ce da se "seta" i da prevezuje
	pokazivace tako da rezultujuca lista bude sortirana, a da ne napravimo ni jedan 
	novi cvor
	*/
	Cvor* tekuci = nova_glava;
	while(l1 != NULL && l2 != NULL)
	{
		if(l1->vrednost < l2->vrednost)
		{
			tekuci->sledeci = l1;
			l1 = l1->sledeci;
		}else{
			tekuci->sledeci = l2;
			l2 = l2->sledeci;
		}	
		tekuci = tekuci->sledeci;
	}
	
	/*Ako je nesto preostalo u prvoj listi, samo ga nadovezujemo na tekuci rezultat*/
	if(l1)
		tekuci->sledeci = l1;
	
	/*Ako je nesto preostalo u drugoj listi, samo ga nadovezujemo na tekuci rezultat*/
	if(l2)
		tekuci->sledeci = l2;
	
	/*Vracamo glavu rezultujuce liste*/
	return nova_glava;
}

int main(int argc, char* argv[])
{

    if(argc != 3)
        greska();
        
    FILE* dat1 = fopen(argv[1], "r");
    if(dat1 == NULL)
        greska();
        
    FILE* dat2 = fopen(argv[2], "r");
    if(dat2 == NULL)
        greska();

    Cvor* l1 = NULL, *l2 = NULL;

    ucitaj_listu(&l1, dat1);
    ucitaj_listu(&l2, dat2);
	
    Cvor* tekuci = spoji_liste(l1, l2);

    ispisi_listu(tekuci);
      
    /*
    NAPOMENA:
    Oslobadjamo salo tekuci iz razloga sto se u toj listi nalaze svi cvorovi koji su inicijalno bili u l1 i l2. 
    Ako napisemo:
    oslobodi(&l1);
    oslobodi(&l2);
    oslobodi(&tekuci);
    Pokusacemo dva puta da oslobadjamo istu memoriju, sto nije ispravno!
    */
    oslobodi_listu(tekuci);

    fclose(dat1);
    fclose(dat2);
    return 0;
}