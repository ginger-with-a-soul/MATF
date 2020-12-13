 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }
 
 void stampaj(double* niz, int n)
 {
	int i;
	for(i=0; i<n; i++)
		printf("%g ", niz[i]);
	printf("\n");
 }
 
 void merge_sort(double* niz, int l, int d, double* pomocni)
 {
 
 }
 
  void merge_sort_rev(double* niz, int l, int d, double* pomocni)
 {
 
 }
 
  void quick_sort(double* niz, int l, int d)
 {
 
 }
 
  void quick_sort_rev(double* niz, int l, int d)
 {
 
 }
 
 int main(int argc, char* argv[]){
 
	if(argc != 2)
		greska();
		
	double* niz;
	int n;
	
	//Ucitavanje dimenzije niza
	scanf("%d", &n);
	if(n <= 0)
		greska();
	
	//Alociranje potrebnog prostora
	niz = malloc(n*sizeof(double));
	if(niz == NULL)
		greska();

	//Alokacija pomocnog niza za merge sort:
	double* pomocni = malloc(n*sizeof(double));
	if(pomocni == NULL)
		greska();
			
	//Ucitavanje elemenata niza
	int i;
	for(i=0; i<n; i++)
		scanf("%lf", &niz[i]);
	
	//Sortiranje
	if(strcmp(argv[1], "-m") == 0)
		merge_sort(niz,0, n-1, pomocni);
	else if(strcmp(argv[1], "-mr") == 0)
		merge_sort_rev(niz, 0, n-1, pomocni);
	else if(strcmp(argv[1], "-q") == 0)
		quick_sort(niz, 0, n-1);
	else if(strcmp(argv[1], "-qr") == 0)
		quick_sort_rev(niz, 0, n-1);
	else if(strcmp(argv[1], "-qsort") == 0)
		{}
	else if(strcmp(argv[1], "-qsortr") == 0)
		{}
		
	//Ispis rezultata
	stampaj(niz, n);
	
	//Oslobadjanje niza
	free(niz);
	free(pomocni);
	return 0;
 }