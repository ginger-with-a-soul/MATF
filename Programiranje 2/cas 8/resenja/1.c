 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_FAILURE);
 }
 
 void stampaj(int* niz, int n)
 {
	int i;
	for(i=0; i<n; i++)
		printf("%d ", niz[i]);
	printf("\n");
 }

  void selection_sort(int* niz, int n)
 {
	int i, j;
	for(i=0; i<n; i++)
	{
		//Pronaci najmanji u ostatku niza i smestiti ga na poziciju i
		int poz_min = i;
		for(j=i+1; j<n; j++)
			if(niz[j] < niz[poz_min])
				poz_min = j;
		
		int tmp = niz[poz_min];
		niz[poz_min] = niz[i];
		niz[i] = tmp;
	}
 }
 
 void insertion_sort(int* niz, int n)
 {
	int i, j;
	for(i=1; i<n; i++)
	{
		int trenutni = niz[i];
		for(j=i; j>0 && trenutni < niz[j-1]; j--)
			niz[j] = niz[j-1];
		niz[j] = trenutni;
	}
 }
 
  void insertion_sort_rev(int* niz, int n)
 {
	int i, j;
	for(i=1; i<n; i++)
	{
		int trenutni = niz[i];
		for(j=i; j>0 && trenutni > niz[j-1]; j--)
			niz[j] = niz[j-1];
		niz[j] = trenutni;
	}
 }
 
 void selection_sort_rev(int* niz, int n)
 {
	int i, j;
	for(i=0; i<n; i++)
	{
		//Pronaci najveci u ostatku niza i smestiti ga na poziciju i
		int poz_max = i;
		for(j=i+1; j<n; j++)
			if(niz[j] > niz[poz_max])
				poz_max = j;
		
		int tmp = niz[poz_max];
		niz[poz_max] = niz[i];
		niz[i] = tmp;
	}
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
		
	if(strcmp(argv[1], "-i") == 0)
		insertion_sort(niz,n);
	else if(strcmp(argv[1], "-s") == 0)
		selection_sort(niz, n);
	else if(strcmp(argv[1], "-ir") == 0)
		insertion_sort_rev(niz, n);
	else if(strcmp(argv[1], "-sr") == 0)
		selection_sort_rev(niz, n);
		
	//Ispis rezultata
	stampaj(niz, n);
	
	//Oslobadjanje niza
	free(niz);
	return 0;
 }