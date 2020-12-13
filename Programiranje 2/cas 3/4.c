#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 21

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc!=2){
		greska();
	}

	FILE *ulaz;
	char rec[MAX], rec_iz_linije[MAX], *linija = NULL;
	int n;
	size_t duzina_linije = 0;
	/*linija = NULL i size_t duzina_linije = 0
	sluze za fju getline koja upisuje liniju iz zeljene
	datoteke i azurira duzina_linije na broj ucitanih karaktera.
	getline je bolja od fgets zato sto nije potrebno znati
	duzinu liniji. Getline sama dinamicki alocira prostor za liniju
	za razliku od fgets koja zahteva staticki odredjen prostor*/

	fscanf(stdin, "%i %s", &n, rec);
	if(n<0){
		greska();
	}

	ulaz = fopen(argv[1], "r");
	if(ulaz == NULL){
		greska();
	}

	while(getline(&linija, &duzina_linije, ulaz) != EOF){
		int korak = 0, a = 0, ukupno = 0;
		while(sscanf(linija + ukupno, "%s%n", rec_iz_linije, &korak) != EOF){ /*sscanf cita iz stringa ali pati od Slemijevog
																				pejnter algoritma, odnosno kad cita uvek cita
																				sa pocetka linije/string pa zato stavljamo
																				korak ciji tip je %n. Azuriramo ukupno sa korakom
																				pri svakom citanju kako ne bismo citali iz pocetka
																				uvek*/
			ukupno += korak;
			if(strcmp(rec, rec_iz_linije) == 0){
				a++;
			}
		}
		if(a == n){
			fprintf(stdout, "%s\n", linija);
		}
	}

	fclose(ulaz);
	free(linija);

	return 0;
}