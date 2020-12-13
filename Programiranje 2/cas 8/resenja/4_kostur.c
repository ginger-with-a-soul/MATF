 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 
 #define MAX_I 21
 
  void greska()
 {
	fprintf(stderr, "-1");
	exit(EXIT_SUCCESS);
 }
 
 //Definicija strukture student
 typedef struct {
	char ime[MAX_I];
	char prezime[MAX_I];
	char smer;
	float prosek;
 } STUDENT;
 
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

	if(strcmp(argv[1], "-q") == 0)
		{}
	else if(strcmp(argv[1], "-qsort") == 0)
		{}

	//Ispis rezultata
	for(i=0; i<n; i++)
		printf("%s %s %c %.2f\n", niz[i].ime, niz[i].prezime, niz[i].smer, niz[i].prosek);
		
	free(niz);
	fclose(ulaz);
	return 0;
 }