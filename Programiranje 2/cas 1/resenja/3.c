#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_NAZIV 21

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	char ime1[MAX_NAZIV], ime2[MAX_NAZIV];
	char c;
	
	/*ulaz.txt izlaz.txt u*/
	scanf("%s%s %c", ime1, ime2, &c);
	if(c != 'u' && c != 'l')
		greska();

	FILE* ulaz, *izlaz;
	ulaz = fopen(ime1, "r");
	if(ulaz == NULL)
		greska();

	izlaz = fopen(ime2, "w");
	if(izlaz == NULL)
		greska();

	char karakter;
	if(c == 'u')
	{
		while((karakter = fgetc(ulaz)) != EOF)
			fputc(toupper(karakter), izlaz);
	}else{
		while((karakter = fgetc(ulaz)) != EOF)
			fputc(tolower(karakter), izlaz);
	}
	fclose(ulaz);
	fclose(izlaz);
return 0;
}
