#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 81

void greska();
void svaka_n_ta(char* ime, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}
void svaka_n_ta(char* ime, int n){
	FILE *ulaz;
	int i = 0;
	char rec[MAX];
	ulaz = fopen(ime, "r");
	if(ulaz == NULL){
		greska();
	}

	while(fscanf(ulaz, "%s", rec) == 1){
		i++;
		if(i == n){
			fprintf(stdout, "%s ", rec);
			i = 0;
		}
	}
	fclose(ulaz);
}


int main(int argc, char *argv[]){
	if(argc != 3){
		greska();
	}

	FILE *ulaz;
	int n = atoi(argv[2]);
	if(n<1){
		greska();
	}
	char ime[MAX];
	strcpy(ime, argv[1]);

	svaka_n_ta(ime, n);
	printf("\n");

	return 0;
}