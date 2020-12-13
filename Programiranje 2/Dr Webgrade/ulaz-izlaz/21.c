#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DAT 64
#define MAX_REC 82

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	char ime1[MAX_DAT], ime2[MAX_DAT], rec[MAX_REC], *linija = NULL, rec_iz_linije[MAX_REC];
	FILE *ulaz, *izlaz;
	size_t duzina_linije = 0;
	int korak = 0, ukupno = 0, brlinije = 1, n, br = 0;

	fscanf(stdin, "%s %s %u", ime1, ime2, &n);
	if(n<1){
		greska();
	}

	ulaz = fopen(ime1, "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen(ime2, "w");
	if(izlaz == NULL){
		greska();
	}

	fscanf(ulaz, "%s", rec);

	while(getline(&linija, &duzina_linije, ulaz) != EOF){
		ukupno = 0;
		br = 0;
		korak = 0;
		while(sscanf(linija + ukupno, "%s%n", rec_iz_linije, &korak) != EOF){
			ukupno += korak;
			if(strcmp(rec, rec_iz_linije) == 0){
				br++;
			}
		}
		if(br >= n){
			fprintf(izlaz, "%i:%i", br, brlinije);
		}
		brlinije++;
	}

	fclose(ulaz);
	fclose(izlaz);
	free(linija);
	return 0;
}