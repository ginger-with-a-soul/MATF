#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	if(argc != 4){
		greska();
	}

	typedef struct razlomak{
		int br;
		int im;
	}RAZLOMAK;

	FILE *ulaz, *izlaz;
	int n;
	char *linija = NULL;
	size_t duzina_linije = 0;

	ulaz = fopen(argv[1], "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen(argv[2], "w");
	if(izlaz == NULL){
		greska();
	}

	fscanf(ulaz, "%i", &n);
	if(n<1 || n>MAX){
		greska();
	}

	RAZLOMAK niz[n];

	for(int i = 0;i<n+1;i++){
		if(i == 0){
			getline(&linija, &duzina_linije, ulaz);
			continue;
		}
		getline(&linija, &duzina_linije, ulaz);
		sscanf(linija, "%i/%i", &niz[i-1].br, &niz[i-1].im);
		if(niz[i-1].im == 0 || niz[i-1].br == 0){
			greska();	
		}
	}

	if(strcmp(argv[3], "-xy") == 0){
		for(int i = 0;i<n;i++){
			if(niz[i].br<0 && niz[i].im<0){
				fprintf(izlaz, "%i/%i %g\n", niz[i].im*-1, niz[i].br*-1, (float)(niz[i].im*-1)/(niz[i].br*-1));
			}
			else if(niz[i].br<0){
				fprintf(izlaz, "%i/%i %g\n", niz[i].im*-1, niz[i].br*-1, (float)(niz[i].im*-1)/(niz[i].br*-1));
			}
			else if(niz[i].im<0){
				fprintf(izlaz, "%i/%i %g\n", niz[i].im, niz[i].br, (float)(niz[i].im)/(niz[i].br));
			}
			else{
				fprintf(izlaz, "%i/%i %g\n", niz[i].im, niz[i].br, (float)(niz[i].im)/(niz[i].br));
			}
		}
	}
	else if(strcmp(argv[3], "-yx") == 0){
		for(int i = 0;i<n;i++){
			if(niz[i].br<0 && niz[i].im<0){
				fprintf(izlaz, "%g %i/%i\n", (float)(niz[i].im*-1)/(niz[i].br*-1), niz[i].im*-1, niz[i].br*-1);
			}
			else if(niz[i].br<0){
				fprintf(izlaz, "%g %i/%i\n", (float)(niz[i].im*-1)/(niz[i].br*-1), niz[i].im*-1, niz[i].br*-1);
			}
			else if(niz[i].im<0){
				fprintf(izlaz, "%g %i/%i\n", (float)(niz[i].im)/(niz[i].br), niz[i].im, niz[i].br);
			}
			else{
				fprintf(izlaz, "%g %i/%i\n", (float)(niz[i].im)/(niz[i].br), niz[i].im, niz[i].br);
			}
		}
	}
	else if(strcmp(argv[3], "-x") == 0){
		for(int i = 0;i<n;i++){
			if(niz[i].br<0 && niz[i].im<0){
				fprintf(izlaz, "%i/%i\n", niz[i].im*-1, niz[i].br*-1);
			}
			else if(niz[i].br<0){
				fprintf(izlaz, "%i/%i\n", niz[i].im*-1, niz[i].br*-1);
			}
			else if(niz[i].im<0){
				fprintf(izlaz, "%i/%i\n", niz[i].im, niz[i].br);
			}
			else{
				fprintf(izlaz, "%i/%i\n", niz[i].im, niz[i].br);
			}


		}
	}
	else if(strcmp(argv[3], "-y") == 0){
		for(int i = 0;i<n;i++){
			if(niz[i].br<0 && niz[i].im<0){
				fprintf(izlaz, "%g\n", (float)(niz[i].br*-1)/(niz[i].im*-1));
			}
			else if(niz[i].br<0){
				fprintf(izlaz, "%g\n", (float)(niz[i].br*-1)/(niz[i].im*-1));
			}
			else if(niz[i].im<0){
				fprintf(izlaz, "%g\n", (float)(niz[i].br)/(niz[i].im));
			}
			else{
				fprintf(izlaz, "%g\n", (float)(niz[i].br)/(niz[i].im));
			}

		}
	}
	else{
		greska();
	}

	free(linija);
	fclose(ulaz);
	fclose(izlaz);
	return 0;
}