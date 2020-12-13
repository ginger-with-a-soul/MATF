#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	printf("-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 2){
		greska();
	}

	int k, alocirano = 0, *a, n, i = 0;
	double sr;

	k = atoi(argv[1]);
	if(k<1){
		greska();
	}

	a = (int*)calloc(k, sizeof(int));
	if(a == NULL){
		greska();
	}

	alocirano = k;

	FILE *ulaz;

	ulaz = fopen("brojevi.txt", "r");
	if(ulaz == NULL){
		greska();
	}

	while(1){
		if(i == alocirano){
			alocirano += k;
			a = realloc(a, alocirano*sizeof(int));
			if(a == NULL){
				greska();
			}
		}
		fscanf(ulaz, "%i", &a[i]);
		if(a[i] == 0){
			break;
		}
		i++;
	}

	if(i%2 != 0){
		sr = a[i/2];
	}
	else{
		sr = (double)(a[i/2] + a[i/2 - 1])/2.0;
	}

	for(k = 0;k<=i;k++){
		if(a[k] > sr){
			fprintf(stdout, "%i ", a[k]);
		}
	}

	free(a);
	fclose(ulaz);

	return 0;
}