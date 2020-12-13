#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE	);
}

typedef struct{
	char ime[MAX];
	int kolicina;
	int pojavljivanje;
}PRIBOR;

int main(){
	int n, suma = 0;
	PRIBOR *niz;
	niz = (PRIBOR*)calloc(n, sizeof(PRIBOR));
	if(niz == NULL){
		greska();
	}
	fscanf(stdin, "%i", &n);
	if(n<1){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%s %i", niz[i].ime, &niz[i].kolicina);
		if(niz[i].kolicina < 1){
			greska();
		}
		niz[i].pojavljivanje = 0;
	}

	for(int i = 0;i<n;i++){
		if(niz[i].pojavljivanje){
			continue;
		}
		suma = niz[i].kolicina;
		for(int j = i+1;j<n;j++){
			if(strcmp(niz[i].ime, niz[j].ime) == 0){
				niz[j].pojavljivanje++;
				suma += niz[j].kolicina;
			}
		}
		fprintf(stdout, "%s %i\n", niz[i].ime, suma);
	}
	free(niz);
	return 0;
}