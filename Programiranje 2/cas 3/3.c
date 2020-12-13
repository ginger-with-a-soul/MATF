#include <stdio.h>
#include <stdlib.h>

#define MAX 51

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	int n;
	char *ime;

	scanf("%i", &n);
	if(n<0 || n>100){
		greska();
	}

	FILE *izlaz;

	for(int i = 1;i<=n;i++){
		ime = (char*)calloc(MAX, sizeof(char));
		if(ime == NULL){
			greska();
		}
		sprintf(ime, "%i.txt", i);
		izlaz = fopen(ime, "w+");
		if(izlaz == NULL){
			greska();
		}
		for(int j = 0;j<=n;j += i){
			fprintf(izlaz, "%i ", j);
		}
		fclose(izlaz);
		free(ime);
	}
	

	return 0;
}