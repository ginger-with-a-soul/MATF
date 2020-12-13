#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_REC 21

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }

/* Funkcija koja binarnom pretragom pronalazi rec u nizu reci*/
int binarna_rekurzivno(char** niz, int l, int d, char* trazena)
{
	if(l > d)
		return -1;
		
	int s = l + (d-l)/2; //ILI (l+d)/2
	int rez = strcmp(niz[s], trazena);
	
	if(rez == 0)
		return s;
	else if(rez > 0)
		return binarna_rekurzivno(niz, l, s-1, trazena);
	else
		return binarna_rekurzivno(niz, s+1, d, trazena);
}

/*Funkcija poredjenja za bsearch za pretragu jedne reci u nizu reci*/
int poredi(const void* a, const void *b)
{
	return strcmp((char*)a, *(char**)b);
}

int main()
{

char **reci;
char trazena[MAX_REC];

//Ucitavamo broj reci
int n;
scanf("%d", &n);

//Alociramo prostor i ucitavamo reci
reci = malloc(n*sizeof(char*));
if(reci == NULL)
	greska();
int i;
for(i=0; i<n; i++){
	reci[i] = malloc(MAX_REC);
	if(reci[i] == NULL)
		greska();
	scanf("%s", reci[i]);
}

//Ucitavamo trazenu rec
scanf("%s", trazena);

//Koriscenjem funkcije bsearch trazimo trazenu rec u nizu reci
char **p = bsearch(trazena, reci, n, sizeof(char*), poredi);
if(p == NULL)
	printf("BSEARCH: Nema!\n");
else
	printf("BSEARCH: %ld\n", p-reci);

//Koriscenjem nase funkcije trazimo trazenu rec u nizu reci	
int poz = binarna_rekurzivno(reci, 0, n-1, trazena);
printf("NASA: %d\n", poz);	

//Oslobadjenje niza reci
for(i=0; i<n; i++)
	free(reci[i]);
free(reci);
	
return 0;
}