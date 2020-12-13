#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_REC 51

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_FAILURE);
 }

void stampaj(char** niz_reci, int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%s\n", niz_reci[i]);
}

void insertion_sort(char** niz_reci, int n)
{
	int i, j;
	char trenutna[MAX_REC];
	
	for(i=1; i<n; i++)
	{
		//cilj je trenutnu rec smestiti na njeno mesto
		//pretpostavka je da su sve reci ispred nje vec sortirane
		strcpy(trenutna, niz_reci[i]);
		for(j=i; j > 0 && strcmp(trenutna, niz_reci[j-1]) <= 0; j--)
			strcpy(niz_reci[j], niz_reci[j-1]);
		strcpy(niz_reci[j], trenutna);
	}
}

void selection_sort(char** niz_reci, int n)
{
	int i, j, poz_min;
	char privremena[MAX_REC];
	
	for(i=0; i<n; i++)
	{
		poz_min = i;
		for(j=i+1; j<n; j++)
		{
			if(strcmp(niz_reci[j], niz_reci[poz_min]) < 0)
				poz_min = j;
		}
		
		strcpy(privremena, niz_reci[i]);
		strcpy(niz_reci[i], niz_reci[poz_min]);
		strcpy(niz_reci[poz_min], privremena);
	}
}

void selection_sort_rev(char** niz_reci, int n)
{
	int i, j, poz_max;
	char privremena[MAX_REC];
	
	for(i=0; i<n; i++)
	{
		poz_max = i;
		for(j=i+1; j<n; j++)
		{
			int d1 = strlen(niz_reci[j]);
			int d2 = strlen(niz_reci[poz_max]);
			if(d1 > d2 || (d1 == d2 && strcmp(niz_reci[j], niz_reci[poz_max]) < 0))
				poz_max = j;
		}
		
		strcpy(privremena, niz_reci[i]);
		strcpy(niz_reci[i], niz_reci[poz_max]);
		strcpy(niz_reci[poz_max], privremena);
	}
}

int provera_uslova(char* s1, char* s2)
{
	int d1 = strlen(s1);
	int d2 = strlen(s2);
	if(d1 > d2 || (d1 == d2 && strcmp(s1, s2) < 0))
		return 1;
	else
		return 0;
		
	//Ili krace return d1 > d2 || (d1 == d2 && strcmp(s1, s2) < 0);
}

void insertion_sort_rev(char** niz_reci, int n)
{
	int i, j;
	char trenutna[MAX_REC];
	
	for(i=1; i<n; i++)
	{
		strcpy(trenutna, niz_reci[i]);
		for(j=i; j > 0 && provera_uslova(trenutna, niz_reci[j-1]) > 0; j--)
			strcpy(niz_reci[j], niz_reci[j-1]);
		strcpy(niz_reci[j], trenutna);
	}
}

int main(int argc, char* argv[])
{
	if(argc != 2)
		greska();
		
	char **reci;

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

	if(strcmp(argv[1], "-i") == 0)
		insertion_sort(reci,n);
	else if(strcmp(argv[1], "-s") == 0)
		selection_sort(reci, n);
	else if(strcmp(argv[1], "-ir") == 0)
		insertion_sort_rev(reci, n);
	else if(strcmp(argv[1], "-sr") == 0)
		selection_sort_rev(reci, n);
		
	//Ispis rezultata
	stampaj(reci, n);
	
	
	//Oslobadjenje niza reci
	for(i=0; i<n; i++)
		free(reci[i]);
	free(reci);
		
	return 0;
}