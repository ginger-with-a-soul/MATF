#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 81

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	char rec[MAX];
	int duzina, signal = 0, count = 0;
	
	for(int i = 1;i<argc;i++){
		strcpy(rec, argv[i]);
		duzina = strlen(rec);
		for(int j = 0, k = duzina-1;j<duzina/2;j++, k--){
			if(rec[j] != rec[k]){
				signal = 1;
			}
		}
		if(!signal){
			count++;
		}
		signal = 0;
	}

	fprintf(stdout, "%i\n", count);

	return 0;
}