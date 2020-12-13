#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_IME 21

void greska();

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	FILE *prvi, *drugi;
	char imePrvi[MAX_IME], imeDrugi[MAX_IME];
	char c;

	scanf("%s %s %c", imePrvi, imeDrugi, &c);

	if(c != 'v' && c != 'm'){
		greska();
	}

if(strstr(imePrvi, ".txt") != NULL && strstr(imeDrugi, ".txt") != NULL){

	

	prvi = fopen(imePrvi, "a+"); /*u ovom modu fajl
									se u isto vreme	
									i cita i pise(na njegov kraj,
									a ne brise se pa se krece od pocetka)
									a ako ne postoji
									onda se sam pravi*/
	if(prvi == NULL){
		greska();
	}
	drugi = fopen(imeDrugi, "w");

	if(drugi == NULL){
		greska();
	}

	if(c == 'v'){
		while((c = fgetc(prvi)) != EOF){
			fputc(toupper(c), drugi);
		}
	}
	else{
		fputc(tolower(c), drugi);
	}
}
else{
	greska();
}

	fclose(prvi);
	fclose(drugi);

	return 0;
}