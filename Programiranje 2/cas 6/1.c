#include <stdio.h>
#include <stdlib.h>


void greska();
void modifikuj(int *niz, int n, int (*modifikacija)(int));
int uvecaj_za_1(int x);
int kvadriraj(int x);
int promeni_znak(int x);
void ispisi(int *niz, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void modifikuj(int *niz, int n, int (*modifikacija)(int)){
	for(int i = 0;i<n;i++){
		niz[i] = modifikacija(niz[i]);
	}
}

int uvecaj_za_1(int x){
	return x+1;
}

int kvadriraj(int x){
	return x*x;
}

int promeni_znak(int x){
	return -1*x;
}

void ispisi(int *niz, int n){
	for(int i = 0;i<n;i++){
		fprintf(stdout, "%i ", niz[i]);
	}
	printf("\n");
}

int main(){
	int n, *niz;
	scanf("%i", &n);
	if(n<1){
		greska();
	}

	niz = (int*)calloc(n, sizeof(int));
	if(niz == NULL){
		greska();
	}
	for(int i = 0;i<n;i++){
		scanf("%i", &niz[i]);
	}

	modifikuj(niz, n, &uvecaj_za_1);
	ispisi(niz, n);

	modifikuj(niz, n, &kvadriraj);
	ispisi(niz, n);

	modifikuj(niz, n, &promeni_znak);
	ispisi(niz, n);

	free(niz);
	return 0;
}