#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 21

void error();
int poredi(const void *a, const void *b);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

typedef struct{
	char ime[MAX];
	char prezime[MAX];
	float prosek;
}STUDENT;

int poredi(const void *a, const void *b){
	STUDENT *prvi = (STUDENT*)a, *drugi = (STUDENT*)b;

	if(prvi->prosek < drugi->prosek){
		return 1;
	}
	else if(prvi->prosek > drugi->prosek){
		return -1;
	}
	else{
		int surname = strcmp(prvi->prezime, drugi->prezime);
		if(surname < 0){
			return -1;
		}
		else if(surname > 0){
			return 1;
		}
		else{
			return strcmp(prvi->ime, drugi->ime);
		}
	}
}

int main(){

	float ocena;
	unsigned n;
	STUDENT *niz;

	scanf("%f", &ocena);
	if(ocena < 6 || ocena > 10){
		error();
	}
	scanf("%u", &n);
	if(n < 1){
		error();
	}

	niz = (STUDENT*)calloc(n, sizeof(STUDENT));
	if(niz == NULL){
		error();
	}

	for(int i = 0; i < n; i++){
		scanf("%s %s %f", niz[i].prezime, niz[i].ime, &niz[i].prosek);
		if(niz[i].prosek < 6 || niz[i].prosek > 10){
			error();
		}
	}

	qsort(niz, n, sizeof(STUDENT), poredi);

	for(int i = 0; i < n; i++){
		if(niz[i].prosek >= ocena){
			fprintf(stdout, "%s %s %.2f\n", niz[i].prezime, niz[i].ime, niz[i].prosek);
		}
	}

	free(niz);
	return 0;
}