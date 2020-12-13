#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_REC 51
#define MAX_NAZIV 21

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	char ime[MAX_NAZIV];
	char rec[MAX_REC], prva_rec[MAX_REC];

	scanf("%s", ime);
	FILE* ulaz, *izlaz;
	ulaz = fopen(ime, "r");
	if(ulaz == NULL)
		greska();

	izlaz = fopen("rez.txt", "w");
	if(izlaz == NULL)
		greska();

	int n, i;
	fscanf(ulaz, "%d", &n);
	fscanf(ulaz, "%s", prva_rec);
	
	for(i = 1; i<n; i++)
  {
		fscanf(ulaz, "%s", rec);
		if(strstr(rec, prva_rec) != NULL && strchr(rec, '_') != NULL)
			fprintf(izlaz, "%s\n", rec);
	}

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}
