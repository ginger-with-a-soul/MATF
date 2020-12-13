#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	if(argc != 5){
		greska();
	}

	int a, b, n, count = 0, zbir_kvadrata;
	FILE *ulaz, *izlaz;
	double broj;

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	n = atoi(argv[3]);
	if(n<1 || a<0 || b<0){
		greska();
	}

	zbir_kvadrata = (a*a) + (b*b);

	ulaz = fopen(argv[4], "r");
	if(ulaz == NULL){
		greska();
	}
	izlaz = fopen("izlaz.txt", "w");
	if(izlaz == NULL){
		greska();
	}

	for(int i = 0;i<n;i++){
		fscanf(ulaz, "%lf", &broj);
		if(broj>zbir_kvadrata){
			count++;
		}
	}

	fprintf(izlaz, "%i", count);

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}