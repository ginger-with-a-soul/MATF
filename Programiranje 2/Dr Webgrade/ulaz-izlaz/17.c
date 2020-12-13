#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	FILE *ulaz1, *ulaz2;
	char c;

	ulaz1 = fopen("plain.txt", "r");
	if(ulaz1 == NULL){
		greska();
	}

	ulaz2 = fopen("plain.txt", "r+");
	if(ulaz2 == NULL){
		greska();
	}

	while((c = fgetc(ulaz1)) != EOF){
		if(isalpha(c)){
			if(c == 'a'){
				fputc('Z', ulaz2);
			}
			else if(c == 'A'){
				fputc('z', ulaz2);
			}
			else if(c > 'a' && c <= 'z'){
				fputc(c-33, ulaz2);
			}
			else if(c > 'A' && c <= 'Z'){
				fputc(c+31, ulaz2);
			}
		}
		else{
			fputc(c, ulaz2);
			}
	}

	fclose(ulaz1);
	fclose(ulaz2);

	return 0;
}