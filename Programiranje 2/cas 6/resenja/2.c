 #include<stdio.h>
 #include<stdlib.h>
 
  void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }
 
 /*
Funkcija koja u datom nizu linearnom pretragom trazi element x.
Ukoliko je element promadjen, vraca njegovu pozivuju u nizu.
U suprotnom vraca -1. 
 */
 int linearna_pretraga(int* niz, int n, int x)
 {
	int i;
	for(i=0; i<n; i++)
		if(niz[i] == x)
			return i;
			
	return -1;
 }

 /* *****ITERATIVNA IMPLEMENTACIJA***********
 Funkcija koja u datom nizu binarnom pretragom trazi element x.
Ukoliko je element promadjen, vraca njegovu pozivuju u nizu.
U suprotnom vraca -1. 
 */
 int binarna_pretraga(int* niz, int n, int x)
 {
	int l = 0;
	int d = n-1;
	int s;
	
	while(l <= d)
	{
		s = l + (d-l)/2;
		if(niz[s] == x)
			return s;
		else if(x < niz[s])
			d = s-1;
		else
			l = s+1;
	}
	return -1;
 }
 
 /* *****REKURZIVNA IMPLEMENTACIJA***********
 Funkcija koja u datom nizu binarnom pretragom trazi element x.
Ukoliko je element promadjen, vraca njegovu pozivuju u nizu.
U suprotnom vraca -1. 
 */
 int binarna_pretraga_rekurzivno(int* niz, int l, int d, int x)
 {
	if(l > d)
		return -1;
	
	int s = l + (d-l)/2;
	if(x == niz[s])
		return s;
	else if(x < niz[s])
		return binarna_pretraga_rekurzivno(niz, l, s-1, x);
	else
		return binarna_pretraga_rekurzivno(niz, s+1, d, x);
 }
 
 /*
 Funkcija poredjenja za bsearch. 
 Prvi argument predstavlja adresu trazenog elementa,
 Drugi argument predstavlja adresu jednog elementa niza.
 Funckija treba da vrati:
   * 0 ako su vrednosti na ovim adresama jednake,
   * nesto pozitivno ako je vrednost prvog argumenta veca,
   * nesto negativno ako je vrednost prvog argumenta manja.
   
 Posto su u ovom slucaju i a i b pokazivaci na int,
 pre svega treba kastovati adresu (sa void* na int*),
 a zatim treba izvrsiti poredjenje VREDNOSTI koje se nalaze
 na tim adresama. 
 
 Da bi se pristupilo vrednosti na datoj adresi, 
 potrebno je dereferencirati pokazivace koji su nam pristigli,
 a koje smo prethodno kastovali - odatle *(int*)
 
 Po pravilu za povratnu vrednost koje smo gore opisali, 
 ovu funkciju je moguce napisati i sa:
 int vr1 = *(int*)a;
 int vr2 = *(int*)b;
 
 if(vr1 == vr2) 
	return 0;
 else if(vr1 > vr2)
	return 1; //ili bilo koju drugu pozitivnu vrednost npr. return 5;
 else
	return -1;
 
 Skraceno to se moze napisati i u jednoj liniji:
 return *(int*)a - *(int*)b;
 */
 int poredi(const void* a, const void* b)
 {
	return *(int*)a - *(int*)b;
 }
 
 int main(){

 	int* a;
	int n;
	
	//Ucitavanje dimenzije niza
	scanf("%d", &n);
	if(n <= 0)
		greska();
	
	//Alociranje potrebnog prostora
	a = malloc(n*sizeof(int));
	if(a == NULL)
		greska();
	
	//Ucitavanje elemenata niza
	int i;
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	
	//Ucitavamo element koji se trazi
	int x;
	scanf("%d", &x);
	
	//Pozivamo sve funkcije pretrage koje smo napisali
	printf("LIN: %d\n", linearna_pretraga(a, n, x));
	printf("BIN: %d\n", binarna_pretraga(a, n, x));
	printf("REK: %d\n", binarna_pretraga_rekurzivno(a, 0, n-1, x));
 
	//Pozivamo funkciju bsearch
	/*
	Argumenti:
		1. Pokazivac na vrednost koju trazimo
		2. Niz
		3. Broj elemenata niza
		4. Velicina jednog clana niza
		5. Funkcija za poredjenje (opisana u komentaru iznad)
	Povratna vrednost: 
		Ako je element nadjen - pokazivac na taj element 
		Ako element nije nadjen - NULL
	*/
	int* p = bsearch(&x, a, n, sizeof(int), &poredi);
	if(p == NULL)
		printf("bsearch: -1\n");
	else
		printf("bsearch: %ld\n", p-a);
 
	//Oslobadjenje niza
	free(a);
	return 0;
 }