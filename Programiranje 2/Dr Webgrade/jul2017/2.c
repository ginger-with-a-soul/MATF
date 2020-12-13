#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIFRA 16

typedef struct{

	char sifra[MAX_SIFRA];
	unsigned dan;
	unsigned mesec;
	unsigned godina;

}ISPIT;

void error();
int poredi(const void *a, const void *b);


void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int poredi(const void *a, const void *b){
	ISPIT *prvi = (ISPIT*)a, *drugi = (ISPIT*)b;

	if(prvi->godina < drugi->godina){
		return -1;
	}
	else if(prvi->godina > drugi->godina){
		return 1;
	}
	else{
		if(prvi->mesec < drugi->mesec){
			return -1;
		}
		else if(prvi->mesec > drugi->mesec){
			return 1;
		}
		else{
			if(prvi->dan < drugi->dan){
				return -1;
			}
			else if(prvi->dan > drugi->dan){
				return 1;
			}
			else{
				return strcmp(drugi->sifra, prvi->sifra);
			}
		}
	}

}

int main(){

	FILE *input;
	ISPIT *niz;
	int i = 0, korak = 100;

	input = fopen("ispiti.txt", "r");
	if(input == NULL){
		error();
	}

	niz = (ISPIT*)calloc(korak, sizeof(ISPIT));
	if(niz == NULL){
		error();
	}

	while(fscanf(input, "%s %u %u %u", niz[i].sifra, &niz[i].dan, &niz[i].mesec, &niz[i].godina) == 4){
		if(i + 10 == korak){
			korak += 100;
			niz = realloc(niz, korak*sizeof(ISPIT));
			if(niz == NULL){
				error();
			}
		}
		if(niz[i].dan < 0 || niz[i].dan > 31 || niz[i].mesec < 0 || niz[i].mesec > 12 || niz[i].godina < 0 || (niz[i].mesec == 2 && niz[i].dan > 29)){
			error();
		}
		i++;
	}

	qsort(niz, i, sizeof(ISPIT), poredi);

	for(int j = 0; j < i; j++){
		fprintf(stdout, "%s ", niz[j].sifra);
	}

	fprintf(stdout, "\n");

	free(niz);
	fclose(input);
	return 0;
}
