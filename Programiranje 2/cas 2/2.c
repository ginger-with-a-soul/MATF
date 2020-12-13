#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	int i = 0, n, *im, *br;
	double suma = 0, prosek;

	fscanf(stdin, "%i", &n);
	if(n<1){
		greska();
	}

	im = (int*)calloc(n, sizeof(int));
	if(im == NULL){
		greska();
	}

	br = (int*)calloc(n, sizeof(int));
	if(br == NULL){
		greska();
	}

	for(i = 0;i<n;i++){
		fscanf(stdin, "%i %i", &br[i], &im[i]);
		if(im[i] == 0){
			greska();
		}
		suma += (double)br[i]/im[i];
	}

	prosek = (double)suma/n;

	for(i = 0;i<n;i++){
		if((double)br[i]/im[i] > prosek){
			fprintf(stdout, "%i/%i", br[i], im[i]);
		}
	}

	free(br);
	free(im);

	return 0;
}