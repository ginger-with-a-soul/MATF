 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 
 void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_FAILURE);
 }
 
 void stampaj(double* niz, int n)
 {
	int i;
	for(i=0; i<n; i++)
		printf("%g ", niz[i]);
	printf("\n");
 }
 
 void merge_sort(double* niz, int l, int d, double* pom)
 {
	
	if(l >= d)
		return;
		
	int s = (l+d)/2;
	
	//Sortiramo levu polovinu
	merge_sort(niz, l, s, pom); 
	
	//Sortiramo desnu polovinu
	merge_sort(niz, s+1, d, pom);

	//Spajamo sortirane nizove u pomocni niz koji na kraju treba da bude sortiran
	int i, j, k=0;
	i = l; 		//i krece od leve granice levog niza
	j = s+1; 	//j krece od leve granice desnog niza
	
	while(i <= s && j <= d)
	{
		if(niz[i] < niz[j])
			pom[k++] = niz[i++];
		else
			pom[k++] = niz[j++];
	}
	
	while(i <= s)
		pom[k++] = niz[i++];
	
	while(j <= d)
		pom[k++] = niz[j++];
		
	//Vracamo sortirani niz iz pom u niz
	for(i=l, k=0; i<=d; i++, k++)
		niz[i] = pom[k];
 }
 
  void merge_sort_rev(double* niz, int l, int d, double* pom)
 {
	if(l >= d)
		return;
		
	int s = (l+d)/2;
	
	//Sortiramo levu polovinu
	merge_sort_rev(niz, l, s, pom); 
	
	//Sortiramo desnu polovinu
	merge_sort_rev(niz, s+1, d, pom);

	//Spajamo sortirane nizove u pomocni niz koji na kraju treba da bude sortiran
	int i, j, k=0;
	i = l; 		//i krece od leve granice levog niza
	j = s+1; 	//j krece od leve granice desnog niza
	
	while(i <= s && j <= d)
	{
		if(niz[i] > niz[j])
			pom[k++] = niz[i++];
		else
			pom[k++] = niz[j++];
	}
	
	while(i <= s)
		pom[k++] = niz[i++];
	
	while(j <= d)
		pom[k++] = niz[j++];
		
	//Vracamo sortirani niz iz pom u niz
	for(i=l, k=0; i<=d; i++, k++)
		niz[i] = pom[k];
 }
 
 void razmeni(double* niz, int i, int j)
 {
	double tmp = niz[i];
	niz[i] = niz[j];
	niz[j] = tmp;
 }
 
  void quick_sort(double* niz, int l, int d)
 {
	if(l >= d)
		return;
	
	int poz_pivot = l;
	int i;
	//Postavljamo sve elemente manje od pivota levo
	for(i=l+1; i <= d; i++)
	{
		if(niz[i] < niz[l])
			razmeni(niz, i, ++poz_pivot);
	}
	//Postavljamo pivota na svoje mesto
	razmeni(niz, l, poz_pivot);
	
	//Rekurzivno ponavljamo postupak za elemente [l, poz_pivot-1] i [poz_pivot+1, d]
	quick_sort(niz, l, poz_pivot-1);
	quick_sort(niz, poz_pivot+1, d);
 }
 
  void quick_sort_rev(double* niz, int l, int d)
 {
 	if(l >= d)
		return;
	
	int poz_pivot = l;
	int i;
	//Postavljamo sve elemente vece od pivota levo
	for(i=l+1; i <= d; i++)
	{
		if(niz[i] > niz[l])
			razmeni(niz, i, ++poz_pivot);
	}
	//Postavljamo pivota na svoje mesto
	razmeni(niz, l, poz_pivot);
	
	//Rekurzivno ponavljamo postupak za elemente [l, poz_pivot-1] i [poz_pivot+1, d]
	quick_sort_rev(niz, l, poz_pivot-1);
	quick_sort_rev(niz, poz_pivot+1, d);
 }
 
 /*
 Treba da vrati:
 - nesto pozitivno ako a treba da se nadje posle b u nizu
 - nesto negativno ako a treba da se nadje pre b u nizu
 - 0 ako su a i b jednaki
 */
 int poredi1(const void* a, const void *b)
 {
	double x = *(double*)a;
	double y = *(double*)b;
	if(x<y)
		return -1;
	else if(x>y)
		return 1;
	else
		return 0;
 }
 
 int poredi2(const void* a, const void *b)
 {
	double x = *(double*)a;
	double y = *(double*)b;
	if(x<y)
		return 1;
	else if(x>y)
		return -1;
	else
		return 0;
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

	//Ucitavanje elemenata niza
	int i;
	for(i=0; i<n; i++)
		scanf("%lf", &niz[i]);
	
	//Alokacija pomocnog niza za merge sort:
	double* pomocni = malloc(n*sizeof(double));
	if(pomocni == NULL)
		greska();
		
	if(strcmp(argv[1], "-m") == 0)
		merge_sort(niz, 0, n-1, pomocni);
	else if(strcmp(argv[1], "-mr") == 0)
		merge_sort_rev(niz, 0, n-1, pomocni);
	else if(strcmp(argv[1], "-q") == 0)
		quick_sort(niz, 0, n-1);
	else if(strcmp(argv[1], "-qr") == 0)
		quick_sort_rev(niz, 0, n-1);
	else if(strcmp(argv[1], "-qsort") == 0)
		qsort(niz, n, sizeof(double), poredi1);
	else if(strcmp(argv[1], "-qsortr") == 0)
	{
		qsort(niz, n, sizeof(double), poredi2);
	}
		
	//Ispis rezultata
	stampaj(niz, n);
	
	//Oslobadjanje niza
	free(niz);
	free(pomocni);
	return 0;
 }