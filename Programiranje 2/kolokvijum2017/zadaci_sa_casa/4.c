#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 81

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	if(argc != 3){
		greska();
	}

	char rec[MAX];

	strcpy(rec, argv[2]);

	int duzina = strlen(rec);

	if(strcmp(argv[1], "-m") == 0){
		for(int i = 0;i<duzina;i++){
			if(isupper(rec[i])){
				rec[i] = tolower(rec[i]);
			}
		}
	}
	else if(strcmp(argv[1], "-v") == 0){
		for(int i = 0;i<duzina;i++){
			if(islower(rec[i])){
				rec[i] = toupper(rec[i]);
			}
		}

	}
	else if(strcmp(argv[1], "-mv") == 0){
		for(int i = 0;i<duzina;i++){
			if(isupper(rec[i])){
				rec[i] = tolower(rec[i]);
			}
			else if(islower(rec[i])){
				rec[i] = toupper(rec[i]);
			}
		}

	}
	else{
		greska();
	}

	fprintf(stdout, "%s\n", rec);
	return 0;
}