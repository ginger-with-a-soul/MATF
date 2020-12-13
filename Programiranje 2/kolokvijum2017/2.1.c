#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 11

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

typedef struct{
	char indeks[MAX];
	int ocena;
	int pojavljivanje;
}STUDENT;

int main(){
	int n, delilac = 1, suma_ocena = 0;
	double prosek;
	STUDENT *niz;

	fscanf(stdin, "%i", &n);
	if(n<1){
		greska();
	}

	niz = (STUDENT*)calloc(n, sizeof(STUDENT));
	if(niz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%s %i", niz[i].indeks, &niz[i].ocena);
		if(niz[i].ocena<6 || niz[i].ocena>10){
			greska();
		}
		niz[i].pojavljivanje = 0;
	}

	for(int i = 0;i<n;i++){
		if(niz[i].pojavljivanje){
			continue;
		}
		delilac = 1;
		suma_ocena = niz[i].ocena;
		for(int j = i+1;j<n;j++){
			if(strcmp(niz[i].indeks, niz[j].indeks) == 0){
				niz[j].pojavljivanje++;
				delilac++;
				suma_ocena += niz[j].ocena;
			}
		}
		prosek = (double)(suma_ocena/delilac);
		fprintf(stdout, "%s %.2lf\n", niz[i].indeks, prosek);
	}
	free(niz);
	return 0;
}