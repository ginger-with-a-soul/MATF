#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA 21

typedef struct{
	char prezime[MAX_DUZINA];
	char ime[MAX_DUZINA];
	float prosek;
}STUDENT;

void error();
int poredi(const void *a, const void *b);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int poredi(const void *a, const void *b){
	STUDENT *prvi = (STUDENT*)a, *drugi = (STUDENT*)b;
	if(prvi->prosek < drugi->prosek){
		return 1;
	}
	else if(prvi->prosek > drugi->prosek){
		return -1;
	}
	else{
		if(strcmp(prvi->prezime, drugi->prezime) < 0){
			return -1;
		}
		else if((prvi->prezime, drugi->prezime) > 0){
			return 1;
		}
		else{
			if(strcmp(prvi->ime, drugi->ime) < 0){
				return 1;
			}
			else{
				return -1;
			}
		}
	}
}

int main(){

	float min_prosek;
	unsigned n, flag = 0;
	STUDENT *niz;

	scanf("%f", &min_prosek);
	if(min_prosek < 6 || min_prosek > 10){
		error();
	}
	scanf("%u", &n);
	if(n < 0){
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
		if(niz[i].prosek >= min_prosek){
			flag = 1;
			printf("%s %s %.2f\n", niz[i].prezime, niz[i].ime, niz[i].prosek);
		}
	}

	if(!flag){
		printf("-\n");
	}


	free(niz);
	return 0;
}