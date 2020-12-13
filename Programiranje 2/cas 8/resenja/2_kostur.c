#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_REC 51

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }

void stampaj(char** niz_reci, int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%s\n", niz_reci[i]);
}

void insertion_sort(char** niz_reci, int n)
{

}

void selection_sort(char** niz_reci, int n)
{

}

void selection_sort_rev(char** niz_reci, int n)
{

}

void insertion_sort_rev(char** niz_reci, int n)
{

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