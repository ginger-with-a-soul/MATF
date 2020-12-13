#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc<3){
		greska();
	}

	int a, b;
	a = atoi(argv[1]); /*funkcija atoi konvertuje string u int
						i iskljucivo int. Ukoliko zelimo da konvertujemo
						u neki drugi tip onda mozemo da koristimo sscanf.
						Primer sscanf("5.3.2018.", "%i.%i.%i", &dan, &mesec, &godina)*/
	b = atoi(argv[2]);

	if(b<a){
		greska();
	}

	while(a<=b){
		fprintf(stdout, "%i ", a++);
	}

	fprintf(stdout, "\n");

	return 0;
}