 #include<stdio.h>
 #include<stdlib.h>

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }
 
 int uvecaj_za_1(int x)
{
	return x+1;
}

int kvadriraj(int x)
{
	return x*x;
}

int promeni_znak(int x)
{
	return -x;
}
 
 void modifikuj(int* niz, int n, int (*modifikacija)(int))
 {
	int i;
	for(i=0; i<n; i++)
	{
		niz[i] = modifikacija(niz[i]);
	}
 }
 
 void stampaj(int* niz, int n)
 {
	int i;
	for(i=0; i<n; i++)
		printf("%d ", niz[i]);
	printf("\n");
 }
 
 int main(){
 
	int* niz;
	int n;
	
	//Ucitavanje dimenzije niza
	scanf("%d", &n);
	if(n <= 0)
		greska();
	
	//Alociranje potrebnog prostora
	niz = malloc(n*sizeof(int));
	if(niz == NULL)
		greska();

	//Ucitavanje elemenata niza
	int i;
	for(i=0; i<n; i++)
		scanf("%d", &niz[i]);
		
	//Izmene niza na sva tri nacina
	printf("Uvecano za 1:");
	modifikuj(niz, n, &uvecaj_za_1);
	stampaj(niz, n);
	
	printf("Kvadrirano: ");
	modifikuj(niz, n, &kvadriraj);
	stampaj(niz, n);
	
	printf("Promenjen znak: ");
	modifikuj(niz, n, &promeni_znak);
	stampaj(niz, n);
	
	//Oslobadjanje niza
	free(niz);
	return 0;
 }