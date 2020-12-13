#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void greska();
int unesiSkup(char **s, FILE* f);
void prebroj(char *s, int *br_slova, int *br_cifara);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int unesiSkup(char **s, FILE* f){
	char *p, c;
	int korak = 1, i = 0;
	p = (char*)calloc(1, sizeof(char));

	while(isalpha(c = fgetc(f)) || isdigit(c)){
		korak++;
		p = (char*)realloc(p, korak*sizeof(char));
		*s[i] = c;
		i++;
	}
	*s[i] = '\t';
	return i;
}

void prebroj(char *s, int *br_slova, int *br_cifara){
	*br_cifara = 0, *br_slova = 0;
	int i = 0;
	while(s[i] != '\t'){
		if(isalpha(s[i])){
			*br_slova++;
		}
		else{
			*br_cifara++;
		}
		i++;
	}
	fprintf(stdout, "broj slova: %i\nbroj cifara: %i", *br_slova, *br_cifara);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		greska();
	}

	FILE *f;
	int uspesnoUcitano, *br_slova, *br_cifara;
	char *s;

	f = fopen(argv[1], "r");
	if(f == NULL){
		greska();
	}

	uspesnoUcitano = unesiSkup(&s, f);
	prebroj(s, br_slova, br_cifara);

	fclose(f);
	return 0;
}