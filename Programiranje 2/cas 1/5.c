#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA_RECI 51
#define MAX_IME_DATOTEKE 21
#define MAX_BROJ_RECI 256

void greska();

void greska(){
	fprintf(stdout, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *ulaz, *izlaz;
	int n, i = 0, br = 0, m;
	char imeDatoteke[MAX_IME_DATOTEKE];
	char rec[MAX_DUZINA_RECI];
	char nizReci[MAX_BROJ_RECI][MAX_DUZINA_RECI];

	scanf("%s", imeDatoteke);

	ulaz = fopen(imeDatoteke, "a+");
	if(ulaz == NULL){
		greska();
	}

	izlaz = fopen("//home//dimitrije//Desktop//cas 1//rez.txt", "w");

	fscanf(ulaz, "%i", &n);
	if(n<1 || n>MAX_BROJ_RECI){
		greska();
	}

	for(i = 0;i<n;i++){
		fscanf(ulaz, "%s", rec);
		strcpy(nizReci[i], rec);
		fprintf(stdout, "%s ", nizReci[i]);
		for(m = n-1;m>=0;m--){
			if(strcmp(nizReci[i], nizReci[m]) == 0){
				br++;
			}
		}	
		if(br==1){
			fprintf(izlaz, "%s ", nizReci[i]);
		}
		br = 0;
	}

	fprintf(stdout, "\n");


	fclose(ulaz);
	fclose(izlaz);

	return 0;
}