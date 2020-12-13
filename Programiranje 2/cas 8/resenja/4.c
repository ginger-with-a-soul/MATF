 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 
 #define MAX_I 21
 
  void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_FAILURE);
 }
 
 //Definicija strukture student
 typedef struct {
	char ime[MAX_I];
	char prezime[MAX_I];
	char smer;
	float prosek;
 } STUDENT;
 
 void razmeni(STUDENT* niz, int i, int j)
 {
	STUDENT tmp;
	tmp = niz[i];
	niz[i] = niz[j];
	niz[j] = tmp;
 }
 
 void quick_sort(STUDENT* niz, int l, int d)
 {
	if(l >= d)
		return;
	
	int pozicija_pivota = l;
	int i;
	
	for(i=l+1; i<=d; i++)
	{
		if(niz[i].prosek > niz[l].prosek || (niz[i].prosek == niz[l].prosek && strcmp(niz[i].prezime, niz[l].prezime) < 0))
			razmeni(niz, i, ++pozicija_pivota);
	}
	razmeni(niz, pozicija_pivota, l);
	
	quick_sort(niz, l, pozicija_pivota-1);
	quick_sort(niz, pozicija_pivota+1, d);
 }
 
 int poredi(const void* a, const void* b)
 {
	STUDENT s1 = *(STUDENT*)a;
	STUDENT s2 = *(STUDENT*)b;
	
	if(s1.prosek > s2. prosek || (s1.prosek == s2.prosek && s1.smer < s2.smer))
		return 1; //s1 treba da se nadje posle s2 u nizu
	else if((s1.prosek == s2.prosek && strcmp(s1.prezime, s2.prezime) ==0))
		return 0; //s1 i s2 su jednaki
	else
		return -1; //s1 treba da se nadje pre s2 u nizu
 }
 
 int main(int argc, char* argv[]){
 
	if(argc != 2)
		greska();
		
	/*Otvaramo datoteku studenti.txt za citanje*/
	FILE* ulaz = fopen("studenti.txt", "r");
	if(ulaz == NULL)
		greska();
		
	STUDENT* niz;

	//Citamo iz fajla broj studenata
	int n;
	fscanf(ulaz, "%d", &n);

	//Alociramo prostor za n studenata
	niz = malloc(n*sizeof(STUDENT));
	if(niz == NULL)
		greska();
		
	//Informacije o studentima smestamo u niz	
	int i;
	for(i=0; i<n; i++)
	{
		fscanf(ulaz, "%s%s %c%f", niz[i].ime, niz[i].prezime, &niz[i].smer, &niz[i].prosek);
	}

	//Sortiranje
	if(strcmp(argv[1], "-q") == 0)
		quick_sort(niz, 0, n-1);
	else if(strcmp(argv[1], "-qsort") == 0)
		qsort(niz, n, sizeof(STUDENT), poredi);

	//Ispis rezultata
	for(i=0; i<n; i++)
		printf("%s %s %c %.2f\n", niz[i].ime, niz[i].prezime, niz[i].smer, niz[i].prosek);
		
	free(niz);
	fclose(ulaz);
	return 0;
 }