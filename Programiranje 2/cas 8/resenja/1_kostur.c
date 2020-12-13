 #include<stdio.h>
 #include<stdlib.h>

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }
 
 void stampaj(int* niz, int n)
 {
	int i;
	for(i=0; i<n; i++)
		printf("%d ", niz[i]);
	printf("\n");
 }
 
 int main(int argc, char* argv[]){
 
	if(argc != 2)
		greska();
		
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
		
	
	//Ispis rezultata
	stampaj(niz, n);
	
	//Oslobadjanje niza
	free(niz);
	return 0;
 }